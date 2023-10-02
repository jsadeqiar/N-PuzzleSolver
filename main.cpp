#include <iostream>
#include "AStar.h"
#include "State.h"
#include <cmath>

int main(int argc, char* argv[])
{
    int puzzle_size, heuristic;
    std::cout << "Welcome to my N-Puzzle Solver (SID: 862217055)\n";
    std::cout << "NOTE: 0 represents empty cell\n";
    std::cout << "Enter the size of your puzzle (ex: enter 3 for a 3x3)\n";
    std::cin >> puzzle_size;
    std::vector<std::vector<int>> input(puzzle_size, std::vector<int>(puzzle_size));
    std::cout << "\nEnter the " << std::pow(puzzle_size, 2.0) << " puzzle spaces, space separated. (e.g. 1 8 2 0 4 3 7 6 5).\n";

    for(int i = 0; i < puzzle_size; i++)
    {
        for(int j = 0; j < puzzle_size; j++)
        {
            std::cin >> input[i][j];
        }
    }

    std::cout << "\nEnter the goal (" << std::pow(puzzle_size, 2.0) << " spaces)\n";

    std::vector<std::vector<int>> goal(puzzle_size, std::vector<int>(puzzle_size));

    for(int i = 0; i < puzzle_size; i++)
    {
        for(int j = 0; j < puzzle_size; j++)
        {
            std::cin >> goal[i][j];
        }
    }

    
    std::cout << "Select the search method:\n" <<
    "1 - Uniform Cost Search\n" <<
    "2 - A* with Misplaced Tile Heuristic\n" <<
    "3 - A* with euclidean Distance Heuristic\n";
    std::cin >> heuristic;

    //State *state = new State(input);
    //std::cout << state->euclideanDist() << "\n";

    State *state = new State(input);
    State *gstate = new State(goal);
    AStar *astar = new AStar(state, gstate);

    switch(heuristic)
    {
        case 1:
            astar->search(1);
            break;
        case 2:
            astar->search(2);
            break;
        case 3:
            astar->search(3);
            break;
        default:
            break;
    }

    //test->printState();
    //test->printGoal();

    return 0;
}        
