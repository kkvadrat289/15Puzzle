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

/*State::State(const State &state){
    for (size_t i = 0; i < BOARD_SIZE; i++){
        config[i] = state.GetItem(i);
    }

}*/

void State::SetParent(std::shared_ptr<const State> par){
    parent = par;
}

std::shared_ptr<const State> State::GetParent() const{
    return parent;
}

void State::Print() const{
    for (size_t i = 0; i < BOARD_SIZE; i++){
        std::cout << config[i] << '\t';
        if (i % BOARD_SIDE == 3)
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
        CopyAndSwapItems(arr, zeroPozition, zeroPozition - BOARD_SIDE);
        successors.push_back(std::make_shared<State>(arr));

    }
    //move down
    if (zeroPozition < 12){
        int arr[BOARD_SIZE];
        CopyAndSwapItems(arr, zeroPozition, zeroPozition + BOARD_SIDE);
        successors.push_back(std::make_shared<State>(arr));
    }
    //move right
    if (zeroPozition % BOARD_SIDE != 3){
        int arr[BOARD_SIZE];
        CopyAndSwapItems(arr, zeroPozition, zeroPozition + 1);
        successors.push_back(std::make_shared<State>(arr));
    }
    //move left
    if (zeroPozition % BOARD_SIDE != 0){
        int arr[BOARD_SIZE];
        CopyAndSwapItems(arr, zeroPozition, zeroPozition - 1);
        successors.push_back(std::make_shared<State>(arr));
    }
    std::shared_ptr<const State> par = std::make_shared<const State> (*this);
    for (auto child : successors){
        child->SetParent(par);
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
    for (int i = 0; i < BOARD_SIZE; i++){
        if (config[i] == 0){
            dist += 6 - i / BOARD_SIDE - i % BOARD_SIDE;
        }
        else if (config[i] != i - 1){
            int line = (config[i] - 1) / BOARD_SIDE;
            int row = (config[i] - 1) % BOARD_SIDE;
            dist += abs(line - i / BOARD_SIDE) + abs(row - i % BOARD_SIDE);
        }
    }
    return dist;
}

int State::LinearConflict() const{
    int dist = 0;
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 1; j + i % BOARD_SIDE < BOARD_SIDE; j++){
            bool zero = false;
            if (config[i] == 0 || config [i + j] == 0 ){
                zero = true;
            }
            if ( ((config[i] - 1) / BOARD_SIDE == i / BOARD_SIDE ) &&
                 ((config[i + j] - 1) / BOARD_SIDE == (i + j) / BOARD_SIDE) &&
                 (i / BOARD_SIDE == (i + j) / BOARD_SIDE) &&
                 config[i] > config[i + j] &&
                 !zero){
                dist += 2;
            }
        }
        for (int j = 1; i / BOARD_SIDE + j < BOARD_SIDE; j++){
            bool zero = false;
            if (config[i] == 0 || config[i + BOARD_SIDE * j] == 0){
                zero = true;
            }
            if ( ((config[i] - 1) % BOARD_SIDE == i % BOARD_SIDE) &&
                 ((config[i + BOARD_SIDE * j] - 1) % BOARD_SIDE == (i + BOARD_SIDE * j) % BOARD_SIDE) &&
                 (i % BOARD_SIDE == (i + BOARD_SIDE * j) % BOARD_SIDE) &&
                 (config[i] > config[i + BOARD_SIDE * j]) &&
                 !zero){
                dist += 2;
            }
        }
    }
    return dist;
}

int State::CalculateEuristic() const{
    std::cout << ManhattanDist() << " + " << LinearConflict() << std::endl;
    return ManhattanDist() + LinearConflict();
}

void BeamSearch(const size_t width){

}
