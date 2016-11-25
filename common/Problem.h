//
// Created by Giacomo Manzoli on 25/11/16.
//

#ifndef PARTE_2_META_EURSTICHE_PROBLEM_H
#define PARTE_2_META_EURSTICHE_PROBLEM_H

#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

typedef int Node; // Tipo nodo, è un intero rinominato. Questo per disamgibuare il nodo da un indice.

class Problem {
private:
    vector< vector<double> > C;
    unsigned int N;
    vector<Node> nodes;
public:
    Problem(unsigned int N);
    Problem(string fileName);
    vector< vector<double> > getCosts();
    unsigned int getSize();
    void printCosts();
    vector<Node> getNodes();
};


#endif //PARTE_2_META_EURSTICHE_PROBLEM_H
