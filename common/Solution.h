#ifndef SOLUTION_H
#define SOLUTION_H

#import <cstdlib>
#import <vector>
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
    double getFitness();
    vector<Node> getPath();
    void printPath();
    Node nextNode(Node from);
};

#endif