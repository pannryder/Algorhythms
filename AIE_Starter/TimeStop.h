#pragma once
#include "TreeBehaviour.h"
#include "Agent.h"

class TimeStop : public TreeBehaviour {
public:
    virtual bool Update(Agent* agent, float deltaTime) { agent->AgentIsntThinking(); return true; };
};