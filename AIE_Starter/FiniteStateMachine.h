#pragma once
#include "Agent.h"
struct Transition{};

class State {
public:
    struct Transition{
        Condition* condition;
        State* targetState;
    };
private:
    std::vector<Transition> m_transitions;
    std::vector<Behaviour*> m_behaviours;
public:
    State();
    ~State();
    virtual void Enter(Agent* agent);
    virtual void Update(Agent* agent, float deltaTime);
    virtual void Exit(Agent* agent);
    std::vector<Transition> GetTransitions();
};

class Condition {
public:
    virtual bool IsTrue(Agent* agent) = 0;
};

class FiniteStateMachine : public Behaviour {
private:
    std::vector<State*> m_states;

    State* m_currentState;
    State* m_newState;

public:
    FiniteStateMachine(State* s) : m_currentState(s), m_newState(nullptr) {}
    virtual ~FiniteStateMachine();
    void Update(Agent* agent, float deltaTime);
};