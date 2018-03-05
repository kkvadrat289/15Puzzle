#pragma once
#include "state.h"
#include <iostream>
#include <algorithm>

namespace Puzzle15 {

class BeamSearch
{
public:
    BeamSearch(const State &initial, const size_t width);
    int FindPath();
    int GetNumOfOpenedStates() const;
private:
    void findPossibleFront(std::vector<std::shared_ptr<const State> > &possible) const;
    std::vector<std::shared_ptr<const State> > filterPossibleFront(std::vector<std::shared_ptr<const State> > &posiible);

    std::vector<std::shared_ptr<const State> > frontStates;
    const size_t width;
    int numOfOpenedStates;
};

}

