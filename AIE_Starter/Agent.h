#pragma once
#include "PathAgent.h"
#include "NodeMap.h"
#include "Behaviour.h"
#include "raylib.h"
#include <glm/glm.hpp>
#include <string>

class Agent : public PathAgent {
private:
    Behaviour* m_current;
    NodeMap* m_nodeMap;
    Agent* m_target = nullptr;
    float m_timer;
    bool isThinking;
public:
    Agent() {};
    Agent(NodeMap* _nodeMap, Behaviour* _behaviour, Color _color, std::string _name) : m_current(_behaviour), m_nodeMap(_nodeMap) { PathAgent::SetColor(_color); PathAgent::SetName(_name), m_current->Enter(this); };
    ~Agent() { delete m_current; };
    void Update(float deltaTime);
    void GoTo(glm::vec2 point);
    bool PathComplete();
    NodeMap* GetNodeMap();
    void SetTarget(Agent* _target);
    Agent* GetTarget();
    void AgentIsThinking() { isThinking = true; };
    void AgentIsntThinking() { isThinking = false; m_timer = 0; };
    float GetTimer();
};
