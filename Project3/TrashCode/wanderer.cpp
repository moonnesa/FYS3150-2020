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
double wanderer::distance(wanderer otherwanderer) {
    double dx = this->x-otherwanderer.x;
    double dy = this->y-otherwanderer.y;
    double dz = this->z-otherwanderer.z;
    return sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));
}

vec3 wanderer::resetForces(){
    Fg = vec3(0,0,0);
    return Fg;

}

vec3 wanderer::computeGForce(wanderer otherwanderer) {
    double M1, M2, r;
    M1 = mass;
    M2 = otherwanderer.mass;
    G = 4 * pow(M_PI, 2)/M2;
    r = distance(otherwanderer);
    //r = 1.0;
    Fg[0] = (-G * ((M2 * M1) / pow(r, 3)))*(this->x-otherwanderer.x);
    Fg[1] = (-G * ((M2 * M1) / pow(r, 3)))*(this->y-otherwanderer.y);
    Fg[2] = (-G * ((M2 * M1) / pow(r, 3)))*(this->z-otherwanderer.z);
    //cout << p[0] <<" "<<p[1]<<" "<<p[2]<< endl;
    return Fg;
}

vec3 wanderer::acceleration(wanderer otherwanderer) {
    vec3 acceleration;
    double M2 = otherwanderer.mass;
    double r = distance(otherwanderer);
    acceleration[0] = ((-G * M2) / (pow(r, 3)))*(this->x-otherwanderer.x);
    acceleration[1] = ((-G * M2) / (pow(r, 3)))*(this->y-otherwanderer.y);
    acceleration[2] = ((-G * M2) / (pow(r, 3)))*(this->z-otherwanderer.z);
    return acceleration;
}
void wanderer::resetWanderer() {
    p = vec3(0,0,0);
    v = vec3(0,0,0);
    Fg = vec3(0,0,0);
    x=0;
    y=0;
    z=0;
    vx=0;
    vy=0;
    vz=0;
    mass = 0.;
    name = "";
}
