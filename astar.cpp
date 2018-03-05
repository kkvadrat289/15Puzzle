#include "astar.h"

namespace Puzzle15 {

AStar::AStar(const State &init)
{
    opened.insert(std::make_pair(init.CalculateEuristic(), std::make_shared<const State>(init)));
}

std::vector<std::shared_ptr<const State> > AStar::FindPath(){
    std::vector<std::shared_ptr<const State> > path;
    if (!(opened.begin()->second->IsSolvable())){
        std::cout << "Not Solvable!" <<std::endl;
        return path;
    }
    int steps = 0;

    while (opened.size() > 0){
        ++steps;
        std::cout << steps << std::endl;
        std::shared_ptr<const State> current = opened.begin()->second;

        if (current->IsTerminal()){
            steps = current->GetDistance() + 1;

            path.push_back(current);
            while (current->GetParent() != nullptr){
                current = current->GetParent();
                path.push_back(current);
            }
            /*for (size_t i = path.size() - 1; i > 0; i--){
                std::cout << path[i]->CalculateEuristic() << std::endl;
                path[i]->Print();
                std::cout << std::endl;
             }*/
            //std::cout << path.begin()->get()->CalculateEuristic()<<std::endl;
            //path.begin()->get()->Print();
            return path;
        }
        opened.erase(opened.begin());
        closed.push_back(current);
        std::vector<std::shared_ptr<State> > successors;
        current->GetSuccessors(successors);
        for (auto child : successors){
            bool alreadyClosed = false;
            for (auto v : closed){
                if (v->Equals(child)){
                    alreadyClosed = true;
                }
            }
            if (child->GetDistance() >= current->GetDistance() && alreadyClosed){
                continue;
            }
            if (!alreadyClosed || child->GetDistance() < current->GetDistance()){
                child->SetParent(current);
                child->SetDistance(current->GetDistance() + 1);
                bool flag = false;
               /* for (auto v : opened){
                    if (v.second->Equals(child)){flag = true;}
                }*/
                if (!flag){
                    opened.insert(std::make_pair(child->CalculateEuristic() + child->GetDistance(), child));
                }
            }
        }
    }
    return path;
}

int AStar::GetNumOfOpenedStates() const{
    return closed.size();
}

}

