// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/Task/IsPlayerDetected.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UIsPlayerDetected::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Test de la variable "PlayerDetected" du Blackboard
	return OwnerComp.GetBlackboardComponent()->GetValueAsBool("PlayerDetected") ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}