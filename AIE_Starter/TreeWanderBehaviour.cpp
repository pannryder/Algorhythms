#include "TreeWanderBehaviour.h"

bool TreeWanderBehaviour::Update(Agent* agent, float deltaTime)
{
	agent->SetColor(ORANGE);
	if (agent->PathComplete()) {
		agent->GoTo(agent->GetNodeMap()->GetRandomNode()->position);
	}
    return true;
}