#pragma once
#include <memory>
#include <vector>
#include <random>
#include <algorithm>

namespace Puzzle15 {

#define BOARD_SIZE 16
#define SIDE 4

//const int terminal[BOARD_SIZE] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};

class State
{
public:
    State(const int arr[BOARD_SIZE], int dist = 0);
    State(const std::vector<int> &vec, int dist = 0);
   // State(const State &state);
    void Print() const;
    void GetSuccessors(std::vector<std::shared_ptr<State> > &successors) const;
    void CopyAndSwapItems(int* arr, const size_t first, const size_t second) const;
    int CalculateEuristic() const;
    bool IsTerminal() const;
    bool IsSolvable() const;
    //Getters
    std::shared_ptr<const State> GetParent() const;
    int GetItem(const size_t index) const;
    //Setters
    void SetParent(std::shared_ptr<const State> par);
    bool Equals(const int* arr) const;
private:
    int ManhattanDist() const;
    int LinearConflict() const;
    int CornerConflict() const;
    std::shared_ptr<const State> parent;
    int config[BOARD_SIZE];
    int distance;
};

std::vector<int> GenerateRandomState(const int a);

}
