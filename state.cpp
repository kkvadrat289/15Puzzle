#include "state.h"
#include <iostream>
#include <assert.h>
#include <cmath>

namespace Puzzle15 {

State::State(const int arr[], int dist) : distance(dist)
{
    for (size_t i = 0; i < BOARD_SIZE; i++){
        config[i] = arr[i];
    }
}

State::State(const std::vector<int> &vec, int dist) : distance(dist){
    for (size_t i = 0; i < BOARD_SIZE; ++i){
        config[i] = vec[i];
    }
}

void State::SetParent(std::shared_ptr<const State> par){
    parent = par;
}

std::shared_ptr<const State> State::GetParent() const{
    return parent;
}

void State::Print() const{
    for (size_t i = 0; i < BOARD_SIZE; i++){
        std::cout << config[i] << '\t';
        if (i % SIDE == 3)
            std::cout << std::endl;
    }
}

int State::GetItem(const size_t index) const{
    return config[index];
}

void State::GetSuccessors(std::vector<std::shared_ptr<State> > &successors) const{
    size_t zeroPozition = 100;
    for  (size_t i = 0; i < BOARD_SIZE; i++){
        if (config[i] == 0){
            zeroPozition = i;
            break;
        }
    }
    assert(zeroPozition < BOARD_SIZE);
    //move up
    if (zeroPozition > 3){
        int arr[BOARD_SIZE];
        CopyAndSwapItems(arr, zeroPozition, zeroPozition - SIDE);
        if (parent == nullptr || (parent != nullptr && !(parent->Equals(arr))))
            successors.push_back(std::make_shared<State>(arr, distance + 1));

    }
    //move down
    if (zeroPozition < 12){
        int arr[BOARD_SIZE];
        CopyAndSwapItems(arr, zeroPozition, zeroPozition + SIDE);
        if (parent == nullptr || (parent != nullptr && !(parent->Equals(arr))))
            successors.push_back(std::make_shared<State>(arr, distance + 1));

    }
    //move right
    if (zeroPozition % SIDE != 3){
        int arr[BOARD_SIZE];
        CopyAndSwapItems(arr, zeroPozition, zeroPozition + 1);
        if (parent == nullptr || (parent != nullptr && !(parent->Equals(arr))))
            successors.push_back(std::make_shared<State>(arr, distance + 1));

    }
    //move left
    if (zeroPozition % SIDE != 0){
        int arr[BOARD_SIZE];
        CopyAndSwapItems(arr, zeroPozition, zeroPozition - 1);
        if (parent == nullptr || (parent != nullptr && !(parent->Equals(arr))))
            successors.push_back(std::make_shared<State>(arr, distance + 1));

    }
    std::shared_ptr<const State> par = std::make_shared<const State> (*this);
    for (auto child : successors){
        child->SetParent(par);
    }

}

bool State::Equals(const int *arr) const{
    for (int i = 0; i < BOARD_SIZE; ++i){
        if (config[i] != arr[i]){
            return false;
        }
    }
    return true;
}

bool State::Equals(std::shared_ptr<State> &other) const{
    for (int i = 0; i < BOARD_SIZE; ++i){
        if (config[i] != other->GetItem(i)){
            return false;
        }
    }
    return true;
}


void State::CopyAndSwapItems(int* arr,const size_t first, const size_t second) const{

    for(size_t i = 0; i < BOARD_SIZE; i++){
        arr[i] = config[i];
    }
    int temp = arr[first];
    arr[first] = arr[second];
    arr[second] = temp;
}

int State::ManhattanDist() const{
    int dist = 0;
    for (int i = 0; i < BOARD_SIZE; i++){
        if (config[i] == 0){
            dist += 6 - i / SIDE - i % SIDE;
        }
        else if (config[i] != i - 1){
            int line = (config[i] - 1) / SIDE;
            int row = (config[i] - 1) % SIDE;
            dist += abs(line - i / SIDE) + abs(row - i % SIDE);
        }
    }
    return dist;
}

int State::LinearConflict() const{
    int dist = 0;
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 1; j + i % SIDE < SIDE; j++){
            bool zero = false;
            if (config[i] == 0 || config [i + j] == 0 ){
                zero = true;
            }
            if ( ((config[i] - 1) / SIDE == i / SIDE ) &&
                 ((config[i + j] - 1) / SIDE == (i + j) / SIDE) &&
                 (i / SIDE == (i + j) / SIDE) &&
                 config[i] > config[i + j] &&
                 !zero){
                dist += 2;
            }
        }
        for (int j = 1; i / SIDE + j < SIDE; j++){
            bool zero = false;
            if (config[i] == 0 || config[i + SIDE * j] == 0){
                zero = true;
            }
            if ( ((config[i] - 1) % SIDE == i % SIDE) &&
                 ((config[i + SIDE * j] - 1) % SIDE == (i + SIDE * j) % SIDE) &&
                 (i % SIDE == (i + SIDE * j) % SIDE) &&
                 (config[i] > config[i + SIDE * j]) &&
                 !zero){
                dist += 2;
            }
        }
    }
    return dist;
}

int State::CalculateEuristic() const{
    //std::cout << ManhattanDist() << " + " << LinearConflict() << std::endl;
    return ManhattanDist() + LinearConflict() + CornerConflict() + distance;
}

bool State::IsTerminal() const{
    for (int i = 0; i < BOARD_SIZE; i++){
        if ((i == 15 && config[i] != 0) || (i != 15 && config[i] != i + 1)){
            return false;
        }
    }
    return true;
}

bool State::IsSolvable() const{
    size_t zeroLine = 0;
    int inversions = 0;
    for (size_t i = 0; i < BOARD_SIZE; i++){
        for (size_t j = i + 1; j < BOARD_SIZE; ++j){
            if (config[j] < config[i]){
                ++inversions;
            }
        }
        if (config[i] == 0){
            zeroLine = i / 4 + 1;
        }
    }
    if ((zeroLine + inversions) % 2){
        return false;
    }
    return true;
}


std::vector<int> GenerateRandomState(const int a){
    auto rng = std::default_random_engine {};
    std::vector<int> vec(16);
    std::iota(vec.begin(), vec.end(), 0);
    for (int i = 0; i < a; ++i){
        std::shuffle(std::begin(vec), std::end(vec), rng);
    }
    return vec;
}

int State::CornerConflict() const{
    int dist = 0;
    if (config[0] != 1 && (config[1] == 2 || config[4] == 5)){
        dist += 2;
    }
    if (config[3] != 4 && (config[2] == 3 || config[7] == 8)){
        dist += 2;
    }
    if (config[12] != 13 && (config[8] == 9 || config[13] == 14)){
        dist += 2;
    }
    return dist;
}

void State::SetDistance(int dist){
    distance = dist;
}

int State::GetDistance() const{
    return distance;
}

}

