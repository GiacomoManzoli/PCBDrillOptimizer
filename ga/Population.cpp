//
// Created by Giacomo Manzoli on 25/11/16.
//

#include "Population.h"
#include <assert.h>
#include <iostream>


Population::Population(unsigned int size, Problem *problem) {
    this->size = size;
    this->problem = problem;

    for (int i = 0; i < size; ++i) {
        solutions.push_back(new Solution(problem));
    }


}


bool nodeInPath(Node node, vector< Node > path){
    return std::find(path.begin(), path.end(), node) != path.end();
}

/**
 * Crea una nuova soluzione a combinando 2 soluzioni esistenti.
 * La combinazione viene fatta considerando gli archi del cammino delle due soluzioni.
 * C'è il vincolo che la nuova soluzione parta dal nodo 0, quindi si controlla tra le due
 * soluzioni qual'è il nodo successivo al nodo 0 e viene fatta la scelta su quale spostarsi.
 * La scelta è influenzata dal fitness della soluzione.
 * Ci sono dei casi limite:
 *  - Se uno arco è già stato percorso, viene scelto l'altro, senza tenere conto del fitness
 *  - L'arco finale è sempre verso il nodo 0
 * */
Solution *Population::crossover(Solution *s1, Solution *s2) {
    unsigned int N = problem->getSize();
    vector<Node> newPath(N+1);
    newPath[0] = newPath[N] = 0;
    vector<Node> path1 = s1->getPath();
    vector<Node> path2 = s2->getPath();

    for (int i = 1; i < N; ++i) {
        Node currentNode = newPath[i-1];
        Node s1Next = s1->nextNode(currentNode);
        Node s2Next = s2->nextNode(currentNode);
        cout << currentNode << " " << s1Next << " " << s2Next << endl;
        /* Casi possibili
         * s1Next = 0 e s2Next != 0 e notInPath => scelgo s2Next
         * s1Next = 0 e s2Next = 0 oppure s2Next inPath => correggo scegliendo tra quelli rimasti il migliore
         * (^ ci sono anche i casi simmetrici)
         * s1Next e s2Next entrambi in path => correggo scegliendo tra quelli rimasti il migliore
         * s1Next e s2Next entrambi buoni => scelta pesata
         * */

        // Solo uno dei due è una buona scelta
        if (isBadChoice(s1Next, newPath) && isGoodChoice(s2Next, newPath)) { newPath[i] = s2Next; continue; }
        if (isBadChoice(s2Next, newPath) && isGoodChoice(s1Next, newPath)) { newPath[i] = s1Next; continue; }
        // Entrambi sono una brutta scelta
        if (isBadChoice(s1Next, newPath) && isBadChoice(s2Next, newPath) ) { newPath[i] = bestAvaibleNode(currentNode, newPath, problem); continue; }


        // Entrambi i nodi sono nodi buoni
        double tot = s1->getFitness() + s2->getFitness();
        double p1 = s1->getFitness()/tot;
        double p2 = s2->getFitness()/tot;
        assert (p1+p2 ==1);

        newPath[i] = weightedChoice(s1Next, s2Next, p1);
    }
    
    return new Solution(problem, newPath);
}



/**
 * Estrae n soluzioni dalla popolazione, scelte a caso in base al loro livello di fitness
 * */
Solution **Population::extract(int n) {
    Solution** solutions = new Solution*[n];

    // TODO implementare
    for (int i = 0; i < n; ++i) {
        solutions[i] = this->solutions[i];
    }
    return solutions;
}

// ############# METODI PRIVATI

/**
 * Effettua la scelta pesata di un valore in base alla sua probabilità
 * il parametro p è la probabilità di scegliere il primo valore.
 * */
Node Population::weightedChoice(Node v1, Node v2, double p) {
    double r = rand() / double(RAND_MAX);
    assert(r <= 1);
    if (r < p) {
        return v1;
    } else {
        return v2;
    }
}
/**
 * Cerca il miglior nodo in cui spostarsi
 * */
Node Population::bestAvaibleNode(Node from, vector<Node> partialPath, Problem* p){
    vector<Node > availableNodes;
    vector<Node> problemNodes = p->getNodes();
    for (int i = 0; i < problemNodes.size(); ++i) {
        if (!nodeInPath(problemNodes[i], partialPath)) {
            availableNodes.push_back(problemNodes[i]);
        }
    }
    double minCost = (double)INT_MAX;
    int minIndex = -1;
    for (int i = 0; i < availableNodes.size(); ++i) {
        double c = p->getCosts()[from][availableNodes[i]];
        if ( c < minCost){
            minCost = c;
            minIndex = i;
        }
    }
    return availableNodes[minIndex];
}
/**
 * Controlla se il nodo n può essere inserito o meno nel percorso path
 * */
bool Population::isGoodChoice(Node n, vector<Node> path){
    return n != 0 && !nodeInPath(n, path);
}
/**
 * Controlla se il nodo n NON può essere inserito o meno nel percorso path
 * */
bool Population::isBadChoice(Node n, vector<Node> path){
    return n == 0 || nodeInPath(n, path);
}