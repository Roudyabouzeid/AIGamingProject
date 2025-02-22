#pragma once

#include "SDTBaseAIController.h"
#include "CoreMinimal.h"
/**
 * 
 */
class SOFTDESIGNTRAINING_API AiAgentGroupManager
{
public:   
    static AiAgentGroupManager* GetInstance();
    static void Destroy();

    int32 GroupSize();
    void RegisterAIAgent(AAIController* aiAgent);
    void UnregisterAIAgent(AAIController* aiAgent);
    bool IsInGroup(const AAIController* aiAgent);
    TSet<AAIController*>& GetGroup();
    void SetLKP(FVector lkp);
    FVector GetLKP();
    void EmptyGroup();
    float GenerateChaseAngle();

private:

    //SINGLETON
    AiAgentGroupManager();
    static AiAgentGroupManager* m_Instance;

    TSet<AAIController*> m_registeredAgents;

    FVector m_lkp;
};
