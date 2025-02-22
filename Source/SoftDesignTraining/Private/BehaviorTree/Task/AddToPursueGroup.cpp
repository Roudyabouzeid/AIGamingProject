// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/Task/AddToPursueGroup.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SoftDesignTraining/AiAgentGroupManager.h"

#include "SoftDesignTraining/SDTAIController.h"
#include "SoftDesignTraining/SDTUtils.h"
#include "EngineUtils.h"
#include "Math/UnrealMathUtility.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UAddToPursueGroup::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* aiController = OwnerComp.GetAIOwner();
	AiAgentGroupManager* groupManager = AiAgentGroupManager::GetInstance();

	if (!groupManager->IsInGroup(aiController)) {
		// Ajout de l'agent au groupe de poursuite.
		groupManager->RegisterAIAgent(aiController);
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat("ChaseAngle", groupManager->GenerateChaseAngle());
	}

	return EBTNodeResult::Succeeded;
}