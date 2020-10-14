#include <iostream>

#include "jacobi.h"


int main() {
    // 2.a) tridiagonal
    //tridiagtoplitz();
    //int dim = 10;
    // 2.b
    makematrix();
    //mat A= zeros<mat>(dim,dim);

    mat A = makematrix();
    std::cout << A << std::endl;
    //mat R = eye(5,5);
    int k;
    int l;
    double max = maxoffdiag(A, k, l);
    std::cout << max << std::endl << k << std::endl;
    //mat B, R = rotation(A,k,l);

    //std::cout << B << std::endl << R << std::endl;

    return 0;
}
