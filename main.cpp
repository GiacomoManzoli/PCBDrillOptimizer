#include <iostream>

#include "common/Problem.h"
#include "ga/GASolver.h"
#include "cplex/CPLEXSolver.h"


using namespace std;

int main() {
    srand(time(NULL));
    std::cout << "Hello, World!" << std::endl;

    // Carica i dati
    Problem* problem = new Problem(10);
    problem->printCosts();


    // GA
    GASolver* gaSolver = new GASolver(problem);
    Solution* sol2 = gaSolver->solve();
    //sol2->printPath();

    // CPLEX
    CPLEXSolver* solver = new CPLEXSolver(problem);
    Solution* sol1 = solver->solve();
    cout << "CPLEX: "<<endl;
    sol1->printPath();

    return 0;
}