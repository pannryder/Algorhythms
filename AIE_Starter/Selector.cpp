#include "Selector.h"

bool Selector::Update(Agent* agent, float deltatime)
{
	for (TreeBehaviour* child : children) {
		if (child->Update(agent, deltatime) == true) {
			return true;
		}
	}
	return false;
}
