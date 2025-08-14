#pragma once
#include "Condition.h"

class TimerCondition : public Condition
{
private:
    float m_timer;

public:
    TimerCondition(float t) : m_timer(t){}
    virtual bool IsTrue(Agent* agent);
};