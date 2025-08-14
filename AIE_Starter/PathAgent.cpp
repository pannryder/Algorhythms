#include "PathAgent.h"
#include "raylib.h"
#include "Pathfinding.h"

void PathAgent::Update(float deltaTime)
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

void PathAgent::GoToNode(Node* node)
{
    m_path = AStarSearch(m_currentNode, node);
    //m_path = dijkstrasSearch(m_currentNode, node);
    m_currentIndex = 0;
}

void PathAgent::SetNode(Node* node)
{
    if (node != nullptr) {
        m_currentNode = node;
        m_position = node->position;
    }
}

void PathAgent::SetSpeed(float speed)
{
    m_speed = speed;
}

void PathAgent::Draw()
{
    DrawCircleV({ m_position.x, m_position.y }, 8, m_color);
    DrawText(m_name.c_str(),((int)m_position.x-15),((int)m_position.y+10),10,m_color);
}

void PathAgent::SetColor(Color _color)
{
    m_color = _color;
}

void PathAgent::SetName(std::string _name)
{
    m_name = _name;
}

std::vector<Node*> PathAgent::GetPath()
{
    return m_path;
}

glm::vec2 PathAgent::GetPosition()
{
    return m_position;
}

void PathAgent::Reset()
{
    m_path.clear();
}

std::string PathAgent::GetName()
{
    return m_name;
}
