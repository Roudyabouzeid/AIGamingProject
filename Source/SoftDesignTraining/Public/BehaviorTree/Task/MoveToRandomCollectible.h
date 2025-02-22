// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "SoftDesignTraining/SDTCollectible.h"
#include "MoveToRandomCollectible.generated.h"

/**
 * 
 */
UCLASS()
class SOFTDESIGNTRAINING_API UMoveToRandomCollectible : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	public:
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	private:
		ASDTCollectible* FindRandomAvailableCollectible();
};
