
#include <iostream>
#include "Problem.h"
#include "Solution.h"
#include <assert.h>



/**
 * Crea una soluzione per il problema.
 * Viene costruita in modo pseudo-greey
 * */
Solution::Solution(Problem *problem) {
    this->problem = problem;

    // Costruisco la soluzione in modo pseudo-casuale: come successore scelgo a caso tra quelli possibili, tenendo conto di quanto migliorano
    vector< vector<double> > C = problem->getCosts();
    unsigned int N = problem->getSize();
    fitness = 0;
    path.resize(N + 1);
    path[0] = 0; // parto sempre dal nodo 0

    vector<Node> nodes(N-1); // Creo un vettore con i nodi ancora da scegliere per il percorso (da notare che non c'è il nodo 0)
    for (int i = 0; i < N-1; ++i) {
        nodes[i] = i+1;
    }

    for (int i = 1; i < N; ++i) {
        Node selectedNode = chooseNode(path[i-1], nodes, C);
        cout << "Costo tra " << path[i-1] << " e " << selectedNode << endl;
        fitness += C[path[i-1]][selectedNode]; // man mano che proseguo calcolo il costo della soluzione
        path[i] = selectedNode;

        // ricalcolo il vettore dei nodi disponibili
        vector<Node> newNodes;
        for (int j = 0; j < nodes.size(); ++j) {
            if (nodes[j] != selectedNode) { newNodes.push_back(nodes[j]);}
        }
        assert(nodes.size() == newNodes.size()+1);
        nodes = newNodes;
    }
    fitness += C[path[N-1]][0]; // costo dal penultimo nodo, al quello di partenza (il +0 è per chiarezza)
    path[N] = 0; // il nodo di arrivo deve essere sempre 0

}

/**
 * Crea una soluzione per il problema, dato un percorso che è già una soluzione
 * */
Solution::Solution(Problem *problem, vector<Node> p) {
    this->problem = problem;
    unsigned int N = problem->getSize();
    vector< vector<double> > C = problem->getCosts();
    this->path.assign(p.begin(), p.end());
    fitness = 0;
    int debug_sum = 0;
    int debug_sum_2 =0;
    for (int i = 0; i < N; ++i) {
        debug_sum += path[i];
        debug_sum_2 += i;
        fitness += C[path[i]][path[i+1]];
    }
    assert(debug_sum == debug_sum_2);
}

double Solution::getFitness() {
    return fitness;
}
/**
 * Stampa a video il percorso
 * */
void Solution::printPath() {

    cout << "Fitness: " << fitness <<endl;
    for (int i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i != path.size()-1) { cout << " -> ";}
    }
    cout << endl;
}

vector<Node> Solution::getPath() {
    return path;
}

Node Solution::nextNode(Node from) {
    for (int i = 0; i < path.size()-1; ++i) {
        if (path[i] == from){
            return path[i+1];
        }
    }
    assert(false); // Se arriva qui è un errore
    return -1;
}


// ########### Metodi privait
/**
 * Effettua la scelta pesata di un nodo da utilizzare come destinazione a partire dal nodo from
 * */
Node Solution::chooseNode(Node from, vector<Node> nodes, vector< vector<double> >& C){
    if (nodes.size() == 1){
        return nodes[0];
    }

    double tot = 0;
    for (int i = 0; i < nodes.size(); ++i) {
        tot += C[from][nodes[i]];
    }
    vector<double> normalizedCosts; // Normalizzo i costi dal nodo di partenza a quelli a cui possono ancora andare
    double debug_sum = 0;
    for (int i = 0; i < nodes.size(); ++i) {
        normalizedCosts.push_back(C[from][nodes[i]] / tot);
        debug_sum+=C[from][nodes[i]] / tot;
    }
    double val = rand() / double(RAND_MAX); // genero un numero tra 0 e 1
    assert(val >= 0);
    assert(val <= 1);
    cout << "VAL " <<val <<endl;
    // sommo tutte le probabilità, finché non diventano maggiori del valore ottenuto
    // quando diventano maggiori vuol dire che l'indice che ha reso maggiore in numero è quello scelto casualente
    int i = 0;
    double sum = 0;
    while (val > sum){
        sum += normalizedCosts[i];
        if (val > sum) {i++;} // evito di incrementare all'ultima iterazione
    }
    assert(i < nodes.size());
    return nodes[i];
}