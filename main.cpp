#include <iostream>
#include <fstream>

#include "common/Problem.h"
#include "ga/GASolver.h"
#include "cplex/CPLEXSolver.h"


using namespace std;

int main() {
    srand(time(NULL));
    std::cout << "Hello, World! from main.cpp" << std::endl;


     unsigned int maxTimes[4] {
            1,  // 1 seconod0
            10, // 10 secondi
            60, // 1 minuto
            600 // 10 minuti
    };

    const unsigned int START_SIZE = 5;
    const unsigned int STEP = 5;

    string istancesPaths[25] = {
            "istances/benchmark/pseudo/pseudo_n5_distances.txt",
            "istances/benchmark/pseudo/pseudo_n10_distances.txt",
            "istances/benchmark/pseudo/pseudo_n15_distances.txt",
            "istances/benchmark/pseudo/pseudo_n20_distances.txt",
            "istances/benchmark/pseudo/pseudo_n25_distances.txt",
            "istances/benchmark/pseudo/pseudo_n30_distances.txt",
            "istances/benchmark/pseudo/pseudo_n35_distances.txt",
            "istances/benchmark/pseudo/pseudo_n40_distances.txt",
            "istances/benchmark/pseudo/pseudo_n45_distances.txt",
            "istances/benchmark/pseudo/pseudo_n50_distances.txt",
            "istances/benchmark/pseudo/pseudo_n55_distances.txt",
            "istances/benchmark/pseudo/pseudo_n60_distances.txt",
            "istances/benchmark/pseudo/pseudo_n65_distances.txt",
            "istances/benchmark/pseudo/pseudo_n70_distances.txt",
            "istances/benchmark/pseudo/pseudo_n75_distances.txt",
            "istances/benchmark/pseudo/pseudo_n80_distances.txt",
            "istances/benchmark/pseudo/pseudo_n85_distances.txt",
            "istances/benchmark/pseudo/pseudo_n90_distances.txt",
            "istances/benchmark/pseudo/pseudo_n95_distances.txt",
            "istances/benchmark/pseudo/pseudo_n100_distances.txt",
            "istances/benchmark/pseudo/pseudo_n105_distances.txt",
            "istances/benchmark/pseudo/pseudo_n110_distances.txt",
            "istances/benchmark/pseudo/pseudo_n115_distances.txt",
            "istances/benchmark/pseudo/pseudo_n120_distances.txt",
            "istances/benchmark/pseudo/pseudo_n125_distances.txt"
    };

    ofstream myfile;
    myfile.open("outputs/benchmark/ga_pseudo.csv");
    myfile << "size;requested_time;istanceName"<<endl;

    unsigned int currentSize = START_SIZE;
    cout << "Inizio batteria di risoluzioni "<<endl;
    for (unsigned int i = 0; i < 2; i++){
        cout << "---------"<<endl;
        cout << "Dimensione: " << currentSize << endl;
        string currentIstance = istancesPaths[i];

        for (unsigned int t = 0; t < 4; t++){
            unsigned int currentTime = maxTimes[t];

            if (currentSize < 30 && currentTime == 600) continue; // Risparmio un po' di esecuzionioni

            cout<< "Tempo massimo "<< currentTime << endl;


            for (unsigned int k = 0; k < 5; k++){
                clock_t t1, t2;

                Problem *p = new Problem(currentIstance);

                GASolver *solver = new GASolver(
                        p,
                        100,
                        currentTime,
                        0.01,
                        1.1
                );
                solver->solve();

                double elapsedTime = (double)(t2-t1) / CLOCKS_PER_SEC;
                cout << "Tempo necessario: "<< elapsedTime << endl;
                myfile << currentSize <<";";
                myfile << elapsedTime <<";";
                myfile << currentIstance <<endl;
                delete solver;
                delete p;
            }


        }
        currentSize += STEP;
    }
    myfile.close();
    return 0;
}