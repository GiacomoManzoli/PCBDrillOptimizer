//
// Created by Giacomo Manzoli on 25/11/16.
//

#ifndef PARTE_2_META_EURSTICHE_GASOLVER_H
#define PARTE_2_META_EURSTICHE_GASOLVER_H


#include "../common/Solution.h"
#include "Population.h"

class GASolver {
private:
    Problem* problem;
    unsigned int populationSize;
    unsigned int timeLimit;
    double mutationProbability;
    double newGenerationRatio;
    Population* population;
    unsigned int lastIterationsCount;
public:
    GASolver(Problem *problem, unsigned int populationSize, unsigned int timeLimit, double mutationProbability, double newGenerationRatio);
    ~GASolver(){ problem = NULL; /*Non cancella problem*/ delete population;}
    Solution* solve();
    Population* getLastPopulation();
    unsigned int getLastIterationsCount();
};


#endif //PARTE_2_META_EURSTICHE_GASOLVER_H
