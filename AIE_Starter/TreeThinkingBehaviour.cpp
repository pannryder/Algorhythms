#include "TreeThinkingBehaviour.h"

bool TreeThinkingBehaviour::Update(Agent* agent, float deltaTime)
{
    agent->SetColor(DARKGRAY);
    agent->GoTo(agent->GetPosition());
    return true;
}
