#pragma once
#include "Condition.h"

struct Transition {};

class State {
public:
    struct Transition {
        Transition(Condition* _condition, State* _state) : condition(_condition), targetState(_state) {};
        Condition* condition;
        State* targetState;
    };
private:
    std::vector<Transition> m_transitions;
    std::vector<Behaviour*> m_behaviours;
public:
    State(Behaviour* behaviour) { m_behaviours.push_back(behaviour); };
    ~State();
    virtual void Enter(Agent* agent) { m_behaviours[0]->Enter(agent); };
    virtual void Update(Agent* agent, float deltaTime);
    virtual void Exit(Agent* agent) {};
    std::vector<Transition> GetTransitions();
    void AddTransition(Condition* condition, State* state);
};
