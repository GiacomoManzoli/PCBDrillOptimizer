#include <iostream>
#include <fstream>
#include <chrono>

#include "common/Problem.h"
#include "ga/GASolver.h"
#include "cplex/CPLEXSolver.h"


using namespace std;


string getIstanceName(string baseName, int n, int v) {
    return baseName + to_string(n) +"_v"+to_string(v) +"_distances.txt";
}


int main() {
    srand(time(NULL));
    std::cout << "Hello, World! from main.cpp" << std::endl;

    const unsigned int START_SIZE = 5;


    string oFileName = "outputs/benchmark/cplex_rand.csv";
    ofstream myfile;
    myfile.open(oFileName);
    myfile << "size;requested_time;istanceName;val"<<endl;
    myfile.close();
    unsigned int currentSize;
    cout << "Inizio batteria di risoluzioni "<<endl;

    for (unsigned int i = 19; i <= 19; i++){
        cout << "---------"<<endl;
        cout << "Dimensione: " << START_SIZE + START_SIZE*i << endl;
        currentSize = START_SIZE + START_SIZE*i;
        for (unsigned int j = 1; j <= 5; j++){
            string currentIstance = getIstanceName("istances/benchmark/rand/rand_n",currentSize, j);
            cout << "Istanza N: "<<j <<" Filepath: "<< currentIstance <<endl;
            Problem *p = new Problem(currentIstance);

            std::chrono::time_point<std::chrono::system_clock> start, end;

            start = std::chrono::system_clock::now();
            CPLEXSolver *solver = new CPLEXSolver(p, 600);
            Solution* solution = nullptr;
            //t1 = clock();
            try {
                solution = solver->solve();
            } catch (...) {
                cout << "TIME LIMIT RAGGIUNTO" <<endl;
            }

            //t2 = clock();
            end = std::chrono::system_clock::now();

            std::chrono::duration<double> elapsed_seconds = end-start;


            double elapsedTime = elapsed_seconds.count();
            cout << "Tempo necessario: "<< elapsedTime << endl;
            myfile.open(oFileName, ios::out | ios::app );
            myfile << currentSize <<";";
            myfile << elapsedTime <<";";
            myfile << currentIstance <<";";

            if (solution != nullptr){
                myfile << solution->getFitness()<<endl;
                delete solution;
            } else {
                myfile << "-1"<<endl;
            }


            myfile.close();
            delete solver;
            delete p;
        }
    }


    return 0;
}