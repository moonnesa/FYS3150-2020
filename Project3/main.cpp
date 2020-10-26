#include "wanderer.h"
#include "solar_system.h"
#include "solver.h"
// #include "vec3.h"

int main(int argc, char const *argv[]) {
  double t = 10.0;
  int n = 1000.0;
  int N = n * t;
  double h = t / N;
  //double days = 365;
  SolarSystem solsys;
  vec pos_sun = {0.0, 0.0, 0.0};
  vec vel_sun = {0.0, 0.0, 0.0};
  //vec pos_sun = {-2.082456923795519E-04, 7.269365845327120E-03,-7.116216262733176E-05};
  //vec vel_sun = {-7.605663822232906E-06 * 365., 2.520655405552306E-06 * 365.,1.901417766099408E-07 * 365.};
  //vec pos_mer = {0.02289156292778706, -0.4600322284671032,-0.03969085759251941};
  //vec vel_mer = {8.196578360432543, 1.0377015069218147, -0.667145253378925};
  //vec pos_ven = {0.6532839585525638, 0.3118181526908649, -0.03342056761761163};
  //vec vel_ven = {-3.2039605708184054, 6.630400755554966, 0.27585758405322197};
  vec pos_ea = {0.8765050557173649, 0.4715645679721272, -2.19083407643767e-05};
  vec vel_ea = {-3.077486450170032, 5.503990755581942, -0.00011290054075552127};
  //vec pos_mars = {1.389560200606188, -0.03368549892488484,-0.03480262484692486};
  //vec vel_mars = {0.31894692535400826, 5.542616316156517, 0.10831471657601702};
  //vec pos_ju = {-2.608419560286494, -4.693097675142516, 0.07785689562431203};
  //vec vel_ju = {2.3761749558256002, -1.2090920492062296, -0.04814409500285047};
  //vec pos_sat = {1.590991383504502, -9.935642578497415, 0.1093778360004679};
  //vec vel_sat = {1.9015166685195108, 0.3145811124309021, -0.0810624545684677};
  //vec pos_ur = {17.16004314238246, 10.01610951914014, -0.1850097277796742};
  //vec vel_ur = {-0.7318099098696571, 1.1717582347543574, 0.013781445340257659};
  //vec pos_nep = {28.92681014362943, -7.705393750467173, -0.5080431136761442};
  //vec vel_nep = {0.2899445471365661, 1.1130813491673965, -0.02977014473899446};
  //vec pos_pl = {11.66821433558843, -31.57899846202243, 0.003347781098132288};
  //vec vel_pl = {1.09922633030434, 0.15089959886305188, -0.3350907719193256};

  wanderer earth(pos_ea, vel_ea, 0.000003);
  wanderer sun(pos_sun, vel_sun, 1);
  //wanderer jupiter(pos_ju, vel_ju, 0.00095);
  //wanderer mercury(pos_mer, vel_mer, 1.65e-7);
  //wanderer venus(pos_ven, vel_ven, 2.45e-6);
  //wanderer mars(pos_mars, vel_mars, 3.3e-7);
  //wanderer saturn(pos_sat, vel_sat, 2.75e-4);
  //wanderer uranus(pos_ur, vel_ur, 4.4e-5);
  //wanderer neptune(pos_nep, vel_nep, 5.15e-5);
  //wanderer pluto(pos_pl, vel_pl, 6.55e-9);

  solsys.add_celestial_objects(sun);
  solsys.add_celestial_objects(earth);
  /*solsys.add_celestial_objects(mercury);
  solsys.add_celestial_objects(venus);
  solsys.add_celestial_objects(mars);
  solsys.add_celestial_objects(jupiter);
  solsys.add_celestial_objects(saturn);
  solsys.add_celestial_objects(uranus);
  solsys.add_celestial_objects(neptune);
  solsys.add_celestial_objects(pluto);
*/
  solver solar;
  solar.verlet(solsys, N, h);

  return 0;
}
