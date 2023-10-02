#ifndef ASTAR
#define ASTAR

#include <queue>
#include "State.h"

struct compare
{
public:
    bool operator() (State* left, State* right)
    {
        return left->getCost() > right->getCost();
    }
};

class AStar
{
private:
    State *state;
    State *goal;
    std::priority_queue<State*, std::vector<State*>, compare> pqueue;
    std::vector<State*> visited;

public:
    AStar(State *input);
    AStar(State *input, State *goal);
    ~AStar();
    void search(int heuristic);
    bool UCS(); //for UCS
    bool AS(int heuristic); //for A*
    void add_childs_to_pqueue(); //for UCS
    void add_childs_to_pqueue_AS(int heuristic); //for A*
    void print_from_child(State* child);

    void printState();
    void printGoal();
};

#endif