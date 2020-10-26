#ifndef WANDERER_H
#define WANDERER_H

#include "vec3.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class wanderer
{

public:
  double G;
  double mass;
  vec3 p;
  vec3 v;
  double x, y, z;
  double vx, vy, vz;
  double ax, ay, az;
  string name;
  vec3 Fg;
  double pi = M_PI;

  wanderer();
  wanderer(vec3 position, vec3 velocity, const double M, string w_name);
  string getName();
  vec3 getPosition();
  vec3 getVelocity();
  double getDistance(double radius);
  double distance(wanderer otherwanderer);
  vec3 resetForces();
  vec3 computeGForce(wanderer otherwanderer);
  vec3 acceleration(wanderer otherwanderer);
  void resetWanderer();
  // double kinetic();
  // double potential(planet otherplanet);
};

#endif // WANDERER_H
