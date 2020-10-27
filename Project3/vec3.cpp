#include "vec3.h"

#include <cmath>

vec3::vec3() {

  v[0] = 0;
  v[1] = 0;
  v[2] = 0;
}

vec3::vec3(double x, double y, double z) {

  v[0] = x;
  v[1] = y;
  v[2] = z;
}


vec3::vec3(vec3 const &copy) {

  v[0] = copy.v[0];
  v[1] = copy.v[1];
  v[2] = copy.v[2];
}

vec3 &vec3::operator=(const vec3 &copy) {

  v[0] = copy.v[0];
  v[1] = copy.v[1];
  v[2] = copy.v[2];
  return *this;
}

void vec3::print() {
  cout << "[" << v[0] << ", " << v[1] << ", " << v[2] << "]" << endl;
}

void vec3::print(string name) {
    //This will print our vector in the format i.e:
    // A = [0,0,0]
  cout << name;
  print();
}

double vec3::length() const { return sqrt(lengthSquared()); }

double vec3::lengthSquared() const {
  return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}

vec3 &vec3::operator+=(const vec3 &other) {
  v[0] += other.v[0];
  v[1] += other.v[1];
  v[2] += other.v[2];
  return *this;
}


vec3 &vec3::operator-=(const vec3 &other) {
  v[0] -= other.v[0];
  v[1] -= other.v[1];
  v[2] -= other.v[2];
  return *this;
}

vec3 &vec3::operator*=(const double &other) {
  v[0] *= other;
  v[1] *= other;
  v[2] *= other;
  return *this;
}

vec3 &vec3::operator/=(const double &other) {
  v[0] /= other;
  v[1] /= other;
  v[2] /= other;
  return *this;
}
