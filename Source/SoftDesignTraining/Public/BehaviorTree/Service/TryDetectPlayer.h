// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "SoftDesignTraining/SDTAIController.h"
#include "TryDetectPlayer.generated.h"

/**
 * 
 */
UCLASS()
class SOFTDESIGNTRAINING_API UTryDetectPlayer : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UTryDetectPlayer();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	void ProcessJump();
	float GetDetectionRadius(ASDTAIController* aiController);
	bool IsPlayerInVision(float length, ASDTAIController* aiController, FVector playerLocation);
	void DetectionSweep(float radius, float length, APawn* controlledPawn, TArray<FHitResult>& allDetectionHits);
	void ProcessPriorityHit(FHitResult& detectionHit, UBehaviorTreeComponent& OwnerComp, AAIController* aIController);
};
