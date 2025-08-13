#pragma once

struct Node;

struct Edge {
    Node* target;
    float cost;
    Edge() { target = nullptr; cost = 0; };
    Edge(Node* _target, float _cost) : target(_target), cost(_cost) {};
};