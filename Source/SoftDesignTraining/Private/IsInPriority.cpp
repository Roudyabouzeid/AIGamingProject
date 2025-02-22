// Fill out your copyright notice in the Description page of Project Settings.


#include "IsInPriority.h"
#include "AiAgentPriorityManager.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SoftDesignTraining/SoftDesignTraining.h"

EBTNodeResult::Type UIsInPriority::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	AiAgentPriorityManager* priorityManager = AiAgentPriorityManager::GetInstance();
	bool update = priorityManager->IsInPriorityAgents(OwnerComp.GetAIOwner(), GetWorld());
	if (update) {
		priorityManager->AgentWasUpdated(OwnerComp.GetAIOwner());
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}