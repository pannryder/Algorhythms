#pragma once
#include "TreeBehaviour.h"
#include "Agent.h"

class TreeFollowBehaviour : public TreeBehaviour {
private:
	glm::vec2 lastTargetPosition;
public:
	virtual bool Update(Agent* agent, float deltaTime);
};