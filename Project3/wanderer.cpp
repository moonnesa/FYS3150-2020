#include "wanderer.h"


wanderer::wanderer(){
    p = vec3(0,0,0);
    v = vec3(0,0,0);
    x=0;
    y=0;
    z=0;
    vx=0;
    vy=0;
    vz=0;
    mass = 0.;
    name = "";
}

wanderer::wanderer(vec3 position, vec3 velocity, const double M, string N) {
    p = position;
    v = velocity;
    x=p[0];
    y=p[1];
    z=p[2];
    vx=v[0];
    vy=v[1];
    vz=v[1];
    mass = M;
    name = N;

}

string wanderer::getName(){
    return name;
}

vec3 wanderer::getPosition(){
    return p;
}
vec3 wanderer::getVelocity(){
    return v;
}

double wanderer::getDistance(double radius) {
     return radius;
}
//Distance between two planets/wanderers or a wanderer and sun, at the initial positions
double wanderer::distance(wanderer otherwanderer) {
    /*double dx = this->x-otherwanderer.x;
    double dy = this->y-otherwanderer.y;
    double dz = this->z-otherwanderer.z;
    return sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));*/
    return (p-otherwanderer.p).length();
}

vec3 wanderer::resetForces(){
    Fg = vec3(0,0,0);
    return Fg;

}
//Three body Force caculation
vec3 wanderer::computeTBGForce(wanderer otherwanderer, wanderer anotherone) {
    double M1, M2, M3, r;
    Fg = vec3(0,0,0);
    M1 = mass;
    M2 = otherwanderer.mass;
    M3 = anotherone.mass;
    r = distance(otherwanderer);
    //r = 1.0;
    Fg[0] = (- ((M2 * M1) / pow(r, 3)))*(this->x-otherwanderer.x);
    Fg[1] = (- ((M2 * M1) / pow(r, 3)))*(this->y-otherwanderer.y);
    Fg[2] = (- ((M2 * M1) / pow(r, 3)))*(this->z-otherwanderer.z);
    Fg_E_J[0] = (- ((M3 * M1) / pow(r, 3)))*(this->x-anotherone.x);
    Fg_E_J[1] = (- ((M3 * M1) / pow(r, 3)))*(this->y-anotherone.y);
    Fg_E_J[2] = (- ((M3 * M1) / pow(r, 3)))*(this->z-anotherone.z);

    //cout << p[0] <<" "<<p[1]<<" "<<p[2]<< endl;
    return (Fg+Fg_E_J)*G;
}
// Two body and Multi body force calculation
vec3 wanderer::computeGForce(wanderer otherwanderer) {
    double M1, M2, r;
    Fg = vec3(0,0,0);
    M1 = mass;
    M2 = otherwanderer.mass;
    r = this->distance(otherwanderer);
    //r = 1.0;
    Fg[0] = (-(M2 * M1) / pow(r, 4))*(this->x-otherwanderer.x);
    Fg[1] = (-(M2 * M1) / pow(r, 4))*(this->y-otherwanderer.y);
    Fg[2] = (-(M2 * M1) / pow(r, 4))*(this->z-otherwanderer.z);
    //cout << p[0] <<" "<<p[1]<<" "<<p[2]<< endl;
    return Fg*G;
}
// Two body and Multi body Acceleration calculation
vec3 wanderer::acceleration() {
    vec3 acceleration = vec3(0,0,0);
    //double M2 = otherwanderer.mass;
    //double r = distance(otherwanderer);
    acceleration[0] = (Fg[0])/mass;
    acceleration[1] = (Fg[1])/mass;
    acceleration[2] = (Fg[2])/mass;
    return acceleration*G;
}
//Three body Acceleration caculation
vec3 wanderer::TBacceleration() {
    vec3 acceleration = vec3(0,0,0);
    //double M2 = otherwanderer.mass;
    //double r = distance(otherwanderer);
    acceleration[0] = ((Fg+Fg_E_J)[0])/mass;
    acceleration[1] = ((Fg+Fg_E_J)[1])/mass;
    acceleration[2] = ((Fg+Fg_E_J)[2])/mass;
    return acceleration*G;
}

double wanderer::kinetic(wanderer otherwanderer) {
    double dx = this->x-otherwanderer.x;
    double dy = this->y-otherwanderer.y;
    double dz = this->z-otherwanderer.z;
    double r= sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));
    return 0.5 * this->mass * (pow(r, 2));
}
double wanderer::potential(wanderer otherwanderer) {
    double dx = this->x-otherwanderer.x;
    double dy = this->y-otherwanderer.y;
    double dz = this->z-otherwanderer.z;
    double r= sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));
  return -0.5*G*(this->mass * otherwanderer.mass) / pow(r,2);
}
//Total energy for circular motion with velocity 2pi for both solver methods, comes to be Etot = Ek+Ep = 1.5e-007 - -5.92176e-006

double wanderer::TotalEnergy(wanderer otherwanderer){
    double dx = this->x-otherwanderer.x;
    double dy = this->y-otherwanderer.y;
    double dz = this->z-otherwanderer.z;
    double r = sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));
    return 0.5 * this->mass * (pow(r, 2))-(-0.5*G*(this->mass * otherwanderer.mass) / pow(r,2));
    //return this->kinetic(otherwanderer)-this->potential(otherwanderer);
}

//Reset wanderer objects
void wanderer::resetWanderer() {
    p = vec3(0,0,0);
    v = vec3(0,0,0);
    Fg = vec3(0,0,0);
    Fg_E_J = vec3(0,0,0);
    x=0;
    y=0;
    z=0;
    vx=0;
    vy=0;
    vz=0;
    mass = 0.;
    name = "";
}
