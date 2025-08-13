#include "FiniteStateMachine.h"

State::~State()
{
	for (Behaviour* b : m_behaviours)
		delete b;

	for (Transition t : m_transitions)
		delete t.condition;
}

void State::Update(Agent* agent, float deltaTime)
{
	for (Behaviour* b : m_behaviours)
		b->Update(agent, deltaTime);
}

std::vector<Transition> State::GetTransitions()
{
	return m_transitions;
}

FiniteStateMachine::~FiniteStateMachine()
{
	for (State* s : m_states)
		delete s;
}

void FiniteStateMachine::Update(Agent* agent, float deltaTime)
{
	State* newState = nullptr;

	// check the current state's transitions
	for (State::Transition t : m_currentState->GetTransitions())
	{
		if (t.condition->IsTrue(agent))
			newState = t.targetState;
	}
	m_currentState->Update(agent, deltaTime);
}
