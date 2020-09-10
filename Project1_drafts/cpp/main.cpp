#include<fstream>
#include<iostream>
#include<cmath>
#include<iomanip>
#include "time.h"
#include<string>

using namespace std;

//Declarations, definitions below.
void init_arrs(int,double*,double*,double*,double*,double*,double[2]);
void do_thomas(int,double*,double*,double*,double*,double*);
void write_to_file(int,string,double*,double);

int main(int argc, char *argv[]){
	//Get Command-Line Args. These are ./program n bc_left bc_right
	int n = atoi(argv[1]);
	double bc[2];
	bc[0] = atof(argv[2]);
	bc[1] = atof(argv[3]);
	cout << "Running for n="<<n<<" with BC: u(0)=" << bc[0] << ", u(1)=" << bc[1] << endl;
	//Allocate dynamically and initialize.
	double *a, *b, *c, *rhs, *result;
	a = new double[n];
	b = new double[n];
	c = new double[n];
	rhs = new double[n-1];
	result = new double[n+1];
	init_arrs(n,a,b,c,rhs,result,bc);
	//Do Thomas, and time him
	clock_t start, finish;
	start = clock();
	do_thomas(n,a,b,c,rhs,result);
	finish = clock();
	double calc_time = (double) (finish-start)/(CLOCKS_PER_SEC);
	cout << "Thomas took t=" << calc_time << "s to perform" << endl;
	//Write output file
	string fname = "out"+to_string(n)+".dat";
	write_to_file(n+1,fname,result,calc_time);
	return 0;
}


void init_arrs(int N, double *A, double *B, double *C, double *RHS, double *RESULT,double BC[2]){
	double h = 1/((double)N-1);
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
	RHS[0] -= A[0]*BC[0];
	RHS[N-2] -= C[N-1]*BC[1];
	RESULT[0] = BC[0];
	RESULT[N] = BC[1];
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
	RESULT[N-1]=RHS[N-2]/B[N-2];
	for(int i=N-3;i>-1;i--){
		RESULT[i+1]=(RHS[i]-C[i]*RESULT[i+2])/B[i];
	}
}

void write_to_file(int N,string fname,double *arr,double T){
	int w = 10;
	double h = 1/((double)N-1);
	ofstream out_file;
	out_file.open(fname);
	out_file << left << setw(w) << "n" << "   " <<"time=" << endl;
	out_file  << setw(w) << N-1 << setprecision(8) << "   " << T << endl;
	out_file  << setw(w) << "x" << "   " << "u_calc" << endl;
	for(int i=0;i<N;i++){
	out_file  << setw(w) << setprecision(8)<< (double)i*h << "   " << arr[i] << endl;
	}
}