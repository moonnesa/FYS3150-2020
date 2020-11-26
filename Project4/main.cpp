#include <ising.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <stdio.h>
#include "lib.h"
// input arguments: [L/dim] [temp_init] [temp_final] [temp_step] [cycles]
int main(int argc, char *argv[]) {


    double expected_values [5];
    double expected_24_values [5];
    double expected_20_values_1 [5];
    double expected_20_values_24 [5];


    int dim = atoi(argv[1]);
    double temp_init  = atof(argv[2]);
    double temp_final = atof(argv[3]);
    double temp_step  = atof(argv[4]);
    int cycles = atoi(argv[5]);
    double temp_24  = atof(argv[6]);

    Ising IsingModel = Ising(dim, "expectations100.txt");
    for (float temp=temp_init; temp <= temp_final; temp += temp_step) {
        for (int i = 0; i < 5; i ++) {
            expected_values[i] = 0;
        }
        IsingModel.initialise_random(temp);
        IsingModel.simulate(cycles, expected_values);
        IsingModel.write_to_terminal(cycles);
    }
    /*
    Ising IsingModel24_2 = Ising(dim, "expectations20_24.txt");
    for (int i = 0; i < 5; i ++) {
        expected_24_values[i] = 0;
    }
    IsingModel24_2.initialise_random(temp_24);
    IsingModel24_2.simulate(cycles, expected_24_values);
    IsingModel24_2.write_to_terminal(cycles);

    Ising IsingModel1_20 = Ising(dim, "expectations20_1_up.txt");
    for (int i = 0; i < 5; i ++) {
        expected_20_values_1[i] = 0;
    }
    IsingModel1_20.initialise_Up(1);
    IsingModel1_20.simulate(cycles, expected_20_values_1);
    IsingModel1_20.write_to_terminal(cycles);

    Ising IsingModel24_20 = Ising(dim, "expectations20_24_up.txt");
    for (int i = 0; i < 5; i ++) {
        expected_20_values_24[i] = 0;
    }
    IsingModel24_20.initialise_Up(temp_24);
    IsingModel24_20.simulate(cycles, expected_20_values_24);
    IsingModel24_20.write_to_terminal(cycles);
*/

    return 0;
}
