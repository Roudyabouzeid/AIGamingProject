#pragma once

#include "CoreMinimal.h"
#include <AIController.h>
/**
 *
 */
class SOFTDESIGNTRAINING_API AiAgentPriorityManager
{
public:
    static AiAgentPriorityManager* GetInstance();
    static void Destroy();

    void RegisterAIAgent(AAIController* aiAgent);
    void UnregisterAIAgent(AAIController* aiAgent);
    void CalculatePriorityAgents(const UWorld* world);
    bool IsInPriorityAgents(AAIController* aiAgent, const UWorld* world);
    void AgentWasUpdated(AAIController* aiAgent);

private:

    //SINGLETON
    AiAgentPriorityManager();
    static AiAgentPriorityManager* m_Instance;

    TSet<AAIController*> m_registeredAgents;
    TSet<AAIController*> m_doneAgents;
    uint64 m_GFrameCounter;
    uint64 m_update_per_frame;
    uint64 m_updated_in_frame;
};
