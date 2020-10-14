#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <armadillo>

using namespace  std;
using namespace  arma;

/* This is the first part of 2.b)
 * Where we are going to set up
 * the matrix and diagonalizing
 * using Armadillo */
void tridiagtoplitz(){

  /* Backround
   * Defining variables */
  int dim; // N, mesh points

  double rhomin, rhomax, step_l, d, a;
  rhomin = 0.0; rhomax = 1.0; dim = 10;

  // Empty 10x10 matrix
  mat A = zeros<mat>(dim,dim);

  /* Defining the step-length
   * Defining the main diagonal for the matrix
   * Defining the upper/lower diagonal */
  step_l  = (rhomax - rhomin) / dim;
  d       = 2.0 / (step_l * step_l);   // Diagonal Constant
  a       = -1.0 / (step_l * step_l); // Upper/Lower Diagonal Constant

  /* Setting up the tridiagonal matrix
   * Diagonalizing using Armadillo */
  A(0,0) = d;
  A(0,1) = a;

  for(int i = 1; i < dim-1; i++) {
    A(i,i - 1)    = a;
    A(i,i)        = d;
    A(i,i + 1)    = a;
  }

  A(dim - 1,dim - 2) = a;
  A(dim - 1,dim - 1) = d;

  /* Diagonalization
   * Obtaining eigenvalues */
  vec eigenval(dim);
  eig_sym(eigenval, A);
  double pi = acos(-1.0);        // Returns the arc cosine value

  cout << "RESULTS:" << endl;
  cout << setiosflags(ios::showpoint | ios::uppercase);                            //
  cout <<"Number of Eigenvalues = " << setw(15) << dim << endl;
  cout << "Exact versus numerical eigenvalues:" << endl;
  for(int i = 0; i < dim; i++) {
    double Exact = d + 2 * a * cos((i + 1) * pi / (dim + 1));                      // Formula for finding eigenvalues
    cout << setw(15) << setprecision(8) << fabs(eigenval[i]-Exact) << endl;

    /*
    cout << setw(15) << setprecision(8) << "Exact: " << Exact << endl;
    cout << setw(15) << setprecision(8) << "Numerical: " << eigenval[i] << endl;
    cout << "------------------------" << endl;
    */
  }

  cout << A << endl;

  return
          ;
} //  end of function
