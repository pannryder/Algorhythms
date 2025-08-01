#include "Pathfinding.h"
#include "raylib.h"
#include <iostream>
#include <vector>

void  AIForGames::NodeMap::Initialise(std::vector<std::string> asciiMap, int cellSize)
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
    // red color for the blocks
    Color cellColor;
    cellColor.a = 255;
    cellColor.r = 255;
    cellColor.g = 0;
    cellColor.b = 0;
    Color lineColor;
    lineColor.a = 255;
    lineColor.r = 0;
    lineColor.g = 0;
    lineColor.b = 0;

    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            Node* node = GetNode(x, y);
            if (node == nullptr)
            {
                // draw a solid block in empty squares without a navigation node
                DrawRectangle(x * m_cellSize, y * m_cellSize,
                    m_cellSize - 1, m_cellSize - 1, cellColor);
            }
            else
            {
                // draw the connections between the node and its neighbours
                for (int i = 0; i < node->connections.size(); i++)
                {
                    Node* other = node->connections[i].target;
                    DrawLine((x + 0.5f) * m_cellSize, (y + 0.5f) * m_cellSize,
                        (int)other->position.x, (int)other->position.y,
                        lineColor);
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
        std::cout << "startNode or endNode is NULL!!!!!!!!! SO SCAREY AAAAAHH!!!" << std::endl;
        return std::vector<Node*>();
    }

    if (startNode == endNode) {
        return std::vector<Node*>();
    }

    startNode->gScore = 0;
    startNode->previous = nullptr;

    std::vector<Node> openList;
    std::vector<Node> closedList;



}
