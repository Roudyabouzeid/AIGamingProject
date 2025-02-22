// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/Service/TryDetectPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"

#include "SoftDesignTraining/SoftDesignTraining.h"
#include "SoftDesignTraining/SDTCollectible.h"
#include "SoftDesignTraining/SDTFleeLocation.h"
#include "SoftDesignTraining/SDTUtils.h"
#include "EngineUtils.h"
#include "SoftDesignTraining/AiAgentGroupManager.h"

UTryDetectPlayer::UTryDetectPlayer()
{
    bCreateNodeInstance = true;
}

void UTryDetectPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    AAIController* aIController = OwnerComp.GetAIOwner();

	// R�cup�ration du AIController
	ASDTAIController* aiController = Cast<ASDTAIController>(aIController);
    APawn* controlledPawn = aiController->GetPawn();

    if (!controlledPawn)
        return;

    //TODO
    if (aiController->AtJumpSegment)
        return ProcessJump();

    FVector playerPosition = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();

    float radius = GetDetectionRadius(aiController);
    OwnerComp.GetBlackboardComponent()->SetValueAsFloat("MinDetection", radius);
    if (IsPlayerInVision(radius*2, aiController, playerPosition)) {
        OwnerComp.GetBlackboardComponent()->SetValueAsBool("PlayerDetected", true);
        OwnerComp.GetBlackboardComponent()->SetValueAsBool("TargetReached", true);
        if (AiAgentGroupManager::GetInstance()->IsInGroup(aIController))
            AiAgentGroupManager::GetInstance()->SetLKP(playerPosition);
    }
    else {
        OwnerComp.GetBlackboardComponent()->SetValueAsBool("PlayerDetected", false);
    }

    /*TArray<FHitResult> allDetectionHits;
    DetectionSweep(radius, aiController->m_DetectionCapsuleHalfLength * 2, controlledPawn, allDetectionHits);

    FHitResult detectionHit;
    aiController->GetHightestPriorityDetectionHit(allDetectionHits, detectionHit);
	
    ProcessPriorityHit(detectionHit, OwnerComp, aIController);*/
}

void UTryDetectPlayer::ProcessJump() {
    return;
}

float UTryDetectPlayer::GetDetectionRadius(ASDTAIController* aiController) {
    AiAgentGroupManager* groupManager = AiAgentGroupManager::GetInstance();

    if (!groupManager->IsInGroup(aiController)) {
        return aiController->m_DetectionCapsuleHalfLength;
    }

    auto dist = 0.0f;

    FVector LKP = groupManager->GetLKP();
    for (auto&& agent : groupManager->GetGroup()) {
        dist += (agent->GetPawn()->GetActorLocation() - LKP).Size();
    }

    return FMath::Max(dist*0.75, aiController->m_DetectionCapsuleHalfLength) * 1.0f / groupManager->GroupSize();
}

// TODO, changer vers un cône de vision.
bool UTryDetectPlayer::IsPlayerInVision(float length, ASDTAIController* aiController, FVector playerLocation) {
    FVector heightCorrection = FVector::UpVector * 50;
    APawn* controlledPawn = aiController->GetPawn();
    FVector start = controlledPawn->GetActorLocation() + heightCorrection;
    FVector end = playerLocation + heightCorrection;
    FVector vectorToPlayer = end - start;

    if ((end - start).Length() > length)
        return false;

    if (AiAgentGroupManager::GetInstance()->IsInGroup(aiController)) {
        return true;
    }

    FHitResult hitResult;
    TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
    TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
    GetWorld()->LineTraceSingleByObjectType(hitResult, start, end, TraceObjectTypes);

    if (!hitResult.bBlockingHit) {
        // There is no wall between ai and player
        // Need to find the angle between
        float visionAngle = 120.0;
        FVector directionToPlayer = vectorToPlayer.GetSafeNormal();
        float angleBetween = FMath::Abs(FMath::Acos(directionToPlayer.Dot(controlledPawn->GetActorForwardVector())));

        if (angleBetween < visionAngle / 2) {
            // We are in teh vision of the agent.
            return true;
        }
    }

    return false;
}
void UTryDetectPlayer::DetectionSweep(float radius, float length, APawn* controlledPawn, TArray<FHitResult>& allDetectionHits)
{
    // Zone de d�tection du joueuer
    FVector detectionStartLocation = controlledPawn->GetActorLocation(); //+ controlledPawn->GetActorForwardVector() * aiController->m_DetectionCapsuleForwardStartingOffset;
    FVector detectionEndLocation = detectionStartLocation + controlledPawn->GetActorForwardVector() * length;

    TArray<TEnumAsByte<EObjectTypeQuery>> detectionTraceObjectTypes;
    detectionTraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(COLLISION_PLAYER));

    // On effectue un sweep pour d�tecter le joueur
    GetWorld()->SweepMultiByObjectType(allDetectionHits, detectionStartLocation, detectionEndLocation, FQuat::Identity, detectionTraceObjectTypes, FCollisionShape::MakeSphere(radius));
}

void UTryDetectPlayer::ProcessPriorityHit(FHitResult& detectionHit, UBehaviorTreeComponent& OwnerComp, AAIController* aIController) {
    // Si on ne d�tecte pas le joueur, on met la variable "PlayerDetected" � false
    if (detectionHit.GetActor() == nullptr)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsBool("PlayerDetected", false);
        return;
    }
    // Sinon, on passe la variable � true
    if (detectionHit.GetComponent()->GetCollisionObjectType() == COLLISION_PLAYER)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsBool("PlayerDetected", true);
        // Update lkp in ai group controller

        if (AiAgentGroupManager::GetInstance()->IsInGroup(aIController))
            AiAgentGroupManager::GetInstance()->SetLKP(detectionHit.GetActor()->GetActorLocation());
    }
}