//
// Created by Giacomo Manzoli on 25/11/16.
//

#include "GASolver.h"
#include "Population.h"
#include <iostream>

using namespace std;


GASolver::GASolver(Problem *problem, unsigned int populationSize, unsigned int timeLimit, double mutationProbability, double newGenerationRatio) {
    this->problem = problem;
    this->populationSize = populationSize;
    this->timeLimit = timeLimit;
    this->mutationProbability = mutationProbability;
    this->newGenerationRatio = newGenerationRatio;
}


Solution *GASolver::solve() {
    // Crea la popolazione (insieme di soluzioni, dimensione della popolazione)
    Population* population = new Population(this->populationSize,this->mutationProbability, this->newGenerationRatio, problem);

    cout << "Popolazione iniziale:" <<endl;
    Solution* worstSol = population->getWorstSolution();
    cout << "Worst: " <<worstSol->getFitness();
    delete worstSol;
    cout << "\t Avg: " <<population->getAverageFitness();
    Solution* bestSol = population->getBestSolution();
    cout << "\t Best: " <<bestSol->getFitness() << endl;
    delete bestSol;

    cout << "Evoluzione in corso..." <<endl;
    unsigned int i = 0;

    /* Viene usato time perché in questo caso il CPU time è circa uguale al wall time.
     * CPLEX invece lavora su più thread e quindi il CPU time è maggiore del wall time.
     * */
    time_t startingTime = time(0); // espresso in sencondi (UNIX time-stamp)

    while (time(0) - startingTime < this->timeLimit) {
        i++;
        population->evolvePopulation();
        if (i % 1000 == 0) {
            cout << "Iterazione "  <<i <<endl;
            worstSol = population->getWorstSolution();
            cout << "Worst: " <<worstSol->getFitness();
            delete worstSol;
            cout << "\t Avg: " <<population->getAverageFitness();
            bestSol = population->getBestSolution();
            cout << "\t Best: " <<bestSol->getFitness() << endl;
            delete bestSol;
        }
    }

    //while (true){
    //    // Consecutive not improving non funziona bene (consectuive worstening invece non termina quasi mai)
    //    if (consecutiveNotImproving == 20){ break; }
    //    i++;
    //    double oldBest = population->getAverageFitness();
    //    population->evolvePopulation();
    //    double newBest = population->getAverageFitness();
    //
    //    if (newBest >= oldBest) { consecutiveNotImproving++;}
    //    else {consecutiveNotImproving = 0;}
    //    if (i % 10 == 0) {
    //        cout << "Iterazione "  <<i <<endl;
    //        cout << "Worst: " <<population->getWorstSolution()->getFitness();
    //        cout << "\t Avg: " <<population->getAverageFitness();
    //        cout << "\t Best: " <<population->getBestSolution()->getFitness() << endl;
    //    }
    //}
    //for (int j = 0; j < 2000; ++j) {
    //    // Ad ogni iterazione dell'algoritmo evolvo la popolazione.
    //    // L'evoluzione genera R nuovi elementi a partire dagli N presenti
    //    // Tra gli N+R elementi ne vegono scelti N da tenere all'interno della popolazione.
    //    population->evolvePopulation();
    //}

    cout << "Popolazione finale" <<endl;
    worstSol = population->getWorstSolution();
    cout << "Worst: " <<worstSol->getFitness();
    delete worstSol;
    cout << "\t Avg: " <<population->getAverageFitness();
    bestSol = population->getBestSolution();
    cout << "\t Best: " <<bestSol->getFitness() << endl;
    delete bestSol;

    Solution* sol = population->getBestSolution();
    this->population = population;
    this->lastIterationsCount = i;
    return sol;

}

Population *GASolver::getLastPopulation() {
    return this->population;
}

unsigned int GASolver::getLastIterationsCount() {
    return this->lastIterationsCount;
}


