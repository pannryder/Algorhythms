#pragma once
#include "TreeBehaviour.h"

class TreeTimerCondition : public TreeBehaviour
{
private:
    float m_timer;

public:
    TreeTimerCondition(float t) : m_timer(t) {}
    virtual bool Update(Agent* agent, float deltaTime);
};