// Fill out your copyright notice in the Description page of Project Settings.

#include "AiAgentGroupManager.h"
#include "SoftDesignTraining.h"
#include "BehaviorTree/BlackboardComponent.h"

AiAgentGroupManager* AiAgentGroupManager::m_Instance;

AiAgentGroupManager::AiAgentGroupManager()
{
	// Print a log message
	UE_LOG(LogSoftDesignTraining, Log, TEXT("AiAgentGroupManager::AiAgentGroupManager"));
}

AiAgentGroupManager* AiAgentGroupManager::GetInstance()
{
    if (!m_Instance)
    {
        m_Instance = new AiAgentGroupManager();
    }

    return m_Instance;
}

void AiAgentGroupManager::Destroy()
{
    delete m_Instance;
    m_Instance = nullptr;
}

void AiAgentGroupManager::RegisterAIAgent(AAIController* aiAgent)
{
    m_registeredAgents.FindOrAdd(aiAgent);
}

void AiAgentGroupManager::UnregisterAIAgent(AAIController* aiAgent)
{
    m_registeredAgents.Remove(aiAgent);
}

bool AiAgentGroupManager::IsInGroup(const AAIController* aiAgent)
{
	return m_registeredAgents.Contains(aiAgent);
}

TSet<AAIController*>& AiAgentGroupManager::GetGroup()
{
    return m_registeredAgents;
}

int32 AiAgentGroupManager::GroupSize()
{
    //GEngine->AddOnScreenDebugMessage(0, 1.0, FColor::Red, FString::Printf(TEXT("Example text that prints a float: %i"), m_registeredAgents.Num()));
    return m_registeredAgents.Num();
}

void AiAgentGroupManager::SetLKP(FVector lkp) {
    m_lkp = lkp;
}

FVector AiAgentGroupManager::GetLKP() {
    return m_lkp;
}

void AiAgentGroupManager::EmptyGroup() {
    for (auto agent : m_registeredAgents) {
        UBlackboardComponent* BB = agent->GetBlackboardComponent();
        BB->SetValueAsBool("PlayerDetected", false);
    }
    m_registeredAgents.Empty();
}

float AiAgentGroupManager::GenerateChaseAngle()
{
    return FMath::FRandRange(0.0, 360.0);
}
