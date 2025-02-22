// Fill out your copyright notice in the Description page of Project Settings.

#include "AiAgentPriorityManager.h"
#include "CoreGlobals.h"
#include "Math/UnrealMathUtility.h"
#include "Misc/Timespan.h"
#include "SoftDesignTraining/SoftDesignTraining.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SoftDesignTraining/AiAgentGroupManager.h"
#include <chrono>

AiAgentPriorityManager* AiAgentPriorityManager::m_Instance;

AiAgentPriorityManager::AiAgentPriorityManager()
{
    // Print a log message
    UE_LOG(LogSoftDesignTraining, Log, TEXT("AiAgentPriorityManager::AiAgentPriorityManager"));
}

AiAgentPriorityManager* AiAgentPriorityManager::GetInstance()
{
    if (!m_Instance)
    {
        m_Instance = new AiAgentPriorityManager();
    }

    return m_Instance;
}

void AiAgentPriorityManager::Destroy()
{
    delete m_Instance;
    m_Instance = nullptr;
}

void AiAgentPriorityManager::RegisterAIAgent(AAIController* aiAgent)
{
    m_registeredAgents.FindOrAdd(aiAgent);
}

void AiAgentPriorityManager::UnregisterAIAgent(AAIController* aiAgent)
{
    m_registeredAgents.Remove(aiAgent);
    m_doneAgents.Remove(aiAgent);
}

void AiAgentPriorityManager::CalculatePriorityAgents(const UWorld* world)
{
    if (m_GFrameCounter != GFrameCounter) {
        //GEngine->AddOnScreenDebugMessage(1, 1, FColor::Green, FString::Printf(TEXT("GFrameCounter %i"), GFrameCounter));
        m_GFrameCounter = GFrameCounter;
        // update 10 off_screen player
        m_update_per_frame = 10;
        m_updated_in_frame = 0;
    }
}

bool AiAgentPriorityManager::IsInPriorityAgents(AAIController* aiAgent, const UWorld* world) {
    if (aiAgent->WasRecentlyRendered()){
        // update everyone on screen
        return true;
    }
    return !m_doneAgents.Contains(aiAgent) && m_updated_in_frame <= m_update_per_frame;
}

void AiAgentPriorityManager::AgentWasUpdated(AAIController* aiAgent) {
    if (aiAgent->WasRecentlyRendered()){
        m_updated_in_frame += 1;
    }
    m_doneAgents.Add(aiAgent);
    if (m_doneAgents.Num() >= m_registeredAgents.Num()){
        m_doneAgents.Empty();
    }
}
