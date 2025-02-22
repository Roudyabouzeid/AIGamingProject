// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/Task/MoveToRandomCollectible.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "SoftDesignTraining/SDTAIController.h"
#include "SoftDesignTraining/SoftDesignTraining.h"
#include "SoftDesignTraining/SDTCollectible.h"
#include "SoftDesignTraining/SDTUtils.h"
#include "EngineUtils.h"


EBTNodeResult::Type UMoveToRandomCollectible::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* aIController = OwnerComp.GetAIOwner();
    if (!aIController)
        return EBTNodeResult::Failed;

    float closestSqrCollectibleDistance = 18446744073709551610.f;
    ASDTCollectible* closestCollectible = nullptr;

    ASDTCollectible* availableCollectible = FindRandomAvailableCollectible();

    if (availableCollectible != nullptr) {
        aIController->MoveToLocation(availableCollectible->GetActorLocation(), 0.5f, false, true, true, false, NULL, false);
        OwnerComp.GetBlackboardComponent()->SetValueAsBool("TargetReached", false);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}

ASDTCollectible* UMoveToRandomCollectible::FindRandomAvailableCollectible() {
    // TODO, possiblement partitionner ces deux lignes dans leurs propres méthodes. 
    TArray<AActor*> foundCollectibles;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASDTCollectible::StaticClass(), foundCollectibles);

    // Itération sur les collectibles, à la recherche d'un disponible (non en cooldown)
    while (foundCollectibles.Num() != 0)
    {
        int index = FMath::RandRange(0, foundCollectibles.Num() - 1);

        ASDTCollectible* collectibleActor = Cast<ASDTCollectible>(foundCollectibles[index]);
        if (!collectibleActor)
            return nullptr;

        if (!collectibleActor->IsOnCooldown())
        {
            // La task rend alors un succès
            return collectibleActor;
        }
        else
        {
            foundCollectibles.RemoveAt(index);
        }
    }
    return nullptr;
}




