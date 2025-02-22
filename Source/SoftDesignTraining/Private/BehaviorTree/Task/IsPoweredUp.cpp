// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/Task/IsPoweredUp.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "SoftDesignTraining/SDTAIController.h"
#include "SoftDesignTraining/SoftDesignTraining.h"
#include "SoftDesignTraining/SDTCollectible.h"
#include "SoftDesignTraining/SDTFleeLocation.h"
#include "SoftDesignTraining/SDTUtils.h"
#include "EngineUtils.h"


EBTNodeResult::Type UIsPoweredUp::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return SDTUtils::IsPlayerPoweredUp(GetWorld()) ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}