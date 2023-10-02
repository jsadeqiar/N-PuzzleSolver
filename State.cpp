#include "State.h"

State::State(int size)
{
    this->size = size;
    int count = 1;

    this->state.resize(size);
    for(int i = 0; i < size; i++)
    {
        this->state[i].resize(size);
        for(int j = 0; j < size; j++)
        {
            this->state[i][j] = count++;
        }
    }
    this->state[size-1][size-1] = 0;
    this->parent = NULL;

}

State::State(std::vector<std::vector<int>> input)
{
    this->state = input;
    this->size = input[0].size();
    this->depth = 0;
    this->hcost = 0;
    this->parent = NULL;
}

State::State(int size, int depth, int cost, State* parent, std::vector<std::vector<int>> state)
{
    this->size = size;
    this->depth = depth;
    //this->hcost = cost;
    this->parent = parent;
    this->state = state;
}

State::~State()
{
    this->state.clear();
}

void State::printState()
{
    std::cout << "g(n) = " << this->getDepth()
    << " and h(n) = " << this->gethCost() << "\n";
    for(int i = 0; i < this->size; i++)
    {
        for(int j = 0; j < this->size; j++)
        {
            std::cout << this->state[i][j] << " ";
        }
        std::cout << '\n';
    }
    std::cout << "==========\n";
    return;
}

void State::swap(int x, int y, int a, int b)
{
    int temp = this->state[x][y];
    this->state[x][y] = this->state[a][b];
    this->state[a][b] = temp;
    return;
}

int State::getSize()
{
    return this->size;
}

int State::getDepth()
{
    return this->depth;
}

int State::getCost()
{
    return this->depth + this->hcost;
}

int State::gethCost()
{
    return this->hcost;
}

State* State::getParent()
{
    return this->parent;
}

std::vector<std::vector<int>> State::getState()
{
    return this->state;
}

std::vector<int> State::blankLocation()
{
    std::vector<int> results;
    for(int i = 0; i < this->size; i++)
    {
        for(int j = 0; j < this->size; j++)
        {
            if(this->state[i][j] == 0)
            {
                results.push_back(i);
                results.push_back(j);
                return results;
            }
        }
    }
    results.push_back(-1);
    return results;
}

void State::setCost(int cost)
{
    this->depth = cost;
}

void State::setDepth(int depth)
{
    this->depth = depth;
}

void State::sethCost(int hcost)
{
    this->hcost = hcost;
}

void State::setParent(State *parent)
{
    this->parent = parent;
}

int State::misplacedTile()
{
    int result = 0;
    int count = 1;
    for(int i = 0; i < this->size; i++)
    {
        for(int j = 0; j < this->size; j++)
        {
            if(this->state[i][j] != count)
                result++;
            count++;
        }
    }
    //std::cout << result - 1 << "\n";
    return result - 1;
}

int State::euclideanDist()
{
    State *tmp = new State(this->getSize());

    double result = 0;
    int count = 1;
    for(int i = 0; i < this->size; i++)
    {
        for(int j = 0; j < this->size; j++)
        {
            if((this->state[i][j] != tmp->state[i][j]) || count == std::pow(this->getSize(), 2))
            {
                // count -> state[count / this->size][count % this->size - 1]
                // 8 goes to state[8/3 = 2] [8 % 3 - 1 = 1] -> state [2][1] correct.
                // i = row
                // j = col
                double dist;
                int tmp = this->state[i][j];
                int goalRow = tmp / this->getSize();
                int goalCol = tmp % this->getSize() - 1;
                double x = i - goalRow;
                double y = j - goalCol;
                dist = std::pow(x, 2) + std::pow(y, 2);
                dist = std::sqrt(dist);
                result += dist;
            }
            count++;
        }
    }
    //std::cout << result << "\n";
    return result;
}