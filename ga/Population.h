//
// Created by Giacomo Manzoli on 25/11/16.
//

#ifndef PARTE_2_META_EURSTICHE_POPULATION_H
#define PARTE_2_META_EURSTICHE_POPULATION_H


#include "../common/Problem.h"
#include "../common/Solution.h"

class Population {
private:
    // Parametri dell'algoritmo
    double MUTATION_PROBABILITY;
    double NEW_GENERATION_RATIO;

    // Parametri settabili da API
    unsigned int size;
    Problem* problem;

    // Statistiche sulla popolazione
    Solution* best;
    Solution* worst;
    double averageFitness;

    vector< Solution* > solutions;

    // Metodi per la gestione della popolazione
    Solution *montecarloSelection(vector<Solution *> solutions);
    Solution *mutate(Solution *solution);
    vector<Solution*> extract(int n);
    Solution* crossover(Solution* s1, Solution* s2);

    // Metodi ausiliari per la gestione dei nodi
    Node weightedChoice(Node v1, Node v2, double p);
    Node bestAvaibleNode(Node from, vector<Node> partialPath, Problem *p);
    bool isGoodChoice(Node n, vector<Node> path);
    bool isBadChoice(Node n, vector<Node> path);
    bool nodeInPath(Node node, vector<Node> path);

    // Metodi ausiliari per la gestione delle soluzioni
    Solution *chooseRandom(vector<Solution*> pool, vector<Solution*>  avoid);
    Solution *chooseBest(vector<Solution*>  pool);

public:
    Population(unsigned int size, double mutationProbability, double newGenerationRatio,  Problem* problem);
    ~Population() {
        problem = nullptr;
        delete best;
        delete worst;
    }
    void evolvePopulation();
    Solution* getBestSolution();
    Solution* getWorstSolution();
    double getAverageFitness();
};


#endif //PARTE_2_META_EURSTICHE_POPULATION_H
