#include "RunAwayBehaviour.h"

void RunAwayBehaviour::Update(Agent* agent, float deltaTime)
{
    Agent* target = agent->GetTarget();
    
}

void RunAwayBehaviour::Enter(Agent* agent)
{
    agent->SetColor(BLUE);
    agent->Reset();
}
