#ifndef STATE
#define STATE

#include <vector>
#include <iostream>
#include <math.h>
#include <cmath>

class State
{
private:
    std::vector<std::vector<int>> state;
    int size;
    int depth; //depth is essentially ncost. fcost = ncost + hcost.
    double hcost;
    State *parent;
public:
    State(int size);
    State(int size, int depth, int cost, State* parent, std::vector<std::vector<int>> state);
    State(std::vector<std::vector<int>> input);
    ~State();

    void printState();
    void swap(int x, int y, int a, int b);
    int misplacedTile();
    int euclideanDist();

    int getSize();
    int getDepth();
    int getCost();
    int gethCost();
    State* getParent();
    std::vector<std::vector<int>> getState();
    std::vector<int> blankLocation();

    void setDepth(int depth);
    void setCost(int cost);
    void sethCost(int hcost);
    void setParent(State *parent);

};

#endif