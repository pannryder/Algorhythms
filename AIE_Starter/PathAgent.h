#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Node.h"
#include "raylib.h"

class PathAgent {
private:
    glm::vec2 m_position;
    int m_currentIndex;
    Node* m_currentNode;
    float m_speed;
    std::vector<Node*> m_path;
    Color m_color;

public:
    void Update(float deltaTime);
    void GoToNode(Node* node);
    void SetNode(Node* node);
    void SetSpeed(float speed);
    void Draw();
    void SetColor(Color _color);
    std::vector<Node*> GetPath();
    glm::vec2 GetPosition();
    void Reset();
};