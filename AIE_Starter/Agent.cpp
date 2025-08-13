#include "Agent.h"

void Agent::Update(float deltaTime)
{
    if (m_current)
        m_current->Update(this, deltaTime);
    PathAgent::Update(deltaTime);
}

void Agent::GoTo(glm::vec2 point)
{
    Node* end = m_nodeMap->GetClosestNode(point);
    PathAgent::GoToNode(end);
}

bool Agent::PathComplete()
{
    return PathAgent::GetPath().empty();
}

NodeMap* Agent::GetNodeMap()
{
    return m_nodeMap;
}

void Agent::SetTarget(Agent* _target)
{
    m_target = _target;
}

Agent* Agent::GetTarget()
{
    return m_target;
}
