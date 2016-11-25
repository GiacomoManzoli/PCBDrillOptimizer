#include <iostream>

#include "common/Problem.h"
#include "ga/GASolver.h"

using namespace std;

int main() {
    srand(time(NULL));
    std::cout << "Hello, World!" << std::endl;

    // Carica i dati
    Problem* problem = new Problem(10);
    problem->printCosts();

    GASolver* solver = new GASolver(problem);
    solver->solve();


    return 0;
}