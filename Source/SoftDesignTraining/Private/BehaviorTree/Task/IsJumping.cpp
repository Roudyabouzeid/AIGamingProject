// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/Task/IsJumping.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SoftDesignTraining/SDTAIController.h"
#include "BehaviorTree/BlackboardComponent.h"



EBTNodeResult::Type UIsJumping::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* aIController = OwnerComp.GetAIOwner();
	if (aIController == nullptr)
    {
		return EBTNodeResult::Succeeded;
	}
	ASDTAIController* sDTAIController = Cast<ASDTAIController>(aIController);

	// R�cup�ration de la derni�re position de l'agent
	FVector lastPosition = OwnerComp.GetBlackboardComponent()->GetValueAsVector("LastPosition");
	
	// Permet de v�rifier si une t�l�portation de l'agent a eu lieu pour la compter comme un saut.
	if (FVector::Dist(aIController->GetPawn()->GetActorLocation(), lastPosition) < 30)
	{
		return EBTNodeResult::Failed;
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsVector("LastPosition", aIController->GetPawn()->GetActorLocation());
	// D�tection des diff�rentes phases de saut
	if (sDTAIController->InAir || sDTAIController->AtJumpSegment || sDTAIController->Landing)
	{
		return EBTNodeResult::Succeeded;
	}

	// Si aucune de ces conditions, la tache renvoie un �chec
    return EBTNodeResult::Failed;
}