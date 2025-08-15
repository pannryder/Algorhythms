#pragma once
#include "TreeBehaviour.h"

class Adaptor : public Behaviour {
	TreeBehaviour* m_behaviour;
public:
	Adaptor(TreeBehaviour* _behaviour) { m_behaviour = _behaviour; };
	~Adaptor() { delete m_behaviour; };
	void Update(Agent* agent, float deltaTime) { m_behaviour->Update(agent,deltaTime); };
};