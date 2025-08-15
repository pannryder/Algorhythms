#include "TreeDistanceCondition.h"

bool TreeDistanceCondition::Update(Agent* agent, float deltaTime)
{
    return (glm::distance(agent->GetPosition(), agent->GetTarget()->GetPosition()) < m_distance) == m_lessThan;
}
