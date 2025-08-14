#include "State.h"

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

std::vector<State::Transition> State::GetTransitions()
{
	return m_transitions;
}

void State::AddTransition(Condition* condition, State* state)
{
	m_transitions.push_back(Transition(condition, state));
}
