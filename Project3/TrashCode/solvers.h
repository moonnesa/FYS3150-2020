#ifndef SOLVERS_H
#define SOLVERS_H
#include "wanderer.h"
#include "vec3.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>


using std::vector;
using namespace std;

class solvers {
private:
  double x;
  double y;
  double z;
  double vx;
  double vy;
  double vz;
  double pi = M_PI;

public:
  vec3 a = vec3(0,0,0);
  vec3 a_next = vec3(0,0,0);
  friend class wanderer;
  double radius;

  solvers();
  solvers(double r);
  void euler(wanderer &current, wanderer &other, int n, double h, string ofilename);
  void verlet(wanderer &current, wanderer &other, int n, double h, string ofilename);
};

#endif // SOLVERS_H
