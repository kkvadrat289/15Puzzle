#include <iostream>
#include "state.h"
#include "beamsearch.h"

#define WIDTH 1000

using namespace Puzzle15;
void Process(const std::vector<int> &vec){
    std::cout<< std::endl;
    State st(vec);
    BeamSearch s(st, WIDTH);
    int steps = s.FindPath();
    std::cout << "Steps: " << steps <<std::endl;
    std::cout << "Opened states: " << s.GetNumOfOpenedStates() <<std::endl;
}

int main()
{



    int a;
    while (std::cin >> a){
        auto rng = std::default_random_engine {};
        std::vector<int> vec(16);
        std::iota(vec.begin(), vec.end(), 0);
        for (int i = 0; i < a; ++i){
            std::shuffle(std::begin(vec), std::end(vec), rng);
        }
        Process(vec);
   }
/*
    int arr[BOARD_SIZE] = {1,2,3,4,5,6,7,8,9,15,0,11,13,10,14,12};
    State st(arr, 0);
    std::cout << st.IsSolvable() <<std::endl;
    BeamSearch s(st, WIDTH);
    int steps = s.FindPath();
    std::cout << "Steps: " << steps <<std::endl;
    std::cout << "Opened states: " << s.GetNumOfOpenedStates() <<std::endl;
*/
    return 0;
}
