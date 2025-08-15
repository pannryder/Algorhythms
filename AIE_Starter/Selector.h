#pragma once
#include "Composite.h"

class Selector : public Composite {
public:
	Selector(std::vector<TreeBehaviour*> _childrens) : Composite(_childrens) {};
	virtual bool Update(Agent* agent, float deltatime);

};