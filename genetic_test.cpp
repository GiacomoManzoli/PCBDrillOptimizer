#include <iostream>
#include <fstream>

#include "common/Problem.h"
#include "ga/GASolver.h"


using namespace std;

int main() {
    srand(time(NULL));
    std::cout << "Hello, World! from genetic_test.cpp" << std::endl;

    unsigned int populationSizes[3] = {100, 250, 500};
    double mutationRates[3] = {0.01, 0.05, 0.1};
    double newGenerationRatios[3] = {1.1, 1.5, 2};

    string istancesPaths[10] = {
            "istances/genetic/rand_n50_1_distances.txt",
            "istances/genetic/rand_n50_2_distances.txt",
            "istances/genetic/rand_n50_3_distances.txt",
            "istances/genetic/rand_n50_4_distances.txt",
            "istances/genetic/rand_n50_5_distances.txt",
            "istances/genetic/pseudo_rand_n50_1_distances.txt",
            "istances/genetic/pseudo_rand_n50_2_distances.txt",
            "istances/genetic/pseudo_rand_n50_3_distances.txt",
            "istances/genetic/pseudo_rand_n50_4_distances.txt",
            "istances/genetic/pseudo_rand_n50_5_distances.txt"
    };
    ofstream myfile;
    myfile.open("outputs/gen_n50.csv");

    myfile << "pop_size;mutation;generation;istance;iters;worst;avg;best"<<endl;
    cout << "Inizio batteria di risoluzioni "<<endl;
    for (unsigned int a = 0; a < 3; a++){
        for (unsigned int b = 0; b < 3; b++){
            for (unsigned int c = 0; c < 3; c++){
                for (unsigned int ist = 0; ist < 10; ist++){
                    for (unsigned int times = 0; times < 5; times++){

                        cout << istancesPaths[ist]<<";";
                        cout << populationSizes[a]<<";";
                        cout << mutationRates[b]<<";";
                        cout << newGenerationRatios[c]<<";"<<endl;
                        string path = istancesPaths[ist];
                        Problem* p = new Problem(path);
                        GASolver* solver = new GASolver(
                                p,
                                populationSizes[a],
                                1, // Timelimit di 1 minuto
                                mutationRates[b],
                                newGenerationRatios[c]);
                        Solution* solution = solver->solve();
                        Population* population = solver->getLastPopulation();
                        myfile << populationSizes[a]<<";";
                        myfile << mutationRates[b]<<";";
                        myfile << newGenerationRatios[c]<<";";
                        myfile << istancesPaths[ist]<<";";
                        myfile << solver->getLastIterationsCount()<<";";
                        myfile << population->getWorstSolution()->getFitness()<<";";
                        myfile << population->getAverageFitness()<<";";
                        myfile << population->getBestSolution()->getFitness()<<endl;
                        delete solver;
                        delete p;
                    }
                }
            }
        }
    }
    myfile.close();




    return 0;
}