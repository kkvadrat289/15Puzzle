#include <iostream>
#include "state.h"
#include "beamsearch.h"
#include "astar.h"

#define WIDTH 1000

using namespace Puzzle15;
void Process(const std::vector<int> &vec){
    std::cout<< std::endl;
    State st(vec);
    BeamSearch s(st, WIDTH);
    auto path_bs = s.FindPath();

    std::cout << "Beam search:" << std::endl;
    std::cout << "\tSteps: " << path_bs.size() <<std::endl;
    std::cout << "\tOpened states: " << s.GetNumOfOpenedStates() <<std::endl;

    AStar as(vec);
    auto path_as = as.FindPath();
    std::cout << "A Star:" << std::endl;
    std::cout << "\tSteps: " << path_as.size() <<std::endl;
    std::cout << "\tOpened states: " << as.GetNumOfOpenedStates() <<std::endl;
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


   /*int arr[BOARD_SIZE] = {1,2,3,4,5,6,7,8,9,15,0,11,13,10,14,12};
    int term[BOARD_SIZE] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};
    State st(arr, 0);

    //std::cout << st.IsSolvable() <<std::endl;
    AStar s(st);
    //s.FindPath();
    auto path = s.FindPath();
    std::cout << "Steps: " << path.size() <<std::endl;
    std::cout << "Opened states: " << s.GetNumOfOpenedStates() <<std::endl;
    int a = 0;*/
    return 0;
}
