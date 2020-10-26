#include "wanderer.h"
//#include "solver.h"
// #include "vec3.h"

// Default constructor
wanderer::wanderer() {

  mass = 1.;
  position = {0, 0, 0};
  velocity = {0, 0, 0};
  x = position(0);
  y = position(1);
  z = position(2);
  vx = velocity(0);
  vy = velocity(1);
  vz = velocity(2);
}

// Constructor creating a wanderer object with known initial condition
wanderer::wanderer(vec pos, vec vel, const double M) {

  mass = M;
  position = pos;
  velocity = vel;
  x = position(0);
  y = position(1);
  z = position(2);
  vx = velocity(0);
  vy = velocity(1);
  vz = velocity(2);
}

// Finds the distance between two objects of the wanderer class
double wanderer::distance(wanderer otherwanderer) {
  double delta_x = this->x - otherwanderer.x;
  double delta_y = this->y - otherwanderer.y;
  double delta_z = this->z - otherwanderer.z;
  // vec dr;
  // dr = this->position-otherwanderer.position;
  return sqrt(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z);
  // return sqrt(dr%dr);
}

vec wanderer::GForce(wanderer otherwanderer) {
  double M1, M2, r;
  vec gforce = zeros(3);
  M1 = this->mass;
  M2 = otherwanderer.mass;
  r = distance(otherwanderer);
  gforce(0) = -G * (M2 * M1 / pow(r, 3)) * (this->x - otherwanderer.x);
  gforce(1) = -G * (M2 * M1 / pow(r, 3)) * (this->y - otherwanderer.y);
  gforce(2) = -G * (M2 * M1 / pow(r, 3)) * (this->z - otherwanderer.z);
  return gforce;
}

vec wanderer::accel(wanderer otherwanderer) {
  acceleration = zeros(3);
  double M2 = otherwanderer.mass;
  double r = distance(otherwanderer);
  acceleration(0) = -G * M2 * (this->x - otherwanderer.x) / pow(r, 3);
  acceleration(1) = -G * M2 * (this->y - otherwanderer.y) / pow(r, 3);
  acceleration(2) = -G * M2 * (this->z - otherwanderer.z) / pow(r, 3);
  return acceleration;
}

double wanderer::kinetic(wanderer otherwanderer) {
  double r = this->distance(otherwanderer);
  return 0.5 * this->mass * (pow(r, 2));
}
double wanderer::potential(wanderer otherwanderer) {
  return -G*(this->mass * otherwanderer.mass) / distance(otherwanderer);
}
