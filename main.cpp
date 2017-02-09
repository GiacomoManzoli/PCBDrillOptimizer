#include <iostream>
#include "cplex/CPLEXSolver.h"
#include "ga/GASolver.h"


using namespace std;



int main() {
    cout << "######################################"<<endl;
    int size = 5;
    Problem* problem = new Problem(size);
    cout << "Problema: N = " <<size<<endl;
    problem->printCosts();



    cout << "######################################"<<endl;
    cout << "Risolvo con CPLEX" <<endl;
    CPLEXSolver* cplexSolver = new CPLEXSolver(problem);
    Solution* cplexSol = cplexSolver->solve();

    cout << "--------------------------------------"<<endl;
    cout << "Risolvo con GA" <<endl;
    GASolver* gaSolver = new GASolver(problem, 50, 3, 0.05, 2);
    Solution* gaSol = gaSolver->solve();

    cout << "######################################"<<endl;
    cout << "Soluzione di CPLEX - Costo "<<cplexSol->getFitness() <<endl;
    cplexSol->printPath();
    cout << "--------------------------------------"<<endl;
    cout << "Soluzione di GA - Costo "<<gaSol->getFitness() <<endl;
    gaSol->printPath();
    cout << "--------------------------------------" <<endl;
    cout << "Gap dall'ottimo: " << (1-(gaSol->getFitness() / cplexSol->getFitness()))*100 <<"%"<<endl;

    return 0;
}