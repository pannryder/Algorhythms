#pragma once
#include "TreeBehaviour.h"
#include "Agent.h"

class TimeStart : public TreeBehaviour {
public:
    virtual bool Update(Agent* agent, float deltaTime) { agent->AgentIsThinking();return true; };
};