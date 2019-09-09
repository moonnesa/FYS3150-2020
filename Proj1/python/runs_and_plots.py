#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import numpy as np
import sys
import os
import matplotlib.pyplot as plt
import struct

def analytical_sol(x):
    return 1-(1-np.exp(-10))*x-np.exp(-10*x)

def readfile(fname):
    #with open(fname,'r') as f:
    fin = open(fname,'r')
    lines = fin.readlines()
    N_TIME = lines[1].strip().split()
    N = int(N_TIME[0])
    TIME = float(N_TIME[1])
    ERR = lines[3].strip().split()
    err = float(ERR[0]),float(ERR[1])
    X = np.empty(N+1)
    U = np.empty(N+1)
    if len(lines)>4:
        for i in range(5,N+6):
            XU = lines[i].strip().split()
            X[i-5] = float(XU[0])
            U[i-5] = float(XU[1])
    return N,TIME,X,U,err

def make_cfg(fname,n,loops,bcs,solver,long_out,file_out):
    os.system("rm " + fname)
    file = open(fname,"a")
    file.write("n="+str(n)+'\n')
    file.write("loops="+str(loops)+'\n')
    file.write("bc_left="+str(bcs[0])+'\n')
    file.write("bc_right="+str(bcs[1])+'\n')
    file.write("solver="+str(solver)+'\n')
    file.write("long_output="+str(long_out)+'\n')
    file.write("out_filename="+str(file_out)+'\n')
    file.close()
    

def run_cpp(in_file):
    os.system('../cpp/proj1 ' + in_file)
 

def clear_files():
    os.system('rm ../data/cfg/*')
    os.system('rm ../data/out/*')

def error_analysis(nums):
    rel_err = list()
    sq_err = list()
    for n in nums:
        err = readfile("out/out{}.dat".format(n))[4]
        rel_err.append(err[0])
        sq_err.append(err[1])
    return rel_err,sq_err


##### PLOT OUTPUT
#plt.figure(1)
#for n in range(3,0,-1):
#    make_cfg("../data/cfg/in"+str(n)+".cfg", 10**n, 1, [0,0],0,1,"../data/out/out"+str(n)+".dat")
#    run_cpp("../data/cfg/in"+str(n)+".cfg")
#    _,_,x,u,_ = readfile("../data/out/out"+str(n)+".dat")
#    plt.plot(x,u,'-s',label='n={}'.format(10**n))
#X = np.linspace(0,1,10**4)
#plt.plot(X,analytical_sol(X),'k',label='Analytical')
#
#plt.grid(1)
#plt.xlabel("x")
#plt.ylabel("u(x)")
#plt.legend()
#plt.savefig('../data/functionfig.png')



### ERROR AND TIME ANALYSIS
nums = [10**n for n in range(1,9)]
nums.append(50000000)
nums.append(5000000)
nums.append(500000)
err_sq = list()
err_rel = list()
t_gen = list()
t_const = list()

for num in nums:
#    make_cfg("../data/cfg/gen_"+str(num)+".cfg", num, 1, [0,0], 0, 0, "../data/out/gen_"+str(num)+".dat")
    #make_cfg("../data/cfg/const_"+str(num)+".cfg", num, 1, [0,0], 1, 0, "../data/out/const_"+str(num)+".dat")
#    run_cpp("../data/cfg/gen_"+str(num)+".cfg")
    #run_cpp("../data/cfg/const_"+str(num)+".cfg")
    _,t,_,_,err = readfile("../data/out/gen_"+str(num)+".dat")
    t_gen.append(t)
    err_sq.append(err[1])
    err_rel.append(err[0])    
    #_,t,_,_,_ = readfile("../data/out/const_"+str(num)+".dat")
    #t_const.append(t)

#t_LU = list()
#err_sq_LU = list()
#err_rel_LU = list()
#nums_LU = [10**n for n in range(1,4)]
#nums_LU.append(5000)
#nums_LU.append(500)
#for num in nums_LU:
#    make_cfg("../data/cfg/LU_"+str(num)+".cfg", num, 50, [0,0], 2, 0, "../data/out/LU_"+str(num)+".dat")
#    run_cpp("../data/cfg/LU_"+str(num)+".cfg")
#    _,t,_,_,err = readfile("../data/out/LU_"+str(num)+".dat")
#    err_sq_LU.append(err[1])
#    err_rel_LU.append(err[0])
#    t_LU.append(t)
#    
x = np.log10(nums)
#x_LU = np.log10(nums_LU)

plt.figure(2)
fit_sq = np.polyfit(x[0:4],err_sq[0:4],1)
fit_rel = np.polyfit(x[0:4],err_rel[0:4],1)

y_sq = np.polyval(fit_sq,x)
y_rel = np.polyval(fit_rel,x)

plt.plot(x,err_sq,'or',label='$L^2$ Error')
plt.plot(x[0:5],y_sq[0:5],'r',label='y={:1.3f}x+{:1.3f}'.format(fit_sq[0],fit_sq[1]))
plt.plot(x,err_rel,'og',label='Rel. Error')
plt.plot(x[0:5],y_rel[0:5],'g',label='y={:1.3f}x+{:1.3f}'.format(fit_rel[0],fit_rel[1]) )


plt.axis([0,9,-20,0])
plt.grid(1)
plt.title('Error Estimation')
plt.xlabel('$log_{10}(n)$')
plt.ylabel('$log_{10}(\epsilon)$')
plt.legend(loc='lower left')
plt.savefig('../data/errorfig.png')
#
#
#plt.figure(3)
#y_gen = np.log10(t_gen)
#y_const = np.log10(t_const)
#y_LU = np.log10(t_LU)
#
#fit_gen = np.polyfit(x,y_gen,1)
#fit_const = np.polyfit(x,y_const,1)
#fit_LU = np.polyfit(x_LU[1:],y_LU[1:],1)
#
#y0_gen = np.polyval(fit_gen,x)
#y0_const = np.polyval(fit_const,x)
#y0_LU = np.polyval(fit_LU,x_LU)
#
#plt.plot(x,y_gen,'or',label='General')
#plt.plot(x,y_const,'og',label='Special')
#plt.plot(x_LU,y_LU,'ob',label='LU decomp')
#
#plt.plot(x,y0_gen,'r',label='y={:1.3f}x+{:1.3f}'.format(fit_gen[0],fit_gen[1]))
#plt.plot(x,y0_const,'g',label='y={:1.3f}x+{:1.3f}'.format(fit_const[0],fit_const[1]))
#plt.plot(x_LU,y0_LU,'b',label='y={:1.3f}x+{:1.3f}'.format(fit_LU[0],fit_LU[1]))
#
#plt.legend()
#plt.title('Time measurements')
#plt.xlabel('$log_{10}(n)$')
#plt.ylabel('$log_{10}(t)$')
#plt.grid(1)
#plt.savefig('../data/timefig.png')
#    
#
