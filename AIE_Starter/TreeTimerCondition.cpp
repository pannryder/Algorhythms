#include "TreeTimerCondition.h"

bool TreeTimerCondition::Update(Agent* agent, float deltaTime)
{
    if (agent->GetTimer() < m_timer) {
        return true;
    }
    return false;
}