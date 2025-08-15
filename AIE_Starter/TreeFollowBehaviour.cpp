#include "TreeFollowBehaviour.h"

bool TreeFollowBehaviour::Update(Agent* agent, float deltaTime)
{
    agent->SetColor(RED);
    Agent* target = agent->GetTarget();

    float dist = glm::distance(target->GetPosition(), lastTargetPosition);
    if (dist > agent->GetNodeMap()->GetCellSize())
    {
        lastTargetPosition = target->GetPosition();
        agent->GoTo(lastTargetPosition);
    }
    return true;
}
