#ifndef wanderer_H
#define wanderer_H

// #include "vec3.h"
// #include "solar_system.h"
// #include "solver.h"
#include <armadillo>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#define _USE_MATH_DEFINES

using std::vector;
using namespace std;
using namespace arma;

class wanderer {
private:
  double G = 4 * pow(M_PI, 2);

public:
  double mass;
  vec position;
  vec velocity;
  vec acceleration;
  double x, y, z;
  double vx, vy, vz;
  double ax, ay, az;
  vec gforce;
  double pi = M_PI;

  wanderer();
  ~wanderer() {}
  wanderer(vec position, vec velocity, const double M);
  double distance(wanderer otherwanderer);
  vec GForce(wanderer otherwanderer);
  vec accel(wanderer otherwanderer);
  double kinetic(wanderer otherwanderer);
  double potential(wanderer otherwanderer);
};

#endif // wanderer_H
