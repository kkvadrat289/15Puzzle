#include <iostream>
#include "state.h"

using namespace std;

int main()
{
    int arr[BOARD_SIZE] = {1,2,3,8,5,6,7,4,9,10,11,12,13,15,14,0};
    State state(arr);
    std::cout<<state.CalculateEuristic()<<std::endl;
    state.Print();
    std::vector<std::shared_ptr<State> > succ;
    std::vector<std::shared_ptr<State> > succ2;
    state.GetSuccessors(succ);
    for (auto s : succ){
        std::cout << std::endl;
        std::cout << s->CalculateEuristic()<<std::endl;
        s->Print();

        s->GetSuccessors(succ2);
        for (auto s2 : succ2){
            std::cout << s2->CalculateEuristic()<<std::endl;
            s2->Print();
        }

    }
    return 0;
}
