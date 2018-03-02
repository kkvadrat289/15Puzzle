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
            dist += 6 - i / 4 - i % 4;
        }
        else if (config[i] != i - 1){
            int line = (config[i] - 1) / 4;
            int row = (config[i] - 1) % 4;
            dist += abs(line - i / 4) + abs(row - i % 4);
        }
    }
    return dist;
}

int State::LinearConflict() const{
    int dist = 0;
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 1; j + i % 4 < 4; j++){
            bool zero = false;
            if (config[i] == 0 || config [i + j] == 0 ){
                zero = true;
            }
            if ( ((config[i] - 1) / 4 == i / 4 ) &&
                 ((config[i + j] - 1) / 4 == (i + j) / 4) &&
                 (i / 4 == (i + j) / 4) &&
                 config[i] > config[i + j] &&
                 !zero){
                dist += 2;
            }
        }
        for (int j = 1; i / 4 + j < 4; j++){
            bool zero = false;
            if (config[i] == 0 || config[i + 4 * j] == 0){
                zero = true;
            }
            if ( ((config[i] - 1) % 4 == i % 4) &&
                 ((config[i + 4 * j] - 1) % 4 == (i + 4 * j) % 4) &&
                 (i % 4 == (i + 4 * j) % 4) &&
                 (config[i] > config[i + 4 * j]) &&
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
