#pragma once
#include "Behaviour.h"
#include "Agent.h"

class RunAwayBehaviour : public Behaviour {
private:
	glm::vec2 lastTargetPosition;
public:
	virtual void Update(Agent* agent, float deltaTime);
	void Enter(Agent* agent);
};