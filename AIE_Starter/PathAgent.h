#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Node.h"

class PathAgent {
private:
    glm::vec2 m_position;
    int m_currentIndex;
    Node* m_currentNode;
    float m_speed;

public:
    std::vector<Node*> m_path;
    void Update(float deltaTime);
    void GoToNode(Node* node);
    void SetNode(Node* node);
    void SetSpeed(float speed);
    void Draw();
};