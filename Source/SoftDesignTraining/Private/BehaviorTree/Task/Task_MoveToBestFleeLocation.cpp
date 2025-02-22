// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/Task/Task_MoveToBestFleeLocation.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "SoftDesignTraining/SDTAIController.h"
#include "SoftDesignTraining/SoftDesignTraining.h"
#include "SoftDesignTraining/SDTCollectible.h"
#include "SoftDesignTraining/SDTFleeLocation.h"
#include "SoftDesignTraining/SDTUtils.h"
#include "EngineUtils.h"


EBTNodeResult::Type UTask_MoveToBestFleeLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* aIController = OwnerComp.GetAIOwner();
	if (!aIController)
		return EBTNodeResult::Failed;


    APawn* controlledPawn = aIController->GetPawn();
	if (!controlledPawn)
		return EBTNodeResult::Failed;

    ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!playerCharacter)
		return EBTNodeResult::Failed;

    // Déplacement de l'agent pour la fuite
	FVector bestFleeActorLocation = GetFleeLocation(playerCharacter->GetActorLocation(), controlledPawn->GetActorLocation(), GetWorld());

	// Si une position de fuite est trouvée, on déplace l'agent vers cette position
    if (bestFleeActorLocation != FVector::ZeroVector)
    {
        aIController->MoveToLocation(bestFleeActorLocation, 0.5f, false, true, false, false, NULL, false);
        OwnerComp.GetBlackboardComponent()->SetValueAsBool("TargetReached", false);
        return EBTNodeResult::Succeeded;
    }
    else 
    {
        return EBTNodeResult::Failed;
    }
}

FVector UTask_MoveToBestFleeLocation::GetFleeLocation(FVector playerLocation, FVector pawnLocation, UWorld* World)
{
    float bestLocationScore = 0.f;
	// Initialisation de la meilleure position de fuite à nullptr
    ASDTFleeLocation* bestFleeLocation = nullptr;
    for (TActorIterator<ASDTFleeLocation> actorIterator(World, ASDTFleeLocation::StaticClass()); actorIterator; ++actorIterator)
    {
        ASDTFleeLocation* fleeLocation = Cast<ASDTFleeLocation>(*actorIterator);
        if (fleeLocation)
        {
            float distToFleeLocation = FVector::Dist(fleeLocation->GetActorLocation(), pawnLocation);

            FVector selfToPlayer = playerLocation - pawnLocation;
            selfToPlayer.Normalize();

            FVector selfToFleeLocation = fleeLocation->GetActorLocation() - pawnLocation;
            selfToFleeLocation.Normalize();

            float fleeLocationToPlayerAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(selfToPlayer, selfToFleeLocation)));
            float locationScore = distToFleeLocation + fleeLocationToPlayerAngle * 100.f;

			// Mis à jour de la meilleure position de fuite à l'aide des scores
            if (locationScore > bestLocationScore)
            {
                bestLocationScore = locationScore;
                bestFleeLocation = fleeLocation;
            }
        }
	}
    
    // Si une position de fuite est trouvée, on renvoie sa position
	if (bestFleeLocation)
	{
		return bestFleeLocation->GetActorLocation();
	} else
	{
		return FVector::ZeroVector;
	}
}

