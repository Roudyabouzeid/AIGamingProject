// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/Task/RemoveFromPursueGroup.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SoftDesignTraining/AiAgentGroupManager.h"

#include "SoftDesignTraining/SDTAIController.h"
#include "SoftDesignTraining/SDTUtils.h"
#include "EngineUtils.h"

EBTNodeResult::Type URemoveFromPursueGroup::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* aiController = OwnerComp.GetAIOwner();
	AiAgentGroupManager* groupManager = AiAgentGroupManager::GetInstance();
	// Suppression de l'agent du groupe de poursuite du joueur
	groupManager->UnregisterAIAgent(aiController);

	return EBTNodeResult::Succeeded;
}