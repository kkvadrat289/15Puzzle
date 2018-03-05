#pragma once
#include "state.h"
#include <iostream>
#include <map>

namespace Puzzle15 {

class AStar
{
public:
    AStar(const State &init);
    std::vector<std::shared_ptr<const State> > FindPath();
    int GetNumOfOpenedStates() const;
private:
    std::multimap<int, std::shared_ptr<const State> > opened;
    std::vector<std::shared_ptr<const State> > closed;

};

}
