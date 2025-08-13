#pragma once
#include "Node.h"
#include <string>

class NodeMap {
    size_t m_width, m_height;
    float m_cellSize;
    Node** m_nodes;

public:
    NodeMap() : m_width(0), m_height(0), m_cellSize(0), m_nodes(nullptr) {}
    ~NodeMap();
    void Initialise(std::vector<std::string> asciiMap, const float cellSize);
    Node* GetNode(int x, int y) { return m_nodes[x + m_width * y]; };
    Node* GetClosestNode(glm::vec2 worldPos);
    void Draw();
};