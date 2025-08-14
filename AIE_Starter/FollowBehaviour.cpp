#include "FollowBehaviour.h"

void FollowBehaviour::Update(Agent* agent, float deltaTime)
{
    Agent* target = agent->GetTarget();

    float dist = glm::distance(target->GetPosition(), lastTargetPosition);
    if (dist > agent->GetNodeMap()->GetCellSize())
    {
        lastTargetPosition = target->GetPosition();
        agent->GoTo(lastTargetPosition);
    }
}

void FollowBehaviour::Enter(Agent* agent)
{
    std::cout << agent->GetName() << " : I KNOW WHERE YOU ARE!!" << std::endl;
    agent->SetColor(RED);
    agent->Reset();
}
