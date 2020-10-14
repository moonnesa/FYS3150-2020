#ifndef JACOBI_H
#define JACOBI_H


#include<iostream>
#include<fstream>
#include<math.h>
#include<iomanip>
#include<time.h>
#include<algorithm>
#include<vector>
#include<armadillo>

using namespace arma;

mat makematrix() {
    unsigned int dim=10; // N, mesh points
    double rhomin, rhomax, step_l, d, a;
    rhomin = 0.0; rhomax = 1.0;




    /* Defining the step-length
    * Defining the main diagonal for the matrix
    * Defining the upper/lower diagonal */
    step_l  = (rhomax - rhomin) / dim;
    d       = 2.0 / (step_l * step_l);   // Diagonal Constant
    a       = -1.0 / (step_l * step_l); // Upper/Lower Diagonal Constant

    // Empty Dim x Dim matrix
    mat A = zeros<mat>(dim,dim);

    /* Setting up the tridiagonal matrix
     * Diagonalizing using Armadillo */
    A(0,0) = d;
    A(0,1) = a;

    for(unsigned int i = 1; i < dim-1; i++) {
      A(i,i - 1)    = a;
      A(i,i)        = d;
      A(i,i + 1)    = a;
    }

    A(dim - 1,dim - 2) = a;
    A(dim - 1,dim - 1) = d;

    // Returns the matrix
    return A;
}

/* Algoritm for finding the maximum diagonal-matrix element
 * From lecture-notes Ch.7 */
double maxoffdiag(mat A, int k, int l){
    int dim=10;
    double max = 0.0;
    //std::cout<<"maxoffdiag"<<std::endl;
    //std::cout << A << std::endl;
    for(int i=0; i < dim; i++){
        for(int j=i+1; j < dim; j++){
            if (fabs(A(i,j) > max)){
                max = fabs(A(i,j));
                l = i;
                k = j;
            }
        }
    }

    return max;
}

/* Rotation algoritm
 * For finding sine and cosine
 * From lecture-notes Ch. 7 */
void rotation(mat A, mat R, int k, int l){
    int dim=10;
    double c, s;
    //double theta;

    //s=sin(theta), c=cos(theta);

    // Defining the variables

    // Tau
    double tau;
    tau = (A(l,l) - A(k,k)) / (2*A(k,l));
    //tau =cot(2*theta);

    double t;
    // t = tan(theta);
    // Value 't' can be either positive or negative
    if (tau >= 0){
        t = 1.0/(tau + sqrt(1 + pow(tau, 2)));
    } else {
        t = -1.0/(-tau + sqrt(1 + pow(tau, 2)));
    }
    // Sine and cosine
    c = 1.0 / (sqrt(1 + pow(t,2)));
    s = c * t;

    // Division by zero
    if (A(k,l) == 0) {
        s = 1.0; c = 0.0;
    }


    double a_kk, a_ll, a_ik, a_il, r_ik, r_il;
    a_kk = A(k,k);
    a_ll = A(l,l);

    A(k,k) = a_kk * c * c - 2 * A(k,l) * c * s + a_ll * s * s;
    A(l,l) = a_ll * c * c + 2 * A(k,l) * c * s + a_kk * s * s;
    A(l,k) = 0.0; // Non-diagonal elements
    A(k,l) = 0.0;

    for (int i=0; i < dim; i++) {
        if (i != k && i !=l) {

            a_ik = A(i,k);
            a_il = A(i,l);
            A(i,k) = a_ik * c - a_il * s;
            A(k,i) = A(i,k);
            A(i,l) = a_il * c + a_ik * s;
            A(l,i) = A(i,l);
        }

    // Theese are the new eigenvectors
        r_ik = R(i,k);
        r_il = R(i,l);
        R(i,k) = c * r_ik - s * r_il;
        R(i,l) = c * r_il + s * r_ik;

    }


}

void jacobimethod(mat &A, mat &R) {
    int dim=10;
    int k, l = 0;
    double eps = 1.0E-8;
    // Maximum number of iterations
    int maxiter = dim * dim * dim;
    int iteration = 0;
    double max_offdiag = maxoffdiag(A, k, l);

    // The rotation algoritm
    while (max_offdiag > eps &&  iteration <= maxiter){
        rotation(A, R, k, l);
        max_offdiag = maxoffdiag(A,k,l);
        iteration++;
    }


    /*int groundStateCol = 0;
    for (int i = 0; i < Dim; i ++) {
        if (A(groundStateCol,groundStateCol) < A(i,i)) {
            groundStateCol = i;
        }
    }

    // Passing to global
    int index;
    index = groundStateCol;*/

    std::cout << "Iterations: " << iteration << std::endl;
}
void writefile(mat &R, std::string filename){
    int dim=10;
    int index;
    std::ofstream ofile;
    ofile.open(filename.c_str());

    for (int i = 0; i < dim; i++) {
        ofile << R(i,index) << std::endl;
     }
     ofile << std::endl;

     ofile.close();
}

#include<assert.h>
/* This is part 2c)
 * In this part, we are going to test
 * The eigenvalues of the matrix
 * and orthogonality */
void testeigen(){

    std::cout << "CALCULATING KNOWN EIGENVALUES! ";

    // Testing with a 5x5 matrix
    int dim=5;

    mat A;
    mat R;
    R.eye(dim,dim);

    //A simple 5x5 test matrix
    A << 1 << 1 << 1 << 1 << 1 << endr
      << 2 << 2 << 2 << 2 << 2 << endr
      << 0 << 0 << 0 << 0 << 0 << endr
      << 1 << 1 << 1 << 1 << 1 << endr
      << 2 << 2 << 2 << 2 << 2 << endr;

    // Givint the eigenvalues for the 5x5 matrix A
    double* v = new double[dim];
    v[0] = 6.0;
    v[1] = 0.0;
    v[2] = 0.0;
    v[3] = 0.0;
    v[4] = 0.0;

    // Defining a tolerance
    double eps = 1.0E-8;

    // fill A with eigenvalues
    jacobimethod(A,R);

    // test booleans
    bool s1 = false;
    bool s2 = false;
    bool s3 = false;
    bool s4 = false;
    bool s5 = false;

    // Here we check if there is difference between exact and numerical value
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            s1 = s1 || (abs(A(i,j) - v[0]) < eps);
            s2 = s2 || (abs(A(i,j) - v[1]) < eps);
            s3 = s3 || (abs(A(i,j) - v[2]) < eps);
            s4 = s4 || (abs(A(i,j) - v[3]) < eps);
            s5 = s5 || (abs(A(i,j) - v[4]) < eps);
        }
    }

    // Assertion
    assert(s1);
    assert(s2);
    assert(s3);
    assert(s4);
    assert(s5);

    std::cout << " SUCCESS " << std::endl;
    delete [] v;
}

#endif // JACOBI_H
