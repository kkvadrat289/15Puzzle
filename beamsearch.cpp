#include "beamsearch.h"

#define MAX_STEPS 81

namespace Puzzle15 {

BeamSearch::BeamSearch(const State &initial, const size_t w): width(w), numOfOpenedStates(0){
    frontStates.push_back(std::make_shared<const State> (initial));
}

int BeamSearch::FindPath(){
    if (!frontStates.back()->IsSolvable()){
        std::cout << "Not solvable" << std::endl;
        return -1;
    }
    int steps = 0;
    while (frontStates.size() > 0 && steps < MAX_STEPS){
        ++steps;
        for (auto frontState : frontStates){
            ++numOfOpenedStates;
            if (frontState->IsTerminal()){
                std::shared_ptr<const State> current = frontState;
                std::vector<std::shared_ptr<const State> > path;
                path.push_back(current);
                while (current->GetParent() != nullptr){
                    current = current->GetParent();
                    path.push_back(current);
                }
                for (size_t i = path.size() - 1; i > 0; i--){
                    std::cout << path[i]->CalculateEuristic() << std::endl;
                    path[i]->Print();
                    std::cout << std::endl;
                }
                std::cout << path.begin()->get()->CalculateEuristic()<<std::endl;
                path.begin()->get()->Print();
                return steps;
            }
        }
        std::vector<std::shared_ptr<const State> > possibleFront;
        findPossibleFront(possibleFront);
        frontStates.clear();
        for (auto newFrontState: filterPossibleFront(possibleFront)){
            frontStates.push_back(newFrontState);
        }

    }
    return -1;
}

void BeamSearch::findPossibleFront(std::vector<std::shared_ptr<const State> > &possible) const{
    for (auto state: frontStates){
        std::vector<std::shared_ptr<State> > successors;
        state->GetSuccessors(successors);
        for (auto child : successors){
            possible.push_back(child);
        }
    }
}

std::vector<std::shared_ptr<const State> > BeamSearch::filterPossibleFront(std::vector<std::shared_ptr<const State> > &possible){
    std::vector<std::pair<int, int> > distances;
    std::vector<std::shared_ptr<const State> > newFront;
    for (size_t i = 0; i < possible.size(); i++){
        distances.push_back(std::make_pair(possible[i]->CalculateEuristic(), i));
    }
    std::sort(distances.begin(), distances.end());
    for (size_t i = 0; i < std::min(width, possible.size()); i++){
        newFront.push_back(possible[distances[i].second]);
    }
    return newFront;
}

int BeamSearch::GetNumOfOpenedStates() const{
    return numOfOpenedStates;
}


}
