#include "FiniteStateMachine.h"

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
	if (newState != nullptr && newState != m_currentState)
	{
		m_currentState->Exit(agent);
		m_currentState = newState;
		m_currentState->Enter(agent);
	}
	m_currentState->Update(agent, deltaTime);
}

void FiniteStateMachine::Enter(Agent* agent)
{
	m_currentState->Enter(agent);
}

