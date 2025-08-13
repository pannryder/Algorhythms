#pragma once
#include "PathAgent.h"
#include "NodeMap.h"
#include "Behaviour.h"
#include "raylib.h"
#include <glm/glm.hpp>

class Agent : public PathAgent {
private:
    Behaviour* m_current;
    NodeMap* m_nodeMap;
    Agent* m_target = nullptr;
public:
    Agent() {};
    Agent(NodeMap* _nodeMap, Behaviour* _behaviour, Color _color) : m_current(_behaviour), m_nodeMap(_nodeMap) { PathAgent::SetColor(_color); };
    ~Agent() { delete m_current; };
    void Update(float deltaTime);
    void GoTo(glm::vec2 point);
    bool PathComplete();
    NodeMap* GetNodeMap();
    void SetTarget(Agent* _target);
    Agent* GetTarget();
};
