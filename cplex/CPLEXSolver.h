//
// Created by Giacomo Manzoli on 25/11/16.
//

#ifndef PARTE_2_META_EURSTICHE_CPLEXSOLVER_H
#define PARTE_2_META_EURSTICHE_CPLEXSOLVER_H


#include "../common/Problem.h"
#include "../common/Solution.h"
#include "cpxmacro.h"

class CPLEXSolver {
private:
    static const int NAME_SIZE = 512;
    Env env; // CPLEX Enviroment
    Prob lp; // CPLEX Problem
    int status;     // error status and messagge buffer
    char errmsg[BUF_SIZE];
    char name[NAME_SIZE];
    std::vector< std::vector<int> > xMap;
    std::vector< std::vector<int> > yMap;
    Problem* problem;
public:
    CPLEXSolver(Problem* problem);
    Solution* solve();
};


#endif //PARTE_2_META_EURSTICHE_CPLEXSOLVER_H
