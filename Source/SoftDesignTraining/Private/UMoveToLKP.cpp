// Fill out your copyright notice in the Description page of Project Settings.


#include "UMoveToLKP.h"

// Fill out your copyright notice in the Description page of Project Settings.
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "SoftDesignTraining/SDTAIController.h"
#include "SoftDesignTraining/SoftDesignTraining.h"
#include "SoftDesignTraining/SDTCollectible.h"
#include "SoftDesignTraining/SDTUtils.h"
#include "EngineUtils.h"
#include <SoftDesignTraining/AiAgentGroupManager.h>

EBTNodeResult::Type UMoveToLKP::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* aIController = OwnerComp.GetAIOwner();
    if (!aIController)
        return EBTNodeResult::Failed;

    if (!AiAgentGroupManager::GetInstance()->IsInGroup(aIController))
        return EBTNodeResult::Failed;

    if (OwnerComp.GetBlackboardComponent()->GetValueAsBool("TargetReached"))
        return EBTNodeResult::Failed;

    aIController->MoveToLocation(AiAgentGroupManager::GetInstance()->GetLKP());

    OwnerComp.GetBlackboardComponent()->SetValueAsBool("TargetReached", false);

    return EBTNodeResult::Succeeded;
}

