#pragma once
#include "Composite.h"

class Sequence : public Composite {
public:
	Sequence(std::vector<TreeBehaviour*> _childrens) : Composite(_childrens) {};
	virtual bool Update(Agent* agent, float deltatime);
};