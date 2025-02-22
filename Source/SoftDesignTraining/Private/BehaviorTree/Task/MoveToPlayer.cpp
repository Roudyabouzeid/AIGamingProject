// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/Task/MoveToPlayer.h"

// Fill out your copyright notice in the Description page of Project Settings.
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Navigation/PathFollowingComponent.h"
#include "SoftDesignTraining/SDTAIController.h"
#include "SoftDesignTraining/SoftDesignTraining.h"
#include "SoftDesignTraining/SDTCollectible.h"
#include "SoftDesignTraining/SDTUtils.h"
#include "EngineUtils.h"
#include <SoftDesignTraining/AiAgentGroupManager.h>
#include <NavigationSystem.h>


EBTNodeResult::Type UMoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* aIController = OwnerComp.GetAIOwner();
    if (!aIController)
        return EBTNodeResult::Failed;

    ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!playerCharacter)
        return EBTNodeResult::Failed;

    if ((aIController->GetPawn()->GetActorLocation() - playerCharacter->GetActorLocation()).Size() < 200.0f) {
        return ProcessCloseRange(aIController, playerCharacter, OwnerComp);
    }

    FVector destination = ProcessDestination(playerCharacter, OwnerComp);

    return MoveToDestination(destination, aIController, OwnerComp);
}

EBTNodeResult::Type UMoveToPlayer::ProcessCloseRange(AAIController* aIController, ACharacter* playerCharacter, UBehaviorTreeComponent& OwnerComp) {
    aIController->MoveToActor(playerCharacter);
    OwnerComp.GetBlackboardComponent()->SetValueAsBool("TargetReached", false);
    return EBTNodeResult::Succeeded;
}

FVector UMoveToPlayer::ProcessDestination(ACharacter* playerCharacter, UBehaviorTreeComponent& OwnerComp) {
    FVector height_offset = FVector::UpVector * 100;
    float dist = OwnerComp.GetBlackboardComponent()->GetValueAsFloat("MinDetection");
    float angle = OwnerComp.GetBlackboardComponent()->GetValueAsFloat("ChaseAngle");

    FVector startPoint = playerCharacter->GetActorLocation() + height_offset;
    FVector endPoint = startPoint + FVector::XAxisVector.RotateAngleAxis(angle, FVector::UpVector) * dist;
    FHitResult hitResult;

    GetWorld()->LineTraceSingleByChannel(hitResult, startPoint, endPoint, ECollisionChannel::ECC_WorldStatic);

    FVector dest = endPoint - height_offset;
    if (hitResult.bBlockingHit) {
        dest = hitResult.Location - height_offset;
    }
    //DrawDebugDirectionalArrow(GetWorld(), startPoint, dest, dist, FColor::Blue, false, 1.0);

    return dest;
}

EBTNodeResult::Type UMoveToPlayer::MoveToDestination(FVector& destination, AAIController* aIController, UBehaviorTreeComponent& OwnerComp) {
    const UNavigationSystemV1* navSystem = UNavigationSystemV1::GetCurrent(aIController);
    UNavigationPath* tpath = navSystem->FindPathToLocationSynchronously(GetWorld(), aIController->GetPawn()->GetActorLocation(), destination);
    FNavPathSharedPtr navPath = tpath->GetPath();

    // Lance un déplacement de l'agent vers le joueur seulement si le chemin est valide, et met à jour la variable 
    // "TargetReached" du Blackboard à false (car poursuite en cours)
    if (navPath.IsValid())
        aIController->RequestMove(destination, navPath);
    else {
        // On délègue à la prochaine frame la tâche de calculer si cette nouvelle direction est valide.
        // Évite de monopoliser les ressources par un agent pour une frame donnée. 
        float angle = FMath::FRandRange(0.0, 360.0);
        OwnerComp.GetBlackboardComponent()->SetValueAsFloat("ChaseAngle", angle);
    }

    OwnerComp.GetBlackboardComponent()->SetValueAsBool("TargetReached", false);
    return EBTNodeResult::Succeeded;
}

