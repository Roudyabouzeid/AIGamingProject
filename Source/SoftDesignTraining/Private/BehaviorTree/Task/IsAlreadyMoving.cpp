// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/Task/IsAlreadyMoving.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "SoftDesignTraining/SDTAIController.h"
#include "SoftDesignTraining/SoftDesignTraining.h"
#include "SoftDesignTraining/SDTUtils.h"
#include "EngineUtils.h"

EBTNodeResult::Type UIsAlreadyMoving::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* aIController = OwnerComp.GetAIOwner();
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	// L'agent est consid�r� comme n'�tant pas en mouvement si la variable "ReachedTarget" est � true
    bool isTargetReached = BlackboardComp->GetValueAsBool("ReachedTarget");
	if (isTargetReached)
	{
		return EBTNodeResult::Failed;
	}

	// De plus, cas ou sa vitesse est nulle
	FVector velocity = aIController->GetPawn()->GetVelocity();
	if (velocity.Size() == 0)
	{
		return EBTNodeResult::Failed;
	}

	// Sinon, on le consid�re comme en mouvement
    return EBTNodeResult::Succeeded;
}