//
// Created by Giacomo Manzoli on 04/02/17.
//

#include <iostream>
#include <fstream>

#include "common/Problem.h"
#include "ga/GASolver.h"


using namespace std;


string getIstanceName(string baseName, int n, int v) {
    return baseName + to_string(n) +"_v"+to_string(v) +"_distances.txt";
}


unsigned int getMaxTime(unsigned int currentSize) {
    if (currentSize <= 20) { return 1; }
    if (currentSize <= 35) { return 10; }
    if (currentSize <= 65) { return 60; }
    if (currentSize <= 85) { return 600; }

    return 600;
}

int main() {
    srand(time(NULL));
    std::cout << "Hello, World! from benchmark_ga_pseudo.cpp" << std::endl;

    const unsigned int START_SIZE = 5;

    // Prepero il file
    string oFileName = "outputs/benchmark/ga_pseudo.csv";
    ofstream myfile;
    myfile.open(oFileName);
    myfile << "size;requested_time;istanceName;val"<<endl;
    myfile.close();

    unsigned int currentSize;
    cout << "Inizio batteria di risoluzioni "<<endl;
    for (unsigned int i = 0; i < 19; i++){
        cout << "---------"<<endl;
        cout << "Dimensione: " << START_SIZE + START_SIZE*i << endl;
        currentSize = START_SIZE + START_SIZE*i;
        for (unsigned int j = 1; j <= 5; j++){
            string currentIstance = getIstanceName("istances/benchmark/pseudo/pseudo_n",currentSize, j);
            cout << "Istanza N: "<<j <<" Filepath: "<< currentIstance <<endl;
            for (unsigned int k = 0; k < 5; k++){
                cout << "Esecuzione "<<k+1<< " di 5"<<endl;

                Problem *p = new Problem(currentIstance);

                std::chrono::time_point<std::chrono::system_clock> start, end;
                start = std::chrono::system_clock::now();

                GASolver *solver = new GASolver(
                        p,
                        100, // POP_SIZE
                        getMaxTime(currentSize),
                        0.05, // Mutatio rate
                        2 // POP_RATIO
                );
                Solution* solution = solver->solve();

                end = std::chrono::system_clock::now();
                std::chrono::duration<double> elapsed_seconds = end-start;
                double elapsedTime = elapsed_seconds.count();
                cout << "Tempo necessario: "<< elapsedTime << endl;


                myfile.open(oFileName, ios::out | ios::app );
                myfile << currentSize <<";";
                myfile << elapsedTime <<";";
                myfile << currentIstance <<";";
                myfile << solution->getFitness()<<endl;
                myfile.close();

                delete solution;
                delete solver;
                delete p;
            }
        }
    }

    return 0;
}