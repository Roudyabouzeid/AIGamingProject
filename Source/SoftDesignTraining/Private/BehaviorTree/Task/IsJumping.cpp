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

	// Récupération de la dernière position de l'agent
	FVector lastPosition = OwnerComp.GetBlackboardComponent()->GetValueAsVector("LastPosition");
	
	// Permet de vérifier si une téléportation de l'agent a eu lieu pour la compter comme un saut.
	if (FVector::Dist(aIController->GetPawn()->GetActorLocation(), lastPosition) < 30)
	{
		return EBTNodeResult::Failed;
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsVector("LastPosition", aIController->GetPawn()->GetActorLocation());
	// Détection des différentes phases de saut
	if (sDTAIController->InAir || sDTAIController->AtJumpSegment || sDTAIController->Landing)
	{
		return EBTNodeResult::Succeeded;
	}

	// Si aucune de ces conditions, la tache renvoie un échec
    return EBTNodeResult::Failed;
}