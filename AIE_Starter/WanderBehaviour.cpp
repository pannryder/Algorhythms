#include "WanderBehaviour.h"

void WanderBehaviour::Update(Agent* agent, float deltaTime)
{
	if (agent->PathComplete()) {
		agent->GoTo(agent->GetNodeMap()->GetRandomNode()->position);
	}
}

void WanderBehaviour::Enter(Agent* agent)
{
	std::cout << agent->GetName() << " : I must be seeing things..." << std::endl;
	agent->AgentIsntThinking();
	agent->SetColor(PINK);
	agent->Reset();
}
