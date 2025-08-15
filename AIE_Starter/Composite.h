#pragma once
#include "TreeBehaviour.h"

class Composite : public TreeBehaviour {
protected:
	std::vector<TreeBehaviour*> children;
public:
	~Composite() { for (TreeBehaviour* i : children) { delete i; } };
	Composite(std::vector<TreeBehaviour*> _children) { children = _children; };
	virtual bool Update(Agent* agent, float deltaTime) = 0;
};