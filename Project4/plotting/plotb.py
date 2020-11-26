# -*- coding: utf-8 -*-
"""
Created on Wed Nov 25 11:40:36 2020

@author: Mooni
"""
import numpy as np 
from matplotlib import pyplot as plt


filename1 = "expectations20.txt"
filename2 = "expectations20_24.txt"
k=0

MC_Cs,Ts,Es,Cvs,Ms,Xs,Mabss,Nr_accs_states = np.loadtxt(filename1, usecols=(0,1,2,3,4,5,6,7), unpack=True)
MC_C,T,E,Cv,M,X,Mabs,Nr_acc_states = np.loadtxt(filename2, usecols=(0,1,2,3,4,5,6,7), unpack=True)
"""
M1=np.zeros(int(MC_Cs[-1]))#expected energies for T=1
E1 = np.zeros(int(MC_Cs[-1]))#expected magnetization for T=1

for i in range(0,len(Ts)):
    if Ts[i]==1:
        M1[k]=Ms[i]
        E1[k]=Es[i]
        k=k+1

print (M1, E1)
"""
# ---------------- New color scheme -----------------
# These are the "Tableau 20" colors as RGB.    
tableau20 = [(31, 119, 180), (174, 199, 232), (255, 127, 14), (255, 187, 120),    
             (44, 160, 44), (152, 223, 138), (214, 39, 40), (255, 152, 150),    
             (148, 103, 189), (197, 176, 213), (140, 86, 75), (196, 156, 148),    
             (227, 119, 194), (247, 182, 210), (127, 127, 127), (199, 199, 199),    
             (188, 189, 34), (219, 219, 141), (23, 190, 207), (158, 218, 229)]    
  
# Scale the RGB values to the [0, 1] range, which is the format matplotlib accepts.    
for i in range(len(tableau20)):    
    r, g, b = tableau20[i]    
    tableau20[i] = (r / 255., g / 255., b / 255.) 
    
fig = plt.figure
plt.subplot()
plt.plot(MC_Cs, Nr_accs_states,color=tableau20[4],label="T=1")
plt.plot(MC_C, Nr_acc_states,color=tableau20[2],label="T=2.4")
#plt.plot(MC_C, Mabs,color=tableau20[6],label="All up Initial")
plt.xlabel("Logarithm of Number of Monte-Carlo Cycles")
plt.ylabel("Number of Accepted States")
plt.title("Number of Accepted States vs Monte-Carlo Cycles T=1 and T=2.4")
ax = plt.subplot()  
ax.yaxis.grid()  
ax.spines["top"].set_visible(False)    
ax.spines["bottom"].set_visible(False)    
ax.spines["right"].set_visible(False)    
ax.spines["left"].set_visible(False)   
plt.xticks(fontsize=10)    
plt.yticks(fontsize=10)    
plt.legend(loc=1, fontsize=10)
#plt.grid(b=True, which='major')
#plt.grid(b=True, which='minor', alpha=0.2)
#plt.minorticks_on()
# Remove the tick marks; they are unnecessary with the tick lines we just plotted.    
"""
plt.subplot(212)        
plt.plot(MC_C, Nr_acc_states,color=tableau20[4])
plt.plot(MC_C, E,color=tableau20[6])
plt.xlabel("Logarithm of Number of Monte-Carlo Cycles")
plt.ylabel("Expected Energies")
ax = plt.subplot(212)  
ax.yaxis.grid()  
ax.spines["top"].set_visible(False)    
ax.spines["bottom"].set_visible(False)    
ax.spines["right"].set_visible(False)    
ax.spines["left"].set_visible(False)   
plt.xticks(fontsize=10)    
plt.yticks(fontsize=10)    
plt.legend(loc=1, fontsize=10)
#plt.grid(b=True, which='major')
#plt.grid(b=True, which='minor', alpha=0.2)
#plt.minorticks_on()
# Remove the tick marks; they are unnecessary with the tick lines we just plotted.    
"""
plt.show()
