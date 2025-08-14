#pragma once
#include "Agent.h"
#include "State.h"

class FiniteStateMachine : public Behaviour {
private:
    std::vector<State*> m_states;

    State* m_currentState;
    State* m_newState;

public:
    FiniteStateMachine(State* s) : m_currentState(s), m_newState(nullptr) {}
    virtual ~FiniteStateMachine();
    void Enter(Agent* agent);
    void Update(Agent* agent, float deltaTime);
    void AddState(State* state) { m_states.push_back(state); }
    void Exit(Agent* agent) {};
};