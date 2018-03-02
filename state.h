#pragma once
#include <memory>
#include <vector>

#define BOARD_SIZE 16

int terminal[BOARD_SIZE] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};

class State
{
public:
    State(const int arr[BOARD_SIZE]);
    State(const State &state);
    void Print() const;
    void GetSuccessors(std::vector<std::shared_ptr<State> > &successors) const;
    void CopyAndSwapItems(int* arr, const size_t first, const size_t second) const;
    int CalculateEuristic() const;
    //Getters
    std::shared_ptr<State> GetParent() const;
    int GetItem(const size_t index) const;
private:
    int ManhattanDist() const;
    std::shared_ptr<State> parent;
    int config[BOARD_SIZE];
};

