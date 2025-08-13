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
#include "NodeMap.h"
#include "Node.h"
#include "Agent.h"
#include "PathAgent.h"
#include "GotoPointBehaviour.h"
#include "WanderBehaviour.h"
#include "FollowBehaviour.h"
#include "SelectorBehaviour.h"
#include <string>

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
    asciiMap.push_back("0101011101110101111111010");
    asciiMap.push_back("0101000100000100010001010");
    asciiMap.push_back("0101111111111111010001110");
    asciiMap.push_back("0100100010000000011111010");
    asciiMap.push_back("0111111111111110001001010");
    asciiMap.push_back("0010010000000010001001000");
    asciiMap.push_back("0111111111111011111111010");
    asciiMap.push_back("0010000010001000010001010");
    asciiMap.push_back("0111000011101111111101110");
    asciiMap.push_back("0101111010100100000100010");
    asciiMap.push_back("0110101111111111111111110");
    asciiMap.push_back("0000000000000000000000000");
    nodeMap.Initialise(asciiMap,32);

    Node* start = nodeMap.GetNode(1, 1);
    Node* end = nodeMap.GetNode(10, 2);
    //std::vector<Node*> nodeMapPath = dijkstrasSearch(start, end);
    std::vector<Node*> nodeMapPath = AStarSearch(start, end);

    Agent agent(&nodeMap, new GotoPointBehaviour(), BROWN);
    agent.SetNode(start);
    agent.SetSpeed(500);

    Agent agent2(&nodeMap, new WanderBehaviour(), ORANGE);
    agent2.SetNode(nodeMap.GetRandomNode());
    agent2.SetSpeed(300);

    Agent agent3(&nodeMap, new SelectorBehaviour(new FollowBehaviour(), new WanderBehaviour()), PINK);
    agent3.SetNode(nodeMap.GetRandomNode());
    agent3.SetTarget(&agent2);
    agent3.SetSpeed(200);

    float time = (float)GetTime();
    float deltaTime;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Time
        //----------------------------------------------------------------------------------

        float fTime = (float)GetTime();
        deltaTime = fTime - time;
        time = fTime;

        // Draw & Update
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(LIGHTGRAY);

        nodeMap.Draw();
        DrawPath(agent.GetPath(), YELLOW);
        DrawPath(agent2.GetPath(), YELLOW);
        DrawPath(agent3.GetPath(), YELLOW);
        //DrawPath(agent.m_path, YELLOW);
        agent.Update(deltaTime);
        agent.Draw();
        agent2.Update(deltaTime);
        agent2.Draw();
        agent3.Update(deltaTime);
        agent3.Draw();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}