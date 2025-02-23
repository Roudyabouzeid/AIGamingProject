// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Task_MoveToBestFleeLocation.generated.h"

UCLASS()
class SOFTDESIGNTRAINING_API UTask_MoveToBestFleeLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	FVector GetFleeLocation(FVector PlayerLocation, FVector PawnLocation, UWorld* World);
};
