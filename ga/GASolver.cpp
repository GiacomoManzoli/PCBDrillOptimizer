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
    Population* population = new Population(100, problem);

    cout << "Popolazione iniziale:" <<endl;
    cout << "Worst: " <<population->getWorstSolution()->getFitness();
    cout << "\t Avg: " <<population->getAverageFitness();
    cout << "\t Best: " <<population->getBestSolution()->getFitness() << endl;

    cout << "Evoluzione in corso" <<endl;
    int i = 0;
    int consecutiveNotImproving = 0;

    //while (true){
    //    // Consecutive not improving non funziona bene (consectuive worstening invece non termina quasi mai)
    //    if (consecutiveNotImproving == 3){ break; }
    //    i++;
    //    double oldBest = population->getBestSolution()->getFitness();
    //    population->evolvePopulation();
    //    double newBest = population->getBestSolution()->getFitness();
//
    //    if (newBest > oldBest) { consecutiveNotImproving++;}
    //    else {consecutiveNotImproving = 0;}
    //}
    for (int j = 0; j < 1000; ++j) {
        population->evolvePopulation();
    }

    cout << endl;
    cout << "Popolazione finale dopo "<<i << " iterazioni" <<endl;
    cout << "Worst: " <<population->getWorstSolution()->getFitness();
    cout << "\t Avg: " <<population->getAverageFitness();
    cout << "\t Best: " <<population->getBestSolution()->getFitness() << endl;
    Solution* s3;
    //cout << "Parent 1" << endl;
    //parents[0]->printPath();
    //cout << "Parent 2" << endl;
    //parents[1]->printPath();
    //cout << "Offspring" <<endl;
    //s3->printPath();
    return s3;
    // Itera fino a che vengono trovate soluzioni migliori
}


