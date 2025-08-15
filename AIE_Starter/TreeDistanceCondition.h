#pragma once
#include "TreeBehaviour.h"


class TreeDistanceCondition : public TreeBehaviour
{
private:
    float m_distance;
    bool m_lessThan;

public:
    TreeDistanceCondition(float d, bool lt) : m_distance(d), m_lessThan(lt) {}
    virtual bool Update(Agent* agent, float deltaTime);
};