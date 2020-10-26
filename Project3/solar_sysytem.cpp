#include "wanderer.h"
#include "solar_system.h"
// #include "solver.h"

/*Initializes the SolarSystem with an empty declaration of a vector
with template wanderer which is an object from the wanderer class*/
SolarSystem::SolarSystem() { vector<wanderer> celestial_objects; }

/*Initializes the SolarSystem with a vector
with template wanderer which is an object from the wanderer class*/
SolarSystem::SolarSystem(vector<wanderer> init_cel_obj) {
  celestial_objects = init_cel_obj;
}

// Appends a wanderer object to the vector of wanderers celestial_objects
void SolarSystem::add_celestial_objects(wanderer wanderer) {
  celestial_objects.push_back(wanderer);
}
int SolarSystem::length() {
    return celestial_objects.size();
}

/*Method calculating the acceleration on one object from every other object
in the celestial_objects vector. Too save some steps the negative value */
mat SolarSystem::accel() {
  int n = celestial_objects.size(); // Number of wanderer-like objects
  // cout << "n:" << n << endl;
  vec drvec;
  double r;
  mat A = zeros(3, n); // Declaring matrix of zeros to store acceleration
  for (int i = 0; i < n; i++) {

    for (int j = i + 1; j < n; j++) {
      /* Difference in position between the current wanderer object and the next
        wanderer object*/
      drvec = celestial_objects[i].position - celestial_objects[j].position;
      // Distance between the current wanderer object with another other wanderer
      // object
      r = celestial_objects[i].distance(celestial_objects[j]);

      // Acceleration on the current object from the next objects
      A.col(i) += -G * celestial_objects[j].mass * (drvec) / pow(r, 3);
      // Acceleration for the next object from the current
      A.col(j) -= -G * celestial_objects[i].mass * (drvec) / pow(r, 3);
    }
  }
  return A;
}
/*Method for returning the referance to a vector containing the wanderers
in the Solar System object*/
vector<wanderer> &SolarSystem::objects() { return celestial_objects; }
