//
// Created by Giacomo Manzoli on 25/11/16.
//

#ifndef PARTE_2_META_EURSTICHE_POPULATION_H
#define PARTE_2_META_EURSTICHE_POPULATION_H


#include "../common/Problem.h"
#include "../common/Solution.h"

class Population {
private:
    unsigned int size;
    Problem* problem;
    vector< Solution* > solutions;
    Node weightedChoice(Node v1, Node v2, double p);
    Node bestAvaibleNode(Node from, vector<Node> partialPath, Problem *p);
    bool isGoodChoice(Node n, vector<Node> path);
    bool isBadChoice(Node n, vector<Node> path);
public:
    Population(unsigned int size, Problem* problem);
    Solution** extract(int n);
    Solution* crossover(Solution* s1, Solution* s2);
};


#endif //PARTE_2_META_EURSTICHE_POPULATION_H
