#include "iostream"
#include "solvers.h"
#include <tuple>

using namespace std;

int main(int argc, char *argv[]){

    double t = 10.0;
    int n = 1000;
    int N = n * int(t);
    double h = 1. / double(n);
    wanderer Earth(vec3(1,0,0), vec3(0,5,0), 0.0000003, "Earth");
    /*wanderer Mercury(vec3( 3.495536068460927E-01,-1.244005354235778E-01,-4.322650728859492E-02), vec3( 4.227635822741497E-03, 2.766717966358528E-02, 1.872995651741010E-03)*365, 0.000000165, "Mercury");
    wanderer Venus(vec3(-2.014564693577006E-01, 6.979647054471583E-01, 2.085192527188221E-02), vec3(-1.954030489393017E-02, -5.617030971633074E-03, 1.050380933499449E-03)*365, 0.00000245, "Venus");
    wanderer Earth(vec3(9.197072435481757E-01, 3.769489356926712E-01, 6.612226445473284E-05), vec3(-6.680014422118789E-03, 1.591045745844236E-02, -4.285733910918290E-07)*365, 0.000003, "Earth");
    wanderer Mars(vec3(1.313182054438775E+00, 5.238027403010505E-01, -2.143298790828418E-02), vec3(-4.580673738523137E-03, 1.421746938727736E-02, 4.104620361665089E-04)*365, 0.00000033, "Mars");
    wanderer Jupiter(vec3(2.550209154629485E+00, -4.432721232593654E+00, -3.866707508925721E-02), vec3(6.447098824156304E-03, 4.121019457101368E-03, -1.613529989591600E-04)*365, 0.0001, "Jupiter");
    wanderer Saturn(vec3(5.139559304458874E+00, -8.566560707385138E+00, -5.566040857035146E-02), vec3(4.473071224059222E-03, 2.856412892846955E-03,-2.280945466479504E-04)*365, 0.0000275, "Saturn");
    wanderer Uranus(vec3(1.553730695000689E+01, 1.224236505232422E+01, -1.558191030077437E-01), vec3(-2.462967281250927E-03, 2.906026427771245E-03, 4.254080066644400E-05)*365, 0.000044, "Uranus");
    wanderer Neptune(vec3(2.941173255905554E+01, -5.468183359613734E+00,-5.652169944272230E-01), vec3(5.527763030717538E-04, 3.104458967851615E-03, -7.691920531641856E-05)*365, 0.0000515, "Neptune");
    wanderer Pluto(vec3(1.382472690342292E+01, -3.119979414554036E+01, -6.603664824603037E-01), vec3(2.943045461378601E-03, 5.994517978475793E-04, -9.154543587554921E-04)*365, 0.00000000655, "Pluto");

    wanderer Sun(vec3(0,0,0), vec3(0,0,0), 1, "Sun");
    solvers solverJS;
    solvers solverMeS;
    solvers solverES;
    //solvers solverEJ;
    solvers solverSS;
    solvers solverNS;
    solvers solverMaS;
    solvers solverVS;
    solvers solverUS;
    solvers solverPS;

    solverES.verlet(Earth, Sun, N, h, "Verlet_array_ES.txt");
    //Earth.resetWanderer();
    solverJS.verlet(Jupiter, Sun, N, h, "Verlet_array_JS.txt");
    //Jupiter.resetForces();
    solverMeS.verlet(Mercury, Sun, N, h, "Verlet_array_MeS.txt");


    //solverES.euler(Earth, Sun, N, h, "Euler_array_ES.txt");
    //Earth.resetWanderer();

    solverMaS.verlet(Mars, Sun, N, h, "Verlet_array_MaS.txt");
    solverNS.verlet(Neptune, Sun, N, h, "Verlet_array_NS.txt");
    solverSS.verlet(Saturn, Sun, N, h, "Verlet_array_SS.txt");
    solverSS.verlet(Pluto, Sun, N, h, "Verlet_array_PS.txt");
    solverSS.verlet(Venus, Sun, N, h, "Verlet_array_VS.txt");
    solverSS.verlet(Uranus, Sun, N, h, "Verlet_array_US.txt");
*/  //wanderer Earth(vec3(9.197072435481757E-01, 3.769489356926712E-01, 6.612226445473284E-05), vec3(-6.680014422118789E-03, 1.591045745844236E-02, -4.285733910918290E-07)*365, 0.000003, "Earth");
    //wanderer Jupiter(vec3(2.550209154629485E+00, -4.432721232593654E+00, -3.866707508925721E-02), vec3(6.447098824156304E-03, 4.121019457101368E-03, -1.613529989591600E-04)*365, 1, "Jupiter");
    wanderer Sun(vec3(0,0,0), vec3(0,0,0), 1, "Sun");
    //solvers solveES;
    //solveES.TBverlet(Earth, Sun, Jupiter, N, h, "EJS_array_ES.txt");
    //Earth.resetWanderer();Jupiter.resetWanderer();
    solvers solveJS;
    solveJS.verlet(Earth, Sun, N, h, "JS_array.txt");
    //solveJS.euler(Earth,Sun,N,h,"Euler_array.txt");

}
