// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SDTBaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class SOFTDESIGNTRAINING_API ASDTBaseAIController : public AAIController
{
	GENERATED_BODY()

public:

    ASDTBaseAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
    virtual void Tick(float deltaTime) override;
    bool m_ReachedTarget;
	
protected:
    virtual void RotationUpdate(float deltaTime) {};
    virtual void ImpulseToDirection(float deltaTime) {};

private:
    virtual void GoToBestTarget(float deltaTime) {};
    virtual void UpdatePlayerInteraction(float deltaTime) {};
    virtual void ShowNavigationPath() {};
};
