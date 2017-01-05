//
// Created by Giacomo Manzoli on 25/11/16.
//

#include "Problem.h"

#include <fstream>
#include <iostream>

/**
 * Costruisce un'istanza casuale del problema di dimensione N.
 * I costi vengono generati casualmente come valori da 1 a 100, rispettando la
 * simmetria della matrice
 * */
Problem::Problem(unsigned int N) {
    this->N = N;
    nodes.reserve(N); // crea i "nodi" del problema
    for (int i = 0; i < N; ++i) { nodes.push_back(i); }

    this->C.resize(N);
    srand(time(NULL));

    for (int i = 0; i < N; ++i) {
        if (C[i].size() == 0) { C[i].resize(N); }
        C[i][i] = 0; // azzera la diagonale
        for (int j = i+1; j < N; j++){
            C[i][j] = rand() % 99 +1; // costo casuale C_i,j (non nullo)
            if (C[j].size() == 0) { C[j].resize(N); }
            C[j][i] = C[i][j]; // la matrice è simmetrica, C_j,i = C_i,j
        }
    }

}

/**
 * Costruisce un'istanza caricandola da file
 * */
Problem::Problem(string fileName) {
    fileName = "istances/genetic/rand_n50_1_distances.txt";
    fstream file(fileName, ios_base::in);
    file >> N;
    nodes.reserve(N); // crea i "nodi" del problema
    for (int i = 0; i < N; ++i) { nodes.push_back(i); }
    C.resize(N);
    for (int i = 0; i < N; ++i) {
        C[i].resize(N);
        for (int j = 0; j <N; j++){
            file >> C[i][j];
        }
    }

}

/**
 * Ritorna la matrice dei costi per il problema
 * */
vector< vector<double> > Problem::getCosts() {
    return C;
}

/**
 * Ritorna il numero di nodi presenti nel problema
 * */
unsigned int Problem::getSize() {
    return N;
}

/**
 * Stampa la matrice dei costi del problema
 * */
void Problem::printCosts() {
    cout << "Costi C_i,j"<<endl;
    cout << "i\\j\t";
    for (int i = 0; i < N; ++i)
    {
        cout <<i <<"\t";
    }
    cout << endl;
    for (int i = 0; i < N; ++i) {
        cout << i <<"\t";
        for (int j = 0; j <N; j++){
            cout << C[i][j]<<"\t";
        }
        cout << endl;
    }
}

vector<Node> Problem::getNodes() {
    return nodes;
}
