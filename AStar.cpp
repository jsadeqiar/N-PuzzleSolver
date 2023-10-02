#include "AStar.h"

AStar::AStar(State *input)
{
    this->state = input;
    this->goal = new State(input->getSize());
    this->pqueue.push(input);
}

AStar::AStar(State *input, State *goal)
{
    this->state = input;
    this->goal = goal;
    this->pqueue.push(input);
}

AStar::~AStar()
{
    delete this->state;
    delete this->goal;
}

void AStar::search(int heuristic)
{
    switch(heuristic)
    {
        case 1:
            this->UCS();
            break;
        case 2:
            this->AS(heuristic);
            break;
        case 3:
            this->AS(heuristic);
            break;
        default:
            std::cout << "Not a valid option!";
            exit(1);
            break;
    }

    return;
}

bool AStar::AS(int heuristic)
{
    if(this->pqueue.empty())
        return false;
    
    State *tmp = this->pqueue.top(); // SET INITIAL H_COST FOR FIRST STATE.
    if(heuristic == 2 && tmp->getDepth() == 0)
        tmp->sethCost(tmp->misplacedTile());
    if(heuristic == 3 && tmp->getDepth() == 0)
        tmp->sethCost(tmp->euclideanDist());

    int num_iter = 0;
    int pqueue_max_size = 0;
    while(!this->pqueue.empty())
    {
        if(pqueue_max_size < this->pqueue.size())
            pqueue_max_size = this->pqueue.size();

        std::cout << num_iter++ << " iterations\r";
        if(this->pqueue.top()->getState() == this->goal->getState())
        {
            this->print_from_child(this->pqueue.top());
            std::cout << "Solution found in " << num_iter << " search iterations at depth " << pqueue.top()->getDepth() << ":\n";
            std::cout << "Max size of Frontier: " << pqueue_max_size << "\n";
            return true;
        }
        this->add_childs_to_pqueue_AS(heuristic);
    }

    std::cout << "No solution found.\nNumber of Nodes expanded: "
    << num_iter << "\nMax size of Frontier: " << pqueue_max_size << "\n";
    return false;
}

bool AStar::UCS()
{
    if(this->pqueue.empty())
        return false;

    int num_iter = 0;   
    int pqueue_max_size = 0;
    while(!this->pqueue.empty())
    {
        if(pqueue_max_size < this->pqueue.size())
            pqueue_max_size = this->pqueue.size();
        num_iter++;
        if(this->pqueue.top()->getState() == this->goal->getState())
        {
            this->print_from_child(this->pqueue.top());
            std::cout << "Solution found in " << num_iter << " search iterations at depth " << pqueue.top()->getDepth() << ":\n";
            std::cout << "Max size of Frontier: " << pqueue_max_size << "\n";
            return true;
        }
        this->add_childs_to_pqueue();
    }

    std::cout << "No solution found.\nNumber of Nodes expanded: "
    << num_iter << "\nMax size of Frontier: " << pqueue_max_size << "\n";
    return false;
}

void AStar::add_childs_to_pqueue()
{
    State* top_of_queue = this->pqueue.top(); // stores the top of queue State
    this->pqueue.pop(); // pop the top State
    this->visited.push_back(top_of_queue); //visited node, push to visited vector.
    bool isVisited = false;
    
    std::vector<int> zero_cell = top_of_queue->blankLocation();
    int x = zero_cell[0]; int y = zero_cell[1]; // store blank cell location into x, y

    // check each 4 directions you can move the blank cell, if it's a valid move:
    // 1) create new temp State with the same size
    // 2) depth + 1
    // 3) cost + 1
    // 4) top_of_queue set as parent
    // 5) swap the blankn with its respective check
    // 6) push the child into pqueue.
    if(x - 1 >= 0)
    {
        //std::cout << "LEFT\n";
        isVisited = false;
        State* tmp = new State(top_of_queue->getSize(),
                           top_of_queue->getDepth() + 1,
                           top_of_queue->getCost() + 1,
                           top_of_queue,
                           top_of_queue->getState());
        tmp->swap(x, y, x - 1, y);
        
        for(int i = 0; i < this->visited.size(); i++)
        {
            if(tmp->getState() == visited[i]->getState())
            {
                delete tmp;
                isVisited = !isVisited;
                break;
            }
        }
        
        if(!isVisited)
            this->pqueue.push(tmp);
    }

    if(x + 1 <= top_of_queue->getSize() - 1)
    {
        //std::cout << "RIGHT\n";
        isVisited = false;
        State* tmp = new State(top_of_queue->getSize(),
                           top_of_queue->getDepth() + 1,
                           top_of_queue->getCost() + 1,
                           top_of_queue,
                           top_of_queue->getState());
        tmp->swap(x, y, x + 1, y);

        for(int i = 0; i < this->visited.size(); i++)
        {
            if(tmp->getState() == visited[i]->getState())
            {
                delete tmp;
                isVisited = !isVisited;
                break;
            }
        }

        if(!isVisited)
            this->pqueue.push(tmp);
    }

    if(y - 1 >= 0)
    {
        //std::cout << "DOWN\n";
        isVisited = false;
        State* tmp = new State(top_of_queue->getSize(),
                           top_of_queue->getDepth() + 1,
                           top_of_queue->getCost() + 1,
                           top_of_queue,
                           top_of_queue->getState());
        tmp->swap(x, y, x, y - 1);
        
        for(int i = 0; i < this->visited.size(); i++)
        {
            if(tmp->getState() == visited[i]->getState())
            {
                delete tmp;
                isVisited = !isVisited;
                break;
            }
        }

        if(!isVisited)
            this->pqueue.push(tmp);
    }

    if(y + 1 <= top_of_queue->getSize() - 1)
    {
        //std::cout << "UP\n";
        isVisited = false;
        State* tmp = new State(top_of_queue->getSize(),
                           top_of_queue->getDepth() + 1,
                           top_of_queue->getCost() + 1,
                           top_of_queue,
                           top_of_queue->getState());
        tmp->swap(x, y, x, y + 1);
        
        for(int i = 0; i < this->visited.size(); i++)
        {
            if(tmp->getState() == visited[i]->getState())
            {
                delete tmp;
                isVisited = !isVisited;
                break;
            }
        }

        if(!isVisited)
            this->pqueue.push(tmp);
    }

    return;
}

void AStar::add_childs_to_pqueue_AS(int heuristic)
{
    State* top_of_queue = this->pqueue.top(); // stores the top of queue State
    this->pqueue.pop(); // pop the top State
    this->visited.push_back(top_of_queue); //visited node, push to visited vector.
    bool isVisited = false;

    //std::cout << top_of_queue->getDepth() << " " << top_of_queue->gethCost() << " = " << top_of_queue->getCost() << "\n";
    
    std::vector<int> zero_cell = top_of_queue->blankLocation();
    int x = zero_cell[0]; int y = zero_cell[1]; // store blank cell location into x, y

    if(x - 1 >= 0)
    {
        //std::cout << "LEFT\n";
        isVisited = false;
        State* tmp = new State(top_of_queue->getSize(),
                           top_of_queue->getDepth() + 1,
                           top_of_queue->getDepth() + 1,
                           top_of_queue,
                           top_of_queue->getState());
        tmp->swap(x, y, x - 1, y);
        
        for(int i = 0; i < this->visited.size(); i++)
        {
            if(tmp->getState() == visited[i]->getState())
            {
                delete tmp;
                isVisited = !isVisited;
                break;
            }
        }
        if(heuristic == 2 && !isVisited)
            tmp->sethCost(tmp->misplacedTile());
        if(heuristic == 3 && !isVisited)
            tmp->sethCost(tmp->euclideanDist());
        if(!isVisited)
            this->pqueue.push(tmp);
    }

    if(x + 1 <= top_of_queue->getSize() - 1)
    {
        //std::cout << "RIGHT\n";
        isVisited = false;
        State* tmp = new State(top_of_queue->getSize(),
                           top_of_queue->getDepth() + 1,
                           top_of_queue->getDepth() + 1,
                           top_of_queue,
                           top_of_queue->getState());
        tmp->swap(x, y, x + 1, y);

        for(int i = 0; i < this->visited.size(); i++)
        {
            if(tmp->getState() == visited[i]->getState())
            {
                delete tmp;
                isVisited = !isVisited;
                break;
            }
        }
        if(heuristic == 2 && !isVisited)
            tmp->sethCost(tmp->misplacedTile());
        if(heuristic == 3 && !isVisited)
            tmp->sethCost(tmp->euclideanDist());
        if(!isVisited)
            this->pqueue.push(tmp);
    }

    if(y - 1 >= 0)
    {
        //std::cout << "DOWN\n";
        isVisited = false;
        State* tmp = new State(top_of_queue->getSize(),
                           top_of_queue->getDepth() + 1,
                           top_of_queue->getDepth() + 1,
                           top_of_queue,
                           top_of_queue->getState());
        tmp->swap(x, y, x, y - 1);
        
        for(int i = 0; i < this->visited.size(); i++)
        {
            if(tmp->getState() == visited[i]->getState())
            {
                delete tmp;
                isVisited = !isVisited;
                break;
            }
        }
        if(heuristic == 2 && !isVisited)
            tmp->sethCost(tmp->misplacedTile());
        if(heuristic == 3 && !isVisited)
            tmp->sethCost(tmp->euclideanDist());
        if(!isVisited)
            this->pqueue.push(tmp);
    }

    if(y + 1 <= top_of_queue->getSize() - 1)
    {
        //std::cout << "UP\n";
        isVisited = false;
        State* tmp = new State(top_of_queue->getSize(),
                           top_of_queue->getDepth() + 1,
                           top_of_queue->getDepth() + 1,
                           top_of_queue,
                           top_of_queue->getState());
        tmp->swap(x, y, x, y + 1);
        
        for(int i = 0; i < this->visited.size(); i++)
        {
            if(tmp->getState() == visited[i]->getState())
            {
                delete tmp;
                isVisited = !isVisited;
                break;
            }
        }
        if(heuristic == 2 && !isVisited)
            tmp->sethCost(tmp->misplacedTile());
        if(heuristic == 3 && !isVisited)
            tmp->sethCost(tmp->euclideanDist());
        if(!isVisited)
            this->pqueue.push(tmp);
    }

    return;
}

void AStar::print_from_child(State* child)
{
    if(child->getParent() != NULL)
    {
        this->print_from_child(child->getParent());
        child->printState();
    }
    else
        child->printState();
    return;
}

void AStar::printState()
{
    std::cout << "PRINTING CURRENT STATE BOARD\n";
    this->state->printState();
}

void AStar::printGoal()
{
    std::cout << "PRINTING GOAL BOARD\n";
    this->goal->printState();
}