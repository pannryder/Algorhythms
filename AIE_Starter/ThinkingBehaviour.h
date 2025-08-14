#pragma once
#include "Behaviour.h"
#include "Agent.h"

class ThinkingBehaviour : public Behaviour {
public:
    virtual void Update(Agent* agent, float deltaTime);
    void Enter(Agent* agent);
};