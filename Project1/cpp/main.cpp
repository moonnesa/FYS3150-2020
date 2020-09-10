#include<fstream>
#include<iostream>
#include<cmath>
#include<iomanip>
#include "time.h"
#include<string>
#include<armadillo>

#define DEFAULT_N 10

using namespace std;
using namespace arma;


//Declarations, definitions below.
void init_arrs(int,double*,double*,double*,double*,double*,double[2]);
void init_arrs_special(int,double*,double*,double*,double[2]);
void do_thomas(int,double*,double*,double*,double*,double*);
void do_thomas_special(int,double*,double*,double*);
void write_to_file(int,string,double*,double[2],double,int);
double* get_error(int, double*);

//Config Input File
class Config{
private:
	string cfg_filename, out_filename;
	int n, loops, long_output, solver;
	double bc_left, bc_right;
public:

	Config(string fname){
		cfg_filename=fname;
		setDefault();
	}
	Config(){
		setDefault();
	}
	void setDefault(){
		//Set some default values. These can be overwritten later.
		out_filename = "OUTPUT";
		n = DEFAULT_N;
		loops = 1;
		long_output = 1;
		solver = 0;
		bc_left = 0;
		bc_right = 0;
	}
	void loadFile(){
		unsigned i1,i2;
		ifstream cfgfile;
		string str, sub;
		cfgfile.open(cfg_filename);
		while(getline(cfgfile,str)) // To get you all the lines.
        {
        	if (str.at(0)!='#'){//Comment, do nothing
        		//Temporary variables
        		i1 = str.find("=");
        		i2 = str.find("\n");
        		sub = str.substr(i1+1,i2+1-i1);
        		//Assign to memory, according to flags.
        		if (str.rfind("n",0)==0) {n = stoi(sub);}
        		else if (str.rfind("loops",0)==0) {loops = stoi(sub);}
        		else if (str.rfind("bc_left",0)==0) {bc_left = stod(sub);}
        		else if (str.rfind("bc_right",0)==0) {bc_right = stod(sub);}
        		else if (str.rfind("long_output",0)==0) {long_output = stoi(sub);}
        		else if (str.rfind("solver",0)==0) {solver = stoi(sub);}
        		else if (str.rfind("out_filename",0)==0){out_filename = sub;}
        	}
        }
		cfgfile.close();
	}
	void printInfo(){
		cout << "Loaded settings:" << endl;
		cout << "n=" << n << " | loops=" << loops << " | bc[0]=" << bc_left << " | bc[1]=" << bc_right <<" | solver=";
		switch(solver){
			case 0: cout << "general" << endl;
					break;
			case 1: cout << "constant" << endl;
					break;
			case 2: cout << "LU" << endl;
					break;
		}
		cout << "long_output=" << long_output << " | out_filename=" << out_filename  << endl;
	}
	double getBCL(){return bc_left;};
	double getBCR(){return bc_right;};
	int getN(){return n;};
	int getLoops(){return loops;};
	int getLongOutput(){return long_output;};
	int getSolver(){return solver;};
	string getOutputFile(){return out_filename;};
};

int main(int argc, char *argv[]){
	//Get Command-Line Args, initialize config.
	Config cfg;
	switch(argc){
		case 1 : 	cfg = Config();
					cout << endl <<"No config loaded. Assuming defaults. Do you want to change this? Call ./proj1 <config-file>" << endl << endl;
					break;
		case 2 : 	cfg = Config(argv[1]); //argv[1] = filename, e.g. call with ./proj1 input.cfg
					cfg.loadFile();
					break;
	}
	cfg.printInfo();

	//Define
	double calc_time=0;				//Store timing results
	clock_t start, finish;			//For timing
	int n = cfg.getN();				//Grid size. (n-1) unknowns, (n+1) total
	int loops = cfg.getLoops();		//How often the algorithm is run for time averaging
	double bc[2];					//Dirichlet BC's
	bc[0] = cfg.getBCL();
	bc[1] = cfg.getBCR();

	//Dynamic memory alloc.
	double *a, *b, *c, *rhs, *result;
	a = new double[n-1];
	b = new double[n-1];
	c = new double[n-1];
	rhs = new double[n-1];
	result = new double[n+1];

	if (cfg.getSolver()==0){
		//Do the 'normal' algorithm, where we don't assume anything about the tridiagonal elements
		for(int i=0;i<loops;i++){
			init_arrs(n,a,b,c,rhs,result,bc);
			start = clock();
			do_thomas(n,a,b,c,rhs,result);
			finish = clock();
			calc_time += (double) finish-start;
		}
		delete [] a;
		delete [] b;
		delete [] c;
		delete [] rhs;
		
	} else if (cfg.getSolver()==1){
		//Do the constant element simplification. Now we don't need to store the off-diagonal elements.
		delete [] a;
		delete [] c;
		for(int i=0;i<loops;i++){
			init_arrs_special(n,b,rhs,result,bc);
			start = clock();
			do_thomas_special(n,b,rhs,result);
			finish = clock();
			calc_time += (double) finish-start;
		}
		delete [] b;
		delete [] rhs;
	} else if (cfg.getSolver()==2){
		//Do LU decomp.
		//Release the old arrays
		delete [] a;
		delete [] b;
		delete [] c;
		delete [] rhs;
		double h = 1/((double) n);
		double h2 = h*h;
		//Alloc mats and vecs. The following is a slight copy-paste for a different data type
		//which might be unwanted, and will be dealt with if we need this in a future project.
		mat A(n-1,n-1);
		mat L(n-1,n-1);
		mat U(n-1,n-1);
		mat P(n-1,n-1);
		vec rhs(n-1), z(n-1), u(n-1);

		for(int i=0;i<loops;i++){
			for (int i=0;i<n-1;i++){
			double x = (i+1)*h;
			rhs[i] = h2*100*exp(-10*x);
			}
	    	A.fill(0);
	    	//Special lines
	    	A(0,0)=2;
	    	A(0,1)=-1;
	    	A(n-2,n-2)=2;
	    	A(n-2,n-3)=-1;
	    	//All other lines
	    	for(int i=1;i<n-2;i++){
	    	    A(i,i) = 2;
	    	    A(i,i-1) = -1;
	    	    A(i,i+1) = -1;
	    	}
			//Apply BCs
			rhs(0) += bc[0];
			rhs(n-2) += bc[1];

			//Time the solver
			start = clock();
	    	lu(L, U, P, A);
    		z = solve(L,rhs);
    		u = solve(U,z);
			finish = clock();
			calc_time += (double) finish-start;
		}
		//Store the result in a normal 'boring' array.
		//This is just to make it compatible with the rest of the code
		result[0]=bc[0];
		result[n]=bc[1];
		for (int i=1;i<n;i++){
			result[i]=u(i-1);
		}
	}

	//Get time averages, error and export to file
	calc_time /= (double) loops*CLOCKS_PER_SEC;
	double *error;
	error = get_error(n,result);
	
	if (bc[0] != 0.0 || bc[1] != 0.0){
		//Error not applicable if u(0) != 0 or u(1) != 0
		cout << "Don't know the theoretical solution to this, setting error to nan" << endl;
		error[0] = numeric_limits<double>::quiet_NaN();
		error[1] = numeric_limits<double>::quiet_NaN();
	}

	write_to_file(n+1,cfg.getOutputFile(),result,error,calc_time,cfg.getLongOutput());
	delete [] result;
	return 0;
}


void init_arrs(int N, double *A, double *B, double *C, double *RHS, double *RESULT,double BC[2]){
	double h = 1/((double)N);
	double h2 = h*h;
	for (int i=0;i<N-1;i++){
		double x = (i+1)*h;
		RHS[i] = h2*100*exp(-10*x);
	}
	for (int i=0;i<N-1;i++){
		A[i]= -1.0;
		B[i]= 2.0;
		C[i]= -1.0;
	}
	//Apply BCs
	RHS[0] -= A[0]*BC[0];
	RHS[N-2] -= C[N-1]*BC[1];
	RESULT[0] = BC[0];
	RESULT[N] = BC[1];
}

void init_arrs_special(int N, double *B, double *RHS, double *RESULT,double BC[2]){
	double h = 1/((double)N);
	double h2 = h*h;
	for (int i=0;i<N-1;i++){
		double x = (i+1)*h;
		RHS[i] = h2*100*exp(-10*x);
	}
	B[0]=2;
	for (int i=1;i<N-1;i++){
		B[i] = ((double) i+2)/((double) i+1);
	}
	//Can do BC's here
	RHS[0] += BC[0];
	RHS[N-2] += BC[1];
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

void do_thomas_special(int N, double *B, double *RHS, double *RESULT){
	//Forw. elim.
	for(int i=1;i<N-1;i++){
		RHS[i] += RHS[i-1]/B[i-1];
	}
	//Back. sub.
	RESULT[N-1]=RHS[N-2]/B[N-2];
	for(int i=N-3;i>-1;i--){
		RESULT[i+1]=(RHS[i]+RESULT[i+2])/B[i];
	}
}


void write_to_file(int N,string fname,double *arr,double error[2],double T,int write_long_output){
	int w = 15;
	double h = 1/((double)N-1);
	ofstream out_file;
	out_file.open(fname);
	out_file << left << setw(w) << "n" << "   " <<"time=" << endl;
	out_file  << setw(w) << N-1 << setprecision(8) << scientific <<"   " << T << endl;
	out_file << setw(w) << "log10 relerr" << "   " << "log10 IerrSQ" << endl;
	out_file << setw(w) << error[0] << "   " << error[1] << endl;
	
	if(write_long_output){
		out_file  << setw(w) << "x" << "   " << "u_calc" << endl;
		for(int i=0;i<N;i++){
			out_file  << setw(w) << setprecision(8)<< (double)i*h << "   " << arr[i] << endl;
		}
	}
}

double* get_error(int N,double *calc){
	//Enough to acces calc[1]->calc[N] since calc[0]=calc[N+1] are exact due to BCs.
	double h = 1/((double)N);
	double x;
	double U_analytical;
	double temp_rel_err; 
	double max_rel_err=0; //avoid special case for first value. anything is >=0
	double err_sq_sum = 0;
	double *output;
	output = new double[2];
	
	for (int i=1;i<N;i++){
		x=i*h;
		U_analytical = 1-(1-exp(-10))*x-exp(-10*x);
		//Relative Error
		temp_rel_err = abs((U_analytical-calc[i])/U_analytical);
		if (temp_rel_err > max_rel_err){
			max_rel_err = temp_rel_err;
		}
		//Error Squared Integral
		err_sq_sum += pow((U_analytical-calc[i]),2)*h;
	}
	//Take the log of both metrics and return
	output[0] = log10(max_rel_err);
	output[1] = log10(err_sq_sum);
	return output;
}
