#ifndef solar_system_H
#define solar_system_H

#define _USE_MATH_DEFINES

#include "wanderer.h"
#include <armadillo>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using namespace arma;

class SolarSystem {
private:
  double G = 4 * M_PI * M_PI;

public:
  vector<wanderer> celestial_objects;

  // Methods
  SolarSystem();
  SolarSystem(vector<wanderer> init_cel_obj);
  ~SolarSystem(){};
  int length();
  void add_celestial_objects(wanderer wanderer);
  mat Forces();
  mat accel();
  vector<wanderer> &objects();
  // mat position();
  // mat velocity();
};

#endif // solar_system_H
