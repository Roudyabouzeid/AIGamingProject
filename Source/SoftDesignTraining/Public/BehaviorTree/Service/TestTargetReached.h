// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "TestTargetReached.generated.h"

/**
 * 
 */
UCLASS()
class SOFTDESIGNTRAINING_API UTestTargetReached : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	UTestTargetReached();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
