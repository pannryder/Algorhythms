#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Edge.h"

struct Node {
    Node(float x, float y) : position{ x, y }, gScore{}, hScore{}, fScore{}, previous{} {};
    glm::vec2 position;
    float gScore;
    float hScore;
    float fScore;
    Node* previous;
    std::vector<Edge> connections;
    void ConnectTo(Node* other, float cost);
};
