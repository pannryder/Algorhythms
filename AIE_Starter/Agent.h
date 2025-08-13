//#pragma once
//#include "PathAgent.h"
//#include "NodeMap.h"
//#include "Behaviour.h"
//#include "raylib.h"
//
//class Agent {
//private:
//    PathAgent m_pathAgent;
//    Behaviour* m_current;
//    NodeMap* m_nodeMap;
//    Color m_color;
//public:
//    Agent() {};
//    Agent(NodeMap* _nodeMap, Behaviour* _behaviour) : m_current(_behaviour), m_nodeMap(_nodeMap), m_color(BROWN) {};
//    ~Agent() { delete m_current; };
//    void Update(float deltaTime);
//    void Draw();
//    void GoTo(glm::vec2 point);
//    void SetNode(Node* node);
//    std::vector<Node*> GetPath();
//};
