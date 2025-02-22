// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MoveToPlayer.generated.h"

/**
 * 
 */
UCLASS()
class SOFTDESIGNTRAINING_API UMoveToPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	EBTNodeResult::Type ProcessCloseRange(AAIController* aIController, ACharacter* playerCharacter, UBehaviorTreeComponent& OwnerComp);
	FVector ProcessDestination(ACharacter* playerCharacter, UBehaviorTreeComponent& OwnerComp);
	EBTNodeResult::Type MoveToDestination(FVector& destination, AAIController* aIController, UBehaviorTreeComponent& OwnerComp);
};
