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
#include "ThinkingBehaviour.h"
#include "FiniteStateMachine.h"
#include "DistanceCondition.h"
#include "TimerCondition.h"

#include "Adaptor.h"
#include "Selector.h"
#include "Sequence.h"
#include "TreeWanderBehaviour.h"
#include "TreeFollowBehaviour.h"
#include "TreeThinkingBehaviour.h"
#include "TreeDistanceCondition.h"
#include "TreeTimerCondition.h"
#include "TimeStart.h"
#include "TimeStop.h"

#include <string>

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "pathfinding and behaviours");

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Map

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
    asciiMap.push_back("0000000000000000000000000");
    nodeMap.Initialise(asciiMap,32);

    Node* start = nodeMap.GetNode(1, 1);
    Node* end = nodeMap.GetNode(10, 2);
    std::vector<Node*> nodeMapPath = AStarSearch(start, end);

    //// Conditions
    //DistanceCondition* closerThan5 = new DistanceCondition(5.0f * nodeMap.GetCellSize(), true);
    //DistanceCondition* closerThan5ex = new DistanceCondition(5.0f * nodeMap.GetCellSize(), true);
    //DistanceCondition* furtherThan7 = new DistanceCondition(7.0f * nodeMap.GetCellSize(), false);
    //TimerCondition* timecond = new TimerCondition(2.0f);


    //// States
    //State* wanderState = new State(new WanderBehaviour());
    //State* followState = new State(new FollowBehaviour());
    //State* thinkingState = new State(new ThinkingBehaviour());
    //thinkingState->AddTransition(timecond, wanderState);
    //thinkingState->AddTransition(closerThan5, followState);
    //wanderState->AddTransition(closerThan5ex, followState);
    //followState->AddTransition(furtherThan7, thinkingState);

    //// State Machine
    //FiniteStateMachine* fsm = new FiniteStateMachine(wanderState);
    //fsm->AddState(wanderState);
    //fsm->AddState(followState);
    //fsm->AddState(thinkingState);

    // Behaviour Tree
    TreeDistanceCondition* Tree_closerThan5 = new TreeDistanceCondition(5.0f * nodeMap.GetCellSize(), true);
    TreeDistanceCondition* Tree_furtherThan7 = new TreeDistanceCondition(7.0f * nodeMap.GetCellSize(), false);
    TreeTimerCondition* Tree_timecond = new TreeTimerCondition(2.0f);

    TreeWanderBehaviour* wanderBehave = new TreeWanderBehaviour();
    TreeFollowBehaviour* followBehave = new TreeFollowBehaviour();
    TreeThinkingBehaviour* thinkBehave = new TreeThinkingBehaviour();
    TimeStart* timerStart = new TimeStart();
    TimeStop* timerStop = new TimeStop();

    Sequence* Branch_follow = new Sequence({ Tree_closerThan5, timerStop,followBehave });
    Sequence* Branch_think = new Sequence({ Tree_furtherThan7, Tree_timecond, timerStart, thinkBehave });
    Sequence* Branch_wander = new Sequence({ wanderBehave });

    Selector* TheTree = new Selector({Branch_follow,Branch_think,Branch_wander});

    Adaptor* TheDaptor = new Adaptor(TheTree);

    // Agents
    Agent agent1(&nodeMap, new GotoPointBehaviour(), BROWN, "Frank");
    agent1.SetNode(start);
    agent1.SetSpeed(500);

    Agent agent2(&nodeMap, new WanderBehaviour(), ORANGE, "George");
    agent2.SetNode(nodeMap.GetRandomNode());
    agent2.SetSpeed(300);

    Agent agent3(&nodeMap, TheDaptor, PINK, "Bob");
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
        DrawPath(agent1.GetPath(), YELLOW);
        DrawPath(agent2.GetPath(), ORANGE);
        DrawPath(agent3.GetPath(), RED);
        agent1.Update(deltaTime);
        agent1.Draw();
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