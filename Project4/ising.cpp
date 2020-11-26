#include "ising.h"
#include <iomanip>
#include <iostream>
#include <time.h>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include "lib.h"

Ising::Ising(int lattice_dimension, string filename) {

    this->lattice_dimension = lattice_dimension;
    this->nr_of_spins = lattice_dimension*lattice_dimension;
    this->expectations_filename = filename;



    //lattice = arma::mat(lattice_dimension, lattice_dimension);
    this->lattice = (int**) matrix(lattice_dimension, lattice_dimension, sizeof(double));

    energy = 0;
    magnetisation = 0;

}

void Ising::initialise_random(double temp) {
    temperature = temp;

    // Reset variables
    energy = 0;
    magnetisation = 0;
    nr_of_accepted_states = 0;
    specific_heat=0;
    susceptibility=0;
    expected_abs_magnetisation=0;

    // Possible energies
    for (int i = -8; i <= 8; i++) dEnergy[i + 8] = 0;
    for (int i = -8; i <= 8; i += 4) dEnergy[i + 8] = exp(-i/temperature);

    // Time as seed for random number generator
    srand(time(NULL));

    for (int i = 0; i < lattice_dimension; i++) {
        for (int j = 0; j < lattice_dimension; j++) {

            // Start in random configuration
            lattice[i][j] = ((int(rand() / (RAND_MAX)) > 0.5) ? 1: -1);

            // Magnetisation
            magnetisation += lattice[i][j];

        }
    }

    // Initial energy - Mulitply every sites spin direction with neighbhours
    for (int i = 0; i < lattice_dimension; ++i) {
        for (int j = 0; j < lattice_dimension; ++j) {
            energy -= lattice[i][j] * (lattice[periodic_boundary_translation(i, lattice_dimension, -1)][j] +  lattice[i][periodic_boundary_translation(j, lattice_dimension, -1)]);
        }
    }
    cout<<setw(25)<<"initializing random"<<endl;
}
void Ising::initialise_Up(double temp) {
    temperature = temp;

    // Reset variables
    energy = 0;
    magnetisation = 0;
    nr_of_accepted_states = 0;
    specific_heat=0;
    susceptibility=0;
    expected_abs_magnetisation=0;

    // Possible energies
    for (int i = -8; i <= 8; i++) dEnergy[i + 8] = 0;
    for (int i = -8; i <= 8; i += 4) dEnergy[i + 8] = exp(-i/temperature);

    for (int i = 0; i < lattice_dimension; i++) {
        for (int j = 0; j < lattice_dimension; j++) {

            // Start in all spins up configuration
            lattice[i][j] = 1;

            // Magnetisation
            magnetisation += lattice[i][j];

        }
    }

    // Initial energy - Mulitply every sites spin direction with neighbhours
    for (int i = 0; i < lattice_dimension; ++i) {
        for (int j = 0; j < lattice_dimension; ++j) {
            energy -= lattice[i][j] * (lattice[periodic_boundary_translation(i, lattice_dimension, -1)][j] +  lattice[i][periodic_boundary_translation(j, lattice_dimension, -1)]);
        }
    }
    cout<<setw(25)<<"initializing Up"<<endl;
}

void Ising::simulate(int cycles, double expected_values[5]) {
    cout<<setw(25)<<"simulating"<<endl;


    for (int i = 0; i <= cycles; i++) {

        metropolis();

            expected_values[0] += energy;
            expected_values[1] += energy*energy;
            expected_values[2] += magnetisation;
            expected_values[3] += magnetisation*magnetisation;
            expected_values[4] += fabs(magnetisation);
            //output(i, expected_values);

    }

    output(cycles, expected_values);

    // Divide by total number of cycles in order to get expected values
    double normalising_coeff = 1.0 / ((double) cycles);
    double ev_E  = expected_values[0] * normalising_coeff;
    double ev_E2 = expected_values[1] * normalising_coeff;
    double ev_M  = expected_values[2] * normalising_coeff;
    double ev_M2 = expected_values[3] * normalising_coeff;
    double ev_Ma = expected_values[4] * normalising_coeff;

    // Variance
    double var_E = (ev_E2 - ev_E*ev_E) / nr_of_spins;
    double var_M = (ev_M2 - ev_Ma*ev_Ma) / nr_of_spins;

    // The expected quantities
    expected_energy 		= ev_E / nr_of_spins;
    expected_magnetisation 	= ev_M / nr_of_spins;
    specific_heat			= var_E / (temperature*temperature);
    susceptibility			= var_M / temperature;
    expected_abs_magnetisation 	= ev_Ma / nr_of_spins;
}

// Metropolis-Hastings. One single Monte-Carlo step.
void Ising::metropolis() {
    for (int i = 0; i < nr_of_spins; i++) {
        int random_x = rand() % lattice_dimension;
        int random_y = rand() % lattice_dimension;

        int delta_E = get_energy_of_site(random_x, random_y);

        if (( double(rand()) * 1. / RAND_MAX) <= dEnergy[delta_E + 8]) {

            lattice[random_x][random_y] = -1 * lattice[random_x][random_y];
            magnetisation += (double) 2 * lattice[random_x][random_y];
            energy += (double) delta_E;
            nr_of_accepted_states++;

        }
    }
}

// Calculates
int Ising::get_energy_of_site(int x, int y) {
    int north = lattice[x][periodic_boundary_translation(y, lattice_dimension, -1)];
    int south = lattice[x][periodic_boundary_translation(y, lattice_dimension, 1)];
    int east  = lattice[periodic_boundary_translation(x, lattice_dimension, +1)][y];
    int west  = lattice[periodic_boundary_translation(x, lattice_dimension, -1)][y];
    int self  = lattice[x][y];
    return 2 * self * (north + south + east + west);
    //cout<<setw(25)<<"get energy"<<endl;
}

// Periodic boundary conditions: "wraps around"
int Ising::periodic_boundary_translation(int x, int dim, int trans) {
    return (x + dim + trans) % dim;
}

void Ising::write_to_terminal(int cycle) {
    using namespace std;
    cout << setw(25) << "Logarithm of MC_cycles: " << setw(10) << setprecision(8) << (log10(cycle))<<endl;
    cout << setw(25) << "Temperature: " << setw(10) << setprecision(8) << temperature << endl;
    cout << setw(25) << "Expected energy: " << setw(10) << setprecision(8) << expected_energy << endl;
    cout << setw(25) << "Specific heat: " << setw(10) << setprecision(8) << specific_heat << endl;
    cout << setw(25) << "Susceptibility: " << setw(10) << setprecision(8) << susceptibility << endl;
    cout << setw(25) << "Expected abs. magnetis.: " << setw(10) << setprecision(8) << expected_abs_magnetisation << endl;
    cout << setw(25) << "Expected magnetisation: " << setw(10) << setprecision(8) << expected_magnetisation << endl;
    cout << setw(25) << "Number of Accepted States: " << setw(10) << setprecision(8) << nr_of_accepted_states << endl;
    cout<<setw(25)<<"wrote to terminal"<<endl;
}


void Ising::output(int cycle, double expected_values[5]) {
    // Divide by total number of cycles in order to get expected values
    double normalising_coeff = 1.0 / ((double) cycle);


    // Normalising
    double ev_E  = expected_values[0] * normalising_coeff;
    double ev_E2 = expected_values[1] * normalising_coeff;
    double ev_M  = expected_values[2] * normalising_coeff;
    double ev_M2 = expected_values[3] * normalising_coeff;
    double ev_Ma = expected_values[4] * normalising_coeff;

    // Variance
    double var_E = (ev_E2 - ev_E*ev_E) / nr_of_spins;
    double var_M = (ev_M2 - ev_Ma*ev_Ma) / nr_of_spins;

    // The expected quantities
    expected_energy 		= ev_E / nr_of_spins;
    expected_magnetisation 	= ev_M / nr_of_spins;
    specific_heat			= var_E / (temperature*temperature);
    susceptibility			= var_M / temperature;
    expected_abs_magnetisation 	= ev_Ma / nr_of_spins;

    using namespace  std;
    ofstream ofile;
    ofile.open(expectations_filename, ios::app);
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << setw(15) << setprecision(8) << (log10(cycle));
    ofile << setw(15) << setprecision(8) << temperature;
    ofile << setw(15) << setprecision(8) << expected_energy;
    ofile << setw(15) << setprecision(8) << specific_heat;
    ofile << setw(15) << setprecision(8) << expected_magnetisation;
    ofile << setw(15) << setprecision(8) << susceptibility;
    ofile << setw(15) << setprecision(8) << expected_abs_magnetisation;
    ofile << setw(15) << setprecision(8) << nr_of_accepted_states << endl;
    ofile.close();

    //cout<<setw(25)<<"outputting"<<endl;
}
