#include "state.h"
#include <iostream>
#include <assert.h>
#include <cmath>

State::State(const int arr[])
{
    for (size_t i = 0; i < BOARD_SIZE; i++){
        config[i] = arr[i];
    }
}

State::State(const State &state){
    for (size_t i = 0; i < BOARD_SIZE; i++){
        config[i] = state.GetItem(i);
    }
    //parent is not copied
}

std::shared_ptr<State> State::GetParent() const{
    return parent;
}

void State::Print() const{
    for (size_t i = 0; i < BOARD_SIZE; i++){
        std::cout << config[i] << '\t';
        if (i % 4 == 3)
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
        CopyAndSwapItems(arr, zeroPozition, zeroPozition - 4);
        successors.push_back(std::make_shared<State>(arr));
    }
    //move down
    if (zeroPozition < 12){
        int arr[BOARD_SIZE];
        CopyAndSwapItems(arr, zeroPozition, zeroPozition + 4);
        successors.push_back(std::make_shared<State>(arr));
    }
    //move right
    if (zeroPozition % 4 != 3){
        int arr[BOARD_SIZE];
        CopyAndSwapItems(arr, zeroPozition, zeroPozition + 1);
        successors.push_back(std::make_shared<State>(arr));
    }
    //move left
    if (zeroPozition % 4 != 0){
        int arr[BOARD_SIZE];
        CopyAndSwapItems(arr, zeroPozition, zeroPozition - 1);
        successors.push_back(std::make_shared<State>(arr));
    }
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
    for (size_t i = 0; i < BOARD_SIZE; i++){
        if (config[i] != i - 1){
            int line = (config[i] - 1) / 4;
            int row = (config[i] - 1) % 4;
            dist += abs(line - i / 4) + abs(row - i % 4);
        }
    }
    return dist;
}


