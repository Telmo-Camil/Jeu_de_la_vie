#include "headers/TestSimulation.hpp"
#include <iostream>

int main() {
    std::cout << "=== Test du Jeu de la Vie ===" << std::endl;
    
    std::vector<std::vector<bool>> initial = {
        {false, false, true, false, false},
        {false, true, true, false, false},
        {false, false, true, false, false},
        {false, false, false, false, false},
        {false, false, false, false, false}
    };
    
    std::vector<std::vector<bool>> expected = {
        {false, true, true, false, false},
        {false, true, true, true, false},
        {false, true, true, false, false},
        {false, false, false, false, false},
        {false, false, false, false, false}
    };
    
    if (TestSimulation::testerEtatApresIterations(initial, expected, 1)) {
        std::cout << "✅ TEST OK" << std::endl;
        return 0;
    } else {
        std::cout << "❌ TEST FAILED" << std::endl;
        return 1;
    }
}
