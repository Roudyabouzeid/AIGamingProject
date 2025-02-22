// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "ShowPursueGroup.generated.h"

/**
 * 
 */
UCLASS()
class SOFTDESIGNTRAINING_API UShowPursueGroup : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	UShowPursueGroup();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
