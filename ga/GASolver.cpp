//
// Created by Giacomo Manzoli on 25/11/16.
//

#include "GASolver.h"
#include "Population.h"
#include <iostream>

using namespace std;


GASolver::GASolver(Problem *problem) {
    this->problem = problem;
}


Solution *GASolver::solve() {
    // Crea la popolazione (insieme di soluzioni, dimensione della popolazione)
    Population* population = new Population(2, problem);

    Solution** parents = population->extract(2);
    Solution* s3 = population->crossover(parents[0], parents[1]);
    //cout << "Parent 1" << endl;
    //parents[0]->printPath();
    //cout << "Parent 2" << endl;
    //parents[1]->printPath();
    //cout << "Offspring" <<endl;
    //s3->printPath();
    return s3;
    // Itera fino a che vengono trovate soluzioni migliori
}


