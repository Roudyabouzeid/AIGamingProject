// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/Service/TestTargetReached.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"

#include "SoftDesignTraining/SDTAIController.h"
#include "SoftDesignTraining/SoftDesignTraining.h"
#include "SoftDesignTraining/SDTCollectible.h"
#include "SoftDesignTraining/SDTFleeLocation.h"
#include "SoftDesignTraining/SDTUtils.h"
#include "EngineUtils.h"

UTestTargetReached::UTestTargetReached()
{
    bCreateNodeInstance = true;
}

void UTestTargetReached::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// R�cup�ration du AIController, et on v�rifie qu'il n'est pas nul
	AAIController* aIController = OwnerComp.GetAIOwner();
	if (!aIController)
	{
		return;
	}

	ASDTAIController* aiController = Cast<ASDTAIController>(aIController);
	// Si l'agent a atteint sa cible, mise � jour de la variable bool�enne "TargetReached" dans le Blackboard
	if (aiController->m_ReachedTarget)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("TargetReached", true);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("TargetReached", false);
	}
}
