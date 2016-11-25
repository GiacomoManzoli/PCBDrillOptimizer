//
// Created by Giacomo Manzoli on 25/11/16.
//

#ifndef PARTE_2_META_EURSTICHE_GASOLVER_H
#define PARTE_2_META_EURSTICHE_GASOLVER_H


#include "../common/Solution.h"

class GASolver {
private:
    Problem* problem;
public:
    GASolver(Problem* problem);
    Solution* solve();
};


#endif //PARTE_2_META_EURSTICHE_GASOLVER_H
