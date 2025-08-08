/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#include "Pathfinding.h"
#include <string>

using namespace AIForGames;

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    NodeMap nodeMap;
    std::vector<std::string> asciiMap;
    asciiMap.push_back("0000000000000000000000000");
    asciiMap.push_back("0101110111000111000001110");
    asciiMap.push_back("0101011101110001111111010");
    asciiMap.push_back("0101000100000000010001000");
    asciiMap.push_back("0101111111111111010001110");
    asciiMap.push_back("0100100010000000011111010");
    asciiMap.push_back("0111111111111110001001010");
    asciiMap.push_back("0010010000000010000001000");
    asciiMap.push_back("0111111111111011111111010");
    asciiMap.push_back("0010000010001000000001010");
    asciiMap.push_back("0111000011101111111101110");
    asciiMap.push_back("0101111000100100000100010");
    asciiMap.push_back("0100101111111111111111110");
    asciiMap.push_back("0000000000000000000000000");
    nodeMap.Initialise(asciiMap,32);

    Node* start = nodeMap.GetNode(1, 1);
    Node* end = nodeMap.GetNode(10, 2);
    //std::vector<Node*> nodeMapPath = dijkstrasSearch(start, end);
    std::vector<Node*> nodeMapPath = AStarSearch(start, end);

    PathAgent agent;
    agent.SetNode(start);
    agent.SetSpeed(500);

    float time = (float)GetTime();
    float deltaTime;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        float fTime = (float)GetTime();
        deltaTime = fTime - time;
        time = fTime;

        agent.Update(deltaTime);

        if (IsMouseButtonPressed(0))
        {
            Vector2 mousePos = GetMousePosition();
            Node* end = nodeMap.GetClosestNode(glm::vec2(mousePos.x, mousePos.y));
            agent.GoToNode(end);
        }
        //if (IsMouseButtonPressed(1))
        //{
        //    Vector2 mousePos = GetMousePosition();
        //    end = nodeMap.GetClosestNode(glm::vec2(mousePos.x, mousePos.y));
        //    nodeMapPath = dijkstrasSearch(start, end);
        //}
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(LIGHTGRAY);

        nodeMap.Draw();
        DrawPath(agent.m_path, YELLOW);
        agent.Draw();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}