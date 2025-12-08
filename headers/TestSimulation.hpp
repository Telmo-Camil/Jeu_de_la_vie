#ifndef TESTSIMULATION_HPP
#define TESTSIMULATION_HPP

#include "Grille.hpp"
#include <vector>

class TestSimulation {
public:
    static bool testerEtatApresIterations(const std::vector<std::vector<bool>>& etatInitial,
                                          const std::vector<std::vector<bool>>& etatAttendu,
                                          int iterations);
};

#endif
