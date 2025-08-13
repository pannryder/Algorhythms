#include <iostream>
#include "raylib.h"

#include "NodeMap.h"

Node* NodeMap::GetClosestNode(glm::vec2 worldPos)
{
    int i = (int)(worldPos.x / m_cellSize);
    if (i < 0 || i >= m_width) return nullptr;
    int j = (int)(worldPos.y / m_cellSize);
    if (j < 0 || j >= m_width) return nullptr;
    return GetNode(i, j);
}

NodeMap::~NodeMap()
{
    if (m_nodes)
    {
        for (int i = 0; i < m_width * m_height; i++)
        {
            delete m_nodes[i];
        }
        delete[] m_nodes;
    }
}

void  NodeMap::Initialise(std::vector<std::string> asciiMap, const float cellSize)
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
                    node->ConnectTo(nodeWest, glm::distance(node->position, nodeWest->position));
                    nodeWest->ConnectTo(node, glm::distance(node->position, nodeWest->position));
                }

                // see if there's a node south of us, checking for array index
                // overruns again
                Node* nodeSouth = y == 0 ? nullptr : GetNode(x, y - 1);
                if (nodeSouth)
                {
                    node->ConnectTo(nodeSouth, glm::distance(node->position, nodeSouth->position));
                    nodeSouth->ConnectTo(node, glm::distance(node->position, nodeSouth->position));
                }
            }
        }
    }
}

void NodeMap::Draw()
{
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            Node* node = GetNode(x, y);
            if (node == nullptr)
            {
                // draw a solid block in empty squares without a navigation node
                DrawRectangleV({ x * m_cellSize, y * m_cellSize },
                    { m_cellSize - 1, m_cellSize - 1 }, DARKGREEN);
            }
            else
            {
                // draw the connections between the node and its neighbours
                for (size_t i = 0; i < node->connections.size(); i++) {
                    Node* other = node->connections[i].target;
                    DrawLineV({ ((x + 0.5f) * m_cellSize), ((y + 0.5f) * m_cellSize) },
                        { other->position.x, other->position.y }, BLACK);
                }
            }
        }
    }
}

Node* NodeMap::GetRandomNode()
{
    Node* node = nullptr;
    while (node == nullptr)
    {
        int x = rand() % m_width;
        int y = rand() % m_height;
        node = GetNode(x, y);
    }
    return node;
}

float NodeMap::GetCellSize()
{
    return m_cellSize;
}
