#include<fstream>
#include<iostream>
#include<cmath>
#include<iomanip>
#include "time.h"
#include<string>

// THIS WORKS FINE, BUT DOES NOT ADD ENDPOINTS AND CAN NOT DEAL WITH OTHER BCs

using namespace std;

void init_arrs(int,double*,double*,double*,double*,double*);
void do_thomas(int,double*,double*,double*,double*,double*);
void write_to_file(int,string,double*);

int main(int argc, char *argv[]){
	//Get Command Line Arg.
	int n = atoi(argv[1]);
	//Allocate Dynamically and initialize.
	double *a, *b, *c, *rhs, *result;
	a = new double[n];
	b = new double[n];
	c = new double[n];
	rhs = new double[n-1];
	result = new double[n-1];
	init_arrs(n,a,b,c,rhs,result);
	//Do Thomas
	do_thomas(n,a,b,c,rhs,result);
	//Write Output File
	string fname = "out"+to_string(n)+".dat";
	write_to_file(n-1,fname,result);
	return 0;
}


void init_arrs(int N, double *A, double *B, double *C, double *RHS, double *RESULT){
	double h = 1/((double)N);
	double h2 = h*h;
	for (int i=0;i<N-1;i++){
		double x = (i+1)*h;
		RHS[i] = h2*100*exp(-10*x);
	}
	for (int i=0;i<N;i++){
		A[i]= -1.0;
		B[i]= 2.0;
		C[i]= -1.0;
	}
	//Can do BC's here
	RHS[0] -= 0;
	RHS[N-2] -= 0;
}

void do_thomas(int N, double *A, double *B, double *C, double *RHS, double *RESULT){
	double scalar;
	//Forw. elim.
	for(int i=1;i<N-1;i++){
		scalar = A[i]/B[i-1];
		B[i] -= scalar*C[i-1];
		RHS[i] -= scalar*RHS[i-1];
	}
	//Back. sub.
	RESULT[N-2]=RHS[N-2]/B[N-2];
	for(int i=N-3;i>-1;i--){
		RESULT[i]=(RHS[i]-C[i]*RESULT[i+1])/B[i];
	}
}

void write_to_file(int N,string fname,double *arr){
	ofstream out_file;
	out_file.open(fname);
	for(int i=0;i<N;i++){
	out_file << setw(15) << setprecision(8) << arr[i] << endl;
	}
}

