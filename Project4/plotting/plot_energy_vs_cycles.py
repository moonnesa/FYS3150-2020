# -*- coding: utf-8 -*-
"""
Created on Wed Nov 25 11:51:29 2020

@author: Mooni
"""

import numpy as np 
from matplotlib import pyplot as plt


filename1 = "cyclesVSEnergi.txt"
filename2 = "expectations.txt"

Cs,Es = np.loadtxt(filename1, usecols=(0,1), unpack=True)
T, E, Cv, M, S, absM, nrAcc = np.loadtxt(filename2, usecols=(0,1,2,3,4,5,6), unpack=True)
plt.plot(Cs, Es)
plt.xlabel("Number of Cycles")
plt.ylabel("Expected Energy")
plt.title("L=2 and T=1")
plt.show()
plt.plot(T,M)
plt.xlabel("Rising Temperature")
plt.ylabel("Expected Magnetization")
plt.title("L=2 and 10^6 Cycles")
plt.show()