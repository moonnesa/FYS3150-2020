#include "solvers.h"


solvers::solvers() { radius = 1.0; }

solvers::solvers(double r) { radius = r; }
void solvers::euler(wanderer &current, wanderer &other, int n, double dt, string ofilename) {
  x = current.x;
  y = current.y;
  z = current.z;
  vx = current.vx;
  vy = current.vy;
  vz = current.vz;
  ofstream ofile, efile;


  ofile.open(ofilename);
  efile.open("ES_Energy_values_E.txt");

  for (int i = 0; i < n; i++) {

    //double r = current.distance(other);
    //vec3 a = current.acceleration();

    //cout << current.distance(other) <<endl;
    current.x += dt * current.vx;
    current.y += dt * current.vy;
    current.z += dt * current.vz;
    current.computeGForce(other);
    current.vx += current.acceleration()[0] * dt;
    current.vy += current.acceleration()[1] * dt;
    current.vz += current.acceleration()[2] * dt;
    //When using too large values for n and dt unquote this i test. this will let you write small files with output values
    //if(i%10==1){
        ofile << current.x << " " << current.y << " " << current.z << endl;
    //}
     //Printing kinetic and potetial energies for every interation in the command window to see if they are the same=conserved for circular orbit
     //cout<<current.kinetic(other)<<endl;
     //cout<<current.potential(other)<<endl;
     efile << current.kinetic(other)<<" "<< current.potential(other) << endl;

  }
  ofile.close();
  efile.close();
  return;
}
void solvers::TBverlet(wanderer &current, wanderer &other, wanderer &another, int n, double h, string ofilename) {
  x = current.x;
  y = current.y;
  z = current.z;
  vx = current.vx;
  vy = current.vy;
  vz = current.vz;

  double hh = h * h;

  ofstream ofile;
  ofile.open(ofilename);

  for (int i = 0; i < n; i++) {
    current.computeTBGForce(other,another);
    a = vec3(0,0,0);
    a += current.TBacceleration();
    //double r = current.distance(other);
    //current.p += (current.v*h) + a*(hh/2);
    current.x += (current.vx*h + a[0]*(hh/2));
    current.y += (current.vy*h + a[1]*(hh/2));
    current.z += (current.vz*h + a[2]*(hh/2));
    current.computeTBGForce(other, another);
    a_next = vec3(0,0,0);
    a_next += current.TBacceleration();
    //current.v += (a_next+a)*(h/2);
    current.vx += (a_next[0] + a[0])*(h/2);
    current.vy += (a_next[1] + a[1])*(h/2);
    current.vz += (a_next[2] + a[2])*(h/2);
    //cout << current.getPosition()[0] << " " << current.getPosition()[1] << " " << current.getPosition()[2]<< endl;
    ofile << current.x << " " << current.y << " " << current.z << endl;

  }
  ofile.close();
  return;
}
void solvers::verlet(wanderer &current, wanderer &other, int n, double h, string ofilename) {
//saving intials values
  x = current.x;
  y = current.y;
  z = current.z;
  vx = current.vx;
  vy = current.vy;
  vz = current.vz;

  double hh = h * h;

  ofstream ofile, efile;
  ofile.open(ofilename);
  efile.open("ES_Energy_values_V.txt");

  for (int i = 0; i < n; i++) {
    current.computeGForce(other);
    a = vec3(0,0,0);
    a += current.acceleration();
    //double r = current.distance(other);
    //current.p += (current.v*h) + a*(hh/2);
    current.x += (current.vx*h + a[0]*(hh/2));
    current.y += (current.vy*h + a[1]*(hh/2));
    current.z += (current.vz*h + a[2]*(hh/2));
    current.computeGForce(other);
    a_next = vec3(0,0,0);
    a_next += current.acceleration();
    //current.v += (a_next+a)*(h/2);
    current.vx += (a_next[0] + a[0])*(h/2);
    current.vy += (a_next[1] + a[1])*(h/2);
    current.vz += (a_next[2] + a[2])*(h/2);
    //cout << current.getPosition()[0] << " " << current.getPosition()[1] << " " << current.getPosition()[2]<< endl;
    //if(i%10==1){
    ofile << current.x << " " << current.y << " " << current.z << endl;
    //cout <<current.distance(other)<<endl;
    //}
    //vec3 velocities = vec3 (current.vx, current.vy, current.vz);
    //cout << current.angularMomentum(velocities)<<endl;
    //cout<<current.kinetic(other)<<endl;
    //cout<<current.potential(other)<<endl;
    //cout<<current.TotalEnergy(other)<<endl;
    efile << current.kinetic(other)<<" "<< current.potential(other) <<" "<<current.TotalEnergy(other)<< endl;
  }
  ofile.close();
  efile.close();
  return;
}
