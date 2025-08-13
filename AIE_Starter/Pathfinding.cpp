#include "Pathfinding.h"
#include "raylib.h"
#include <iostream>
#include <vector>
#include <algorithm>


std::vector<Node*> dijkstrasSearch(Node* startNode, Node* endNode)
{
    if (startNode == nullptr || endNode == nullptr){
        std::cout << "startNode or endNode is NULL!!!!!!!!!" << std::endl;
        return std::vector<Node*>();
    }

    if (startNode == endNode) {
        return std::vector<Node*>();
    }

    startNode->gScore = 0;
    startNode->previous = nullptr;

    std::vector<Node*> openList;
    std::vector<Node*> closedList;

    openList.push_back(startNode);

    while (!openList.empty()) {
        std::sort(openList.begin(), openList.end(), [](Node* a, Node* b) {return a->gScore < b->gScore;});
        Node* currentNode = openList.front();
        if (currentNode == endNode) {
            break;
        }
        openList.erase(openList.begin());
        closedList.push_back(currentNode);
        for (Edge &c : currentNode->connections) {
            ;
            if (std::find(closedList.begin(), closedList.end(), c.target) == closedList.end()) {
                float gScore = currentNode->gScore + c.cost;
                if (std::find(openList.begin(), openList.end(), c.target) == openList.end()) {
                    c.target->gScore = gScore;
                    c.target->previous = currentNode;
                    openList.push_back(c.target);
                }
                else if (gScore < c.target->gScore) {
                    c.target->gScore = gScore;
                    c.target->previous = currentNode;
                }
            }

        }
    }

    if (openList.empty()) {
        return{};
    }

    std::vector<Node*> Path;
    Node* currentNode = endNode;
    while (currentNode != nullptr)
    {
        Path.insert(Path.begin(), currentNode);
        currentNode = currentNode->previous;
    }
    return Path;
}

std::vector<Node*> AStarSearch(Node* startNode, Node* endNode)
{
    if (startNode == nullptr || endNode == nullptr) {
        std::cout << "startNode or endNode is NULL!!!!!!!!! STOP!!!!!" << std::endl;
        return std::vector<Node*>();
    }

    if (startNode == endNode) {
        return std::vector<Node*>();
    }

    startNode->gScore = 0;
    startNode->previous = nullptr;

    std::vector<Node*> openList;
    std::vector<Node*> closedList;

    openList.push_back(startNode);

    while (!openList.empty()) {
        std::sort(openList.begin(), openList.end(), [](Node* a, Node* b) {return a->fScore < b->fScore;});
        Node* currentNode = openList.front();
        if (currentNode == endNode) {
            break;
        }
        openList.erase(openList.begin());
        closedList.push_back(currentNode);
        for (Edge& c : currentNode->connections) {
            ;
            if (std::find(closedList.begin(), closedList.end(), c.target) == closedList.end()) {
                float gScore = currentNode->gScore + c.cost;
                float hScore = Heuristic(c.target,endNode);
                float fScore = gScore + hScore;

                if (std::find(openList.begin(), openList.end(), c.target) == openList.end()) {
                    c.target->gScore = gScore;
                    c.target->fScore = fScore;
                    c.target->previous = currentNode;
                    openList.push_back(c.target);
                }
                else if (gScore < c.target->gScore) {
                    c.target->gScore = gScore;
                    c.target->fScore = fScore;
                    c.target->previous = currentNode;
                }
            }
        }
    }

    if (openList.empty()) {
        return{};
    }

    std::vector<Node*> Path;
    Node* currentNode = endNode;
    while (currentNode != nullptr)
    {
        Path.insert(Path.begin(), currentNode);
        currentNode = currentNode->previous;
    }
    return Path;
}

float Heuristic(Node* a, Node* b)
{
    return glm::distance(a->position,b->position);
}

void DrawPath(std::vector<Node*> mapPath, Color lineColor)
{
    for (size_t i = 1; i < mapPath.size(); i++) {
        DrawLineV({mapPath[i]->position.x, mapPath[i]->position.y},
            { mapPath[i - 1]->position.x, mapPath[i - 1]->position.y }, lineColor);
    }
}