#ifndef SOLUTION_H
#define SOLUTION_H

#include <cstdlib>
#include <vector>
#include <iostream>
#include "Problem.h"

using namespace std;

class Solution {
private:
    Problem* problem;
    vector<Node> path; // Percorso
    double fitness; // lo tengo come campo dati che viene calcolato durante la costruzione
    Node chooseNode(Node from, vector<Node> nodes, vector< vector<double> >& C);
public:
    Solution(Problem* problem);
    Solution(Problem* problem, vector<Node> path);
    ~Solution() { problem = nullptr;}
    double getFitness() const;
    vector<Node> getPath() const;
    void printPath() const;
    Node nextNode(Node from) const;
    bool equals(const Solution& sol) const;
};

#endif