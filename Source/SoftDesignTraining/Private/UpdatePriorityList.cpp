// Fill out your copyright notice in the Description page of Project Settings.


#include "UpdatePriorityList.h"
#include "AiAgentPriorityManager.h"
#include "Engine/Engine.h"

EBTNodeResult::Type UUpdatePriorityList::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	TRACE_CPUPROFILER_EVENT_SCOPE(UUpdatePriorityList);
	AiAgentPriorityManager* priorityManager = AiAgentPriorityManager::GetInstance();
	priorityManager->RegisterAIAgent(OwnerComp.GetAIOwner());
	priorityManager->CalculatePriorityAgents(GetWorld());
	return EBTNodeResult::Succeeded;
}