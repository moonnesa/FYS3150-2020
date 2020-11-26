#include <string>

class Ising {
    private:

        int lattice_dimension;
        int nr_of_spins;
        int nr_of_accepted_states;

        int** lattice;

        double dEnergy [17];
        std::string expectations_filename;

        double temperature;

        double expected_energy;
        double expected_magnetisation;
        double specific_heat;
        double susceptibility;
        double expected_abs_magnetisation;

        double energy;
        double magnetisation;

        void metropolis();

        int periodic_boundary_translation(int x, int dimension, int trans);
        int get_energy_of_site(int x, int y);
        void output(int current_cycle, double expected_values[5]);

    public:

        Ising(int lattice_dimension, std::string filename);

        void initialise_random(double temp);
        void initialise_Up(double temp);
        void simulate(int cycles, double expected_values[5]);
        void write_to_terminal(int cycle);

};
