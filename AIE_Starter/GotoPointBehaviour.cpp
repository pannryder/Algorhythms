#include "GotoPointBehaviour.h"

void GotoPointBehaviour::Update(Agent* agent, float deltaTime)
{
    if (IsMouseButtonPressed(0))
    {
        Vector2 mousePos = GetMousePosition();
        agent->GoTo(glm::vec2(mousePos.x, mousePos.y));
    }
}