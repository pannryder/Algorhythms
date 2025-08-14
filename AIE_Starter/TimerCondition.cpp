#include "TimerCondition.h"

bool TimerCondition::IsTrue(Agent* agent)
{
    if (agent->GetTimer() > m_timer) {
        return true;
    }
    return false;
}
