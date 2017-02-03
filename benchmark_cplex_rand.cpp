#include <iostream>
#include <fstream>

#include "common/Problem.h"
#include "ga/GASolver.h"
#include "cplex/CPLEXSolver.h"


using namespace std;

int main() {
    srand(time(NULL));
    std::cout << "Hello, World! from benchmark_cplex_rand.cpp" << std::endl;

    const unsigned int START_SIZE = 5;
    const unsigned int STEP = 5;

    string istancesPaths[25] = {
            "istances/benchmark/rand/rand_n5_distances.txt",
            "istances/benchmark/rand/rand_n10_distances.txt",
            "istances/benchmark/rand/rand_n15_distances.txt",
            "istances/benchmark/rand/rand_n20_distances.txt",
            "istances/benchmark/rand/rand_n25_distances.txt",
            "istances/benchmark/rand/rand_n30_distances.txt",
            "istances/benchmark/rand/rand_n35_distances.txt",
            "istances/benchmark/rand/rand_n40_distances.txt",
            "istances/benchmark/rand/rand_n45_distances.txt",
            "istances/benchmark/rand/rand_n50_distances.txt",
            "istances/benchmark/rand/rand_n55_distances.txt",
            "istances/benchmark/rand/rand_n60_distances.txt",
            "istances/benchmark/rand/rand_n65_distances.txt",
            "istances/benchmark/rand/rand_n70_distances.txt",
            "istances/benchmark/rand/rand_n75_distances.txt",
            "istances/benchmark/rand/rand_n80_distances.txt",
            "istances/benchmark/rand/rand_n85_distances.txt",
            "istances/benchmark/rand/rand_n90_distances.txt",
            "istances/benchmark/rand/rand_n95_distances.txt",
            "istances/benchmark/rand/rand_n100_distances.txt",
            "istances/benchmark/rand/rand_n105_distances.txt",
            "istances/benchmark/rand/rand_n110_distances.txt",
            "istances/benchmark/rand/rand_n115_distances.txt",
            "istances/benchmark/rand/rand_n120_distances.txt",
            "istances/benchmark/rand/rand_n125_distances.txt"
    };

    ofstream myfile;
    myfile.open("outputs/benchmark/cplex_rand.csv");
    myfile << "size;requested_time;istanceName"<<endl;

    unsigned int currentSize = START_SIZE;
    cout << "Inizio batteria di risoluzioni "<<endl;
    for (unsigned int i = 0; i < 25; i++){
        cout << "---------"<<endl;
        cout << "Dimensione: " << currentSize << endl;
        string currentIstance = istancesPaths[i];
        clock_t t1, t2;

        Problem *p = new Problem(currentIstance);

        t1 = clock();
        CPLEXSolver *solver = new CPLEXSolver(p);
        solver->solve();
        t2 = clock();

        double elapsedTime = (double)(t2-t1) / CLOCKS_PER_SEC;
        cout << "Tempo necessario: "<< elapsedTime << endl;

        myfile << currentSize <<";";
        myfile << elapsedTime <<";";
        myfile << currentIstance <<endl;
        currentSize += STEP;
        delete solver;
        delete p;
    }

    myfile.close();
    return 0;
}