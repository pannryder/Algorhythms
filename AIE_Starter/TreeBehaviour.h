#pragma once
#include "Agent.h"

class TreeBehaviour {
public :
	virtual ~TreeBehaviour() {};
	virtual bool Update(Agent* agent, float deltaTime) = 0;
};