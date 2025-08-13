#pragma once
#include "Node.h"
#include "raylib.h"

void DrawPath(std::vector<Node*> mapPath, Color lineColor);
std::vector<Node*> dijkstrasSearch(Node* startNode,Node* endNode);
std::vector<Node*> AStarSearch(Node* startNode, Node* endNode);
float Heuristic(Node* a, Node* b);
