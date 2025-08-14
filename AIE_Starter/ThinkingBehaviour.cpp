#include "ThinkingBehaviour.h"

void ThinkingBehaviour::Update(Agent* agent, float deltaTime)
{
    agent->GoTo(agent->GetPosition());
}

void ThinkingBehaviour::Enter(Agent* agent)
{
    std::cout << agent->GetName() << " : Where did they go..." << std::endl;
    agent->AgentIsThinking();
    agent->SetColor(DARKGRAY);
    agent->Reset();
}
