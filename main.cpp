#include <iostream>
#include "state.h"

using namespace std;

int main()
{
    int arr[BOARD_SIZE] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};
    State state(arr);
    state.Print();
    std::vector<std::shared_ptr<State> > succ;
    state.GetSuccessors(succ);
    for (auto s : succ){
        std::cout << std::endl;
        s->Print();
    }
    return 0;
}
