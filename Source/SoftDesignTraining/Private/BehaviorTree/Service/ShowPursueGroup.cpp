// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/Service/ShowPursueGroup.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "SoftDesignTraining/SDTUtils.h"
#include "SoftDesignTraining/AiAgentGroupManager.h"
#include "EngineUtils.h"

UShowPursueGroup::UShowPursueGroup()
{
	bCreateNodeInstance = true;
}

void UShowPursueGroup::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* aIController = OwnerComp.GetAIOwner();
	AiAgentGroupManager* groupManager = AiAgentGroupManager::GetInstance();

	// Si l'agent est dans le groupe, on affiche un cercle vert au desus de sa tête
	if (groupManager->IsInGroup(aIController))
	{
		DrawDebugSphere(GetWorld(), aIController->GetPawn()->GetActorLocation() + FVector(0.f, 0.f, 100.f), 15.0f, 32.0f, FColor::Green);
	}
}
