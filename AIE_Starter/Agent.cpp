//#include "Agent.h"
//
//void Agent::Update(float deltaTime)
//{
//    if (m_current)
//        m_current->Update(this, deltaTime);
//    m_pathAgent.Update(deltaTime);
//}
//
//void Agent::Draw()
//{
//    m_pathAgent.Draw();
//}
//
//void Agent::GoTo(glm::vec2 point)
//{
//    Node* end = m_nodeMap->GetClosestNode(point);
//    m_pathAgent.GoToNode(end);
//}
//
//void Agent::SetNode(Node* node)
//{
//    m_pathAgent.SetNode(node);
//}
//
//std::vector<Node*> Agent::GetPath()
//{
//    return m_pathAgent.m_path;
//}