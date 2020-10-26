#include "iostream"
#include "solvers.h"
#include <tuple>

using namespace std;

int main(int argc, char *argv[]){

    double t = 10.0;
    int n = 1000;
    int N = n * int(t);
    double h = t / N;
    wanderer Earth(vec3(9.197072435481757E-01, 3.769489356926712E-01, 6.612226445473284E-05), vec3(-6.680014422118789E-03, 1.591045745844236E-02,-4.285733910918290E-07)*365, 0.0000003, "Earth");
    //wanderer Jupiter(vec3(2.550209154629485E+00, -4.432721232593654E+00, -3.866707508925721E-02), vec3(6.447098824156304E-03, 4.121019457101368E-03, -1.613529989591600E-04)*365, 0.0001, "Jupiter");
    //Jupiter.resetWanderer();
    //wanderer Mercury(vec3(3.495536068460927E-01, -1.244005354235778E-01, -4.322650728859492E-02), vec3(4.227635822741497E-03, 2.766717966358528E-02, 1.872995651741010E-03)*365, 0.0000000165, "Mercury");
    //Mercury.resetWanderer();
    //wanderer Saturn(vec3(5.139559304458874E+00, -8.566560707385138E+00, -5.566040857035146E-02), vec3(4.473071224059222E-03, 2.856412892846955E-03, -2.280945466479504E-04)*365, 0.0000275, "Saturn");
    //Saturn.resetWanderer();
    wanderer Sun(vec3(0,0,0), vec3(0,0,0), 1, "Sun");
    //Sun.resetWanderer();
    // cout << planet1.distance(planet2) << endl;
    //vec3 Fg = Earth.GForce(Sun);
    //solvers solverJS(Jupiter.distance(Sun));
    //solvers solverMS(Mercury.distance(Sun));
    solvers solverES;
    //solvers solverSS(Saturn.distance(Sun));
    //double M = 2*pow(10,30);
    //cout << Earth.distance(Sun) << endl;
    //cout << Earth.GForce(Sun) << endl;
    //cout << sqrt(2*(4 * pow(M_PI, 2))*1) << endl;

    solverES.verlet(Earth, Sun, N, h, "Verlet_array_ES.txt");
    //solverES.euler(Earth, Sun, N, h, "Euler_array_ES.txt");
    Earth.resetWanderer();

    //solverMS.verlet(Mercury, Sun, N, h, "Verlet_array_MS.txt");
    //solverJS.verlet(Jupiter, Sun, N, h, "Verlet_array_JS.txt");
    //solverSS.verlet(Saturn, Sun, N, h, "Verlet_array_SS.txt");


}
