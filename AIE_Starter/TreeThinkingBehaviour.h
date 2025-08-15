#pragma once
#include "TreeBehaviour.h"
#include "Agent.h"

class TreeThinkingBehaviour : public TreeBehaviour {
public:
    virtual bool Update(Agent* agent, float deltaTime);
};