#include "SelectorBehaviour.h"

void SelectorBehaviour::SetBehaviour(Behaviour* b, Agent* agent)
{
    if (m_selected != b)
    {
        m_selected = b;
        agent->Reset();
    }
}

void SelectorBehaviour::Update(Agent* agent, float deltaTime)
{
    if (glm::distance(agent->GetPosition(), agent->GetTarget()->GetPosition()) < agent->GetNodeMap()->GetCellSize() * 5)
    {
        SetBehaviour(m_b1, agent);
        agent->SetColor(RED);
    }
    else
    {
        SetBehaviour(m_b2, agent);
        agent->SetColor(PINK);
    }
    m_selected->Update(agent, deltaTime);
}