#pragma once
#include "Behaviour.h"
#include "Agent.h"

class FollowBehaviour : public Behaviour {
private:
	glm::vec2 lastTargetPosition;
public:
	virtual void Update(Agent* agent, float deltaTime);
};