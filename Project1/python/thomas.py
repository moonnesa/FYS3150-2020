#!/usr/bin/python
import numpy as np
import sys
import matplotlib.pyplot as plt
import time

def add_ends(vec,n,ends):
    VEC = np.empty(n+1)
    VEC[1:n]=vec
    VEC[0]=ends[0]
    VEC[n]=ends[1]
    return VEC

def init_input_arrays(n):
    diag = np.ones(n-1)*2
    off_diag = -1*np.ones(n-1)
    h = 1/n
    h2 = h**2
    x = np.empty(n-1)
    rhs = np.empty(n-1)
    for i in range(0,n-1):
        x[i]=(i+1)*h
        rhs[i] = h2*100*np.exp(-10*x[i])
    return diag, off_diag, x, rhs

def thomas(A,B,C,RHS,n,BC):
    RESULT = np.empty(n-1)
    #Apply BC's
    RHS[0]-=A[0]*BC[0]
    RHS[-1]-=C[-1]*BC[1]
    
    #Forward elim.
    for i in range(1,n-1):
        q = A[i]/B[i-1]
        B[i] -= q*C[i-1]
        RHS[i] -= q*RHS[i-1]
    #Back sub.
    RESULT[n-2]=RHS[n-2]/B[n-2]
    for i in range(n-3,-1,-1):
        RESULT[i]=(RHS[i]-C[i]*RESULT[i+1])/B[i]
    return RESULT

def writefile(n,fname,POS,RES,time):
    with open(fname,'w') as f:
        f.write("{:<15}   {:<15}\n".format("n","time"))
        f.write("{:<15}   {:<8.8e}\n".format(n,time))
        f.write("{:<15}   {:<15}\n".format("x","u_calc"))
        for x,u in zip(POS,RES):
            f.write("{:<8.8e}   {:<8.8e}\n".format(x,u))
    
    
### MAIN PROGRAM ###

# Here set the number of subsections. The program is written such that
# for a given n, we calculate the function value at (n-1) sites, and add the two end points,
# so including the BC's we return n+1 values.
    
#Can be passed with command line or hard coded, change comments below:

#n = 10
n = int(sys.argv[1])

#Dirichlet BC values
BCs = [0,0]
#Init input arrays
d,od,x,rhs = init_input_arrays(n)
#Do Thomas
start = time.time()
res = thomas(od,d,od,rhs,n,BCs)
finish = time.time()
calc_time = finish-start
#Puzzle the pieces together
X = add_ends(x,n,[0,1])
U_calc = add_ends(res,n,BCs)
U_theo = analytical_sol(X)

#File Export
writefile(n,"out{}.dat".format(n),X,U_calc,calc_time)