#include "Sequence.h"

bool Sequence::Update(Agent* agent, float deltatime)
{
	for (TreeBehaviour* child : children) {
		if (child->Update(agent, deltatime) == false) {
			return false;
		}
	}
	return true;
}