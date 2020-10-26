#include "solvers.h"


solvers::solvers() { radius = 1.0; }

solvers::solvers(double r) { radius = r; }
void solvers::euler(wanderer &current, wanderer &other, int n, double timestep, string ofilename) {
  x = current.x;
  y = current.y;
  z = current.z;
  vx = current.vx;
  vy = current.vy;
  vz = current.vz;
  ofstream ofile;


  ofile.open(ofilename);

  for (int i = 0; i < n; i++) {
    current.computeGForce(other);
    //cout << current.computeGForce(other) << endl;
    //double r = current.distance(other);
    //current.getVelocity() += timestep;
    //vx += -h * (4 * pow(M_PI, 2) / pow(r, 3)) * x;
    //vy += -h * (4 * pow(M_PI, 2) / pow(r, 3)) * y;
    //vz += -h * (4 * pow(M_PI, 2) / pow(r, 3)) * z;
    current.v += (current.acceleration(other))*timestep;
    current.p += current.v*timestep;

    cout << current.v << current.p << endl;

    //x += h * vx;
    //y += h * vy;
    //z += h * vz;

    if(i%10 == 0)
        ofile << current.getPosition()[0] << " " << current.getPosition()[1] << " " << current.getPosition()[2] << endl;

  }
  ofile.close();
  return;
}
void solvers::verlet(wanderer &current, wanderer &other, int n, double h, string ofilename) {
  x = current.x;
  y = current.y;
  z = current.z;
  vx = current.vx;
  vy = current.vy;
  vz = current.vz;
  //double tmp_ax, tmp_ay, tmp_az;
  double hh = h * h;

  ofstream ofile;
  ofile.open(ofilename);

  for (int i = 0; i < n; i++) {  
    a_next = current.acceleration(other);
    //double r = current.distance(other);
    current.p = current.p + (current.v*h + a*(hh/2));
    current.v = current.v + (a_next + current.acceleration(other))*(h/2);
    current.computeGForce(other);
    a_next += current.acceleration(other);

//    tmp_ax = -4 * (pi * pi * x) / pow(r, 3.9);
//    tmp_ay = -4 * (pi * pi * y) / pow(r, 3.9);
//    tmp_az = -4 * (pi * pi * z) / pow(r, 3.9);
//    x = x + h * vx + (hh / 2) * tmp_ax;
//    y = y + h * vy + (hh / 2) * tmp_ay;
//    z = z + h * vz + (hh / 2) * tmp_az;
//    // cout << tmpax << endl;
//    // a = current.accel(other);
//    ax = -4 * (pi * pi * x) / pow(r, 3.9);
//    ay = -4 * (pi * pi * y) / pow(r, 3.9);
//    az = -4 * (pi * pi * z) / pow(r, 3.9);
//    //cout << ax << ay << endl;
//    vx = vx + (h / 2) * (ax + tmp_ax);
//    vy = vy + (h / 2) * (ay + tmp_ay);
//    vz = vz + (h / 2) * (az + tmp_az);
    //cout << current.getPosition()[0] << " " << current.getPosition()[1] << " " << current.getPosition()[2]<< endl;
    ofile << current.getPosition()[0] << " " << current.getPosition()[1] << " " << current.getPosition()[2] << endl;


  }

  ofile.close();
  return;
}
