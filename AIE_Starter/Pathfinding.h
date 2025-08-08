#pragma once
#include "raylib.h"
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace AIForGames
{
    struct Node;
    void DrawPath(std::vector<Node*> mapPath, Color lineColor);
    std::vector<Node*> dijkstrasSearch(Node* startNode,Node* endNode);
    std::vector<Node*> AStarSearch(Node* startNode, Node* endNode);

    struct Edge {
        Node* target;
        float cost;
        Edge() { target = nullptr; cost = 0; };
        Edge(Node* _target, float _cost) : target(_target), cost(_cost) {};
    };

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

    class NodeMap {
        int m_width, m_height;
        float m_cellSize;
        Node** m_nodes;

    public:
        void Initialise(std::vector<std::string> asciiMap, const float cellSize);
        Node* GetNode(int x, int y) { return m_nodes[x + m_width * y]; };
        Node* GetClosestNode(glm::vec2 worldPos);
        void Draw();
    };

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

    class Agent {
    private:
        PathAgent m_pathAgent;
        Behaviour* m_current;
        NodeMap* m_nodeMap;
        Color m_color;
    public:
        Agent() {};
        Agent(NodeMap* _nodeMap, Behaviour* _behaviour) : m_current(_behaviour), m_nodeMap(_nodeMap), m_color(BROWN) {};
        ~Agent() { delete m_current; };
        void Update(float deltaTime);
        void Draw();
        void GoTo(glm::vec2 point);
        void SetNode(Node* node);
        std::vector<Node*> GetPath();
    };

    class Behaviour {
    public:
        virtual void Update(Agent* agent, float deltaTime) = 0;
    };

    class GotoPointBehaviour : public Behaviour {
    public:
        virtual void Update(Agent* agent, float deltaTime);
    };

}



