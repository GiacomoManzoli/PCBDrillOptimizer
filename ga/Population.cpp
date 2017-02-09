//
// Created by Giacomo Manzoli on 25/11/16.
//

#include "Population.h"
#include <assert.h>
#include <algorithm>
#include <climits>

Population::Population(unsigned int size, double mutationProbability, double newGenerationRatio, Problem *problem) {
    this->size = size;
    this->problem = problem;
    this->NEW_GENERATION_RATIO = newGenerationRatio;
    this->MUTATION_PROBABILITY = mutationProbability;
    this->averageFitness = 0;
    double best = INT_MAX;
    double worst = 0;
    int bi = 0, wi = 0;

    for (int i = 0; i < size; ++i) {
        solutions.push_back(new Solution(problem));
        double solFitness = solutions.at(i)->getFitness();
        if (solFitness < best){
            bi = i;
            best = solFitness;
        }
        if (solFitness > worst){
            wi = i;
            worst = solFitness;
        }
        this->averageFitness += solFitness;
    }
    this->averageFitness/= size;

    //this->best = solutions.at(bi);
    //this->worst = solutions.at(wi);

    this->best = new Solution(problem, solutions.at(bi)->getPath());
    this->worst = new Solution(problem, solutions.at(wi)->getPath());
}

/**
 * Evolve la popolazione.
 * Vengono creati (size*NEW_GENERATION_RATIO) nuovi individui.
 * Viene riportata la popolazione alla dimensione stabilita scegliendo con montecarlo.
 * Tutte le soluzioni della popolazione possono mutare.
 * */
void Population::evolvePopulation(){
    // crea i nuovi individui
    for (int i = 0; i < size*NEW_GENERATION_RATIO; ++i) {
        vector<Solution*> parents = extract(2); // Sceglie i due genitori con K-tournament
        solutions.push_back(crossover(parents.at(0), parents.at(1))); // Crea un nuovo elemento, secondo cross-over uniforme
    }
    // sfoltisce la popolazione scegliendono N con montecarlo, nella scelta faccio anche l'eventuale mutazione
    vector <Solution* > newPopulation;
    // nel mentre calcolo anche le statistiche della popolazione
    this->averageFitness = 0;
    double best = INT_MAX;
    double worst = 0;
    unsigned int bi= 0, wi = 0; // best_index, worst_index
    for (unsigned int i = 0; i < size; ++i) {
        Solution* selected = montecarloSelection(solutions);
        // mutate fa il delete della soluzione, quindi prima di chiamarla devo toglierla da solutions
        solutions.erase(std::remove(solutions.begin(), solutions.end(), selected), solutions.end());
        Solution* newSolution = mutate( selected );
        newPopulation.push_back( newSolution );

        double solFitness = newSolution->getFitness();
        if (solFitness < best){
            bi = i;
            best = solFitness;
        }
        if (solFitness > worst){
            wi = i;
            worst = solFitness;
        }
        this->averageFitness += solFitness;
    }
    solutions = newPopulation;
    this->averageFitness/= size;
    //this->best = solutions.at(bi);
    //this->worst = solutions.at(wi);
    this->best = new Solution(problem, solutions.at(bi)->getPath());
    this->worst = new Solution(problem, solutions.at(wi)->getPath());
}


Solution *Population::getBestSolution() {
    return new Solution(problem, best->getPath());
}

Solution *Population::getWorstSolution() {
    return new Solution(problem, worst->getPath());;
}

double Population::getAverageFitness() {
    return averageFitness;
}

/* ********************************************************************************************************
 * METODI PER LA GESTIONE DELLA POPOLAZIONE
 * ********************************************************************************************************
 */

/**
 * Effettua la scelta pesata di una soluzione, tenendo conto del suo livello di Fitness.
 * */
Solution* Population::montecarloSelection(vector<Solution*> solutions) {
    double tot = 0;
    for (unsigned int i = 0; i < solutions.size(); ++i) {
        tot += solutions.at(i)->getFitness();
    }
    vector<double> adjustedCosts; // "Aggiusto i costi" in modo che quelli che costano poco abbiano maggior probabilità
    // di essere scelti

    double adjustedTot = 0;
    for (unsigned int i = 0; i < solutions.size(); ++i) {
        double adjustedCost = tot - solutions.at(i)->getFitness();
        adjustedCosts.push_back(adjustedCost);
        adjustedTot += adjustedCost; // Aggiungo l'ultimo elemento al totale
    }
    double val = (rand() / (double) RAND_MAX) * adjustedTot; // genero un numero tra 0 e tot
    assert(val >= 0);
    assert(val <= adjustedTot);
    // sommo tutti i valori di fitness, finché non diventano maggiori del valore ottenuto
    // quando diventano maggiori vuol dire che l'indice che ha reso maggiore in numero è quello scelto casualente
    unsigned int i = 0;
    double sum = 0;
    while (val > sum){
        sum += adjustedCosts.at(i);
        if (val > sum) {i++;} // evito di incrementare all'ultima iterazione
    }
    assert(i < solutions.size());
    return solutions.at(i);
}

/**
 * Applica una mutazione alla soluzione con una probabilità bassa.
 * La mutazione avviene effettuando uno shuffle del percorso associato alla soluzione di partenza.
 * */
Solution* Population::mutate(Solution* solution){
    double p = rand() / double(RAND_MAX);
    if (p >= MUTATION_PROBABILITY){ return solution;}

    // C'è da effettuare una mutazione
    vector<Node> currentPath(solution->getPath());

    random_shuffle(currentPath.begin()+1, currentPath.end()-1);
    assert(currentPath.at(0) == 0);
    assert(currentPath.at(currentPath.size()-1) == 0);

    delete solution;
    return new Solution(problem, currentPath);
}

/**
 * Estrae n soluzioni dalla popolazione.
 * La scelta viene fatta con K-tournament, utilizzando un K proporzionale alla dimensione della popolazione.
 * Prima vengono scelti causalmente K elementi dalla popolazione e poi tra questi viene scelto il migliore.
 * K = N/10
 * */
vector<Solution*> Population::extract(int n) {

    vector<Solution*> winners; // array con i risultati da ritornare

    int K = size / 10;

    for (int i = 0; i < n; ++i) {
        vector<Solution*> participants(K);
        vector<Solution*> avoid(winners); //soluzioni già prese in considerazione (vincitrici+già in torneo
        for (int j = 0; j < K; ++j) {
            participants[j] = chooseRandom(this->solutions, avoid);
            avoid.push_back(participants[j]);
        }
        winners.push_back(chooseBest(participants));
    }

    return winners;
}

/**
 * Crea una nuova soluzione combinando 2 soluzioni esistenti.
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
    vector<Node> path1(s1->getPath());
    vector<Node> path2(s2->getPath());

    for (int i = 1; i < N; ++i) {
        Node currentNode = newPath[i-1];
        Node s1Next = s1->nextNode(currentNode);
        Node s2Next = s2->nextNode(currentNode);
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
        // assert (p1+p2 ==1);
        // se s1 è migliore di s2 --> il fitness di s1 è più basso --> p1 < p2 --> prendo l'inverso
        newPath[i] = weightedChoice(s1Next, s2Next, 1-p1);
    }
    
    return new Solution(problem, newPath);
}


/* ********************************************************************************************************
 * METODI PER LA GESTIONE DEI NODI
 * ********************************************************************************************************
 */

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
bool Population::nodeInPath(Node node, vector< Node > path){
    return std::find(path.begin(), path.end(), node) != path.end();
}

/* ********************************************************************************************************
 * METODI PER LA GESTIONE DELLE SOLUZIONI
 * ********************************************************************************************************
 */

Solution* Population::chooseRandom(vector<Solution*> pool, vector<Solution*>  avoid){
    while(true) {
        unsigned int val = rand() % (unsigned int)pool.size();
        Solution* candidate = pool.at(val);

        bool goodCandidate = true;
        for (unsigned int i = 0; i < avoid.size(); ++i) {
            //if (avoid.at(i)->equals(*candidate)) { // se uso equals ci sono troppe soluzioni con lo stesso path quando mi avvicino alla convergenza e quindi diventa troppo pesante
            if (avoid.at(i) == candidate) {
                goodCandidate = false;
                break;
            }
        }
        if (goodCandidate){
            return candidate;
        }
    }
}

Solution* Population::chooseBest(vector<Solution*> pool){
    double bestValue = INT_MAX;
    unsigned long index = pool.size()+1;
    for (unsigned long i = 0; i < pool.size(); ++i) {
        if (pool.at(i)->getFitness() < bestValue){
            bestValue = pool.at(i)->getFitness();
            index = i;
        }
    }
    return pool.at(index);
}


