#include "Pathfinding.h"

#include <iostream>
#include <vector>
#include <algorithm>

AIForGames::Node* AIForGames::NodeMap::GetClosestNode(glm::vec2 worldPos)
{
    int i = (int)(worldPos.x / m_cellSize);
    if (i < 0 || i >= m_width) return nullptr;
    int j = (int)(worldPos.y / m_cellSize);
    if (j < 0 || j >= m_width) return nullptr;
    return GetNode(i,j);
}

void  AIForGames::NodeMap::Initialise(std::vector<std::string> asciiMap, const float cellSize)
{
    m_cellSize = cellSize;
    const char emptySquare = '0';

    // assume all strings are the same length, so we'll size the map according
    // to the number of strings and the length of the first one
    m_height = asciiMap.size();
    m_width = asciiMap[0].size();

    m_nodes = new Node * [m_width * m_height];

    // loop over the strings, creating Node entries as we go
    for (int y = 0; y < m_height; y++)
    {
        std::string& line = asciiMap[y];
        // report to the user that you have a mis-matched string length
        if (line.size() != m_width)
            std::cout << "Mismatched line #" << y << " in ASCII map (" << line.size() << " instead of " << m_width << ")" << std::endl;

        for (int x = 0; x < m_width; x++)
        {
            // get the x-th character, or return an empty node if the string         
            // isn't long enough
            char tile = x < line.size() ? line[x] : emptySquare;

            // create a node for anything but a '.' character
            m_nodes[x + m_width * y] = tile == emptySquare ? nullptr
                : new Node(((float)x + 0.5f) * m_cellSize, ((float)y + 0.5f) * m_cellSize);
        }
    }
    // now loop over the nodes, creating connections between each node and its      
    // neighbour to the West and South on the grid. this will link up all nodes
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            Node* node = GetNode(x, y);
            if (node)
            {
                // see if there's a node to our west, checking for array overruns      
                // first if we're on the west-most edge
                Node* nodeWest = x == 0 ? nullptr : GetNode(x - 1, y);
                if (nodeWest)
                {
                    node->ConnectTo(nodeWest, 1); // TODO weights
                    nodeWest->ConnectTo(node, 1);
                }

                // see if there's a node south of us, checking for array index
                // overruns again
                Node* nodeSouth = y == 0 ? nullptr : GetNode(x, y - 1);
                if (nodeSouth)
                {
                    node->ConnectTo(nodeSouth, 1);
                    nodeSouth->ConnectTo(node, 1);
                }
            }
        }
    }
}

void AIForGames::NodeMap::Draw()
{
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            Node* node = GetNode(x, y);
            if (node == nullptr)
            {
                // draw a solid block in empty squares without a navigation node
                DrawRectangle(x * m_cellSize, y * m_cellSize,
                    m_cellSize - 1, m_cellSize - 1, DARKGREEN);
            }
            else
            {
                // draw the connections between the node and its neighbours
                for (int i = 0; i < node->connections.size(); i++)
                {
                    Node* other = node->connections[i].target;
                    DrawLine((x + 0.5f) * m_cellSize, (y + 0.5f) * m_cellSize,
                        (int)other->position.x, (int)other->position.y,
                        BLACK);
                }
            }
        }
    }
}

void AIForGames::Node::ConnectTo(Node* other, float cost)
{
    connections.push_back(Edge(other, cost));
}

std::vector<AIForGames::Node*> AIForGames::dijkstrasSearch(Node* startNode, Node* endNode)
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

std::vector<AIForGames::Node*> AIForGames::AStarSearch(Node* startNode, Node* endNode)
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
                float hScore = glm::distance(c.target->position,endNode->position);
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

void AIForGames::DrawPath(std::vector<Node*> mapPath, Color lineColor)
{
    for (int i = 1; i < mapPath.size(); i++) {
        DrawLine(mapPath[i]->position.x, mapPath[i]->position.y,mapPath[i - 1]->position.x, mapPath[i - 1]->position.y, lineColor);
    }

}

void AIForGames::PathAgent::Update(float deltaTime)
{
    if (m_path.empty()) {
        return;
    }
    float distance = glm::distance(m_currentNode->position, m_position);
    glm::vec2 vecDist = m_currentNode->position - m_position;
    glm::vec2 vecUnit = glm::normalize(vecDist);
    distance = distance - (m_speed * deltaTime);
    if (distance > 0) {
        m_position = m_position + (m_speed * deltaTime * vecUnit);
    }
    else {
        ++m_currentIndex;
        m_position = m_currentNode->position;
        if (m_currentNode == m_path.back()) {
            m_path.clear();
        }
        else {
            m_currentNode = m_path[m_currentIndex];
            vecDist = m_currentNode->position - m_position;
            vecUnit = glm::normalize(vecDist);
            m_position = m_position - (distance * vecUnit);
        }
    }
}

void AIForGames::PathAgent::GoToNode(Node* node)
{
    m_path = AStarSearch(m_currentNode, node);
    m_currentIndex = 0;
}

void AIForGames::PathAgent::SetNode(Node* node)
{
    if (node != nullptr) {
        m_currentNode = node;
        m_position = node->position;
    }
}

void AIForGames::PathAgent::SetSpeed(float speed)
{
    m_speed = speed;
}

void AIForGames::PathAgent::Draw()
{
    DrawCircle((int)m_position.x, (int)m_position.y, 8, BROWN);
}
