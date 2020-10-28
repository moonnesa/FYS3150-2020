# -*- coding: utf-8 -*-
"""
Created on Wed Oct 28 18:08:14 2020

@author: Mooni
"""
from mpl_toolkits import mplot3d
import matplotlib.pyplot as plt
import numpy as np

x_list = []
y_list = []
z_list = []
with open("ES_Energy_values_V.txt", "r") as file1:
    # next(file)
    for line1 in file1:
        col1 = line1.split()
        x_list.append(float(col1[0]))
        y_list.append(float(col1[1]))
        z_list.append(float(col1[2]))

x = np.array(x_list)
k = np.zeros(x.size)
y = np.array(y_list)
z = np.array(z_list)

file1.close()

xa_list = []
ya_list = []
za_list = []
with open("ES_Energy_values_E.txt", "r") as file1:
    # next(file)
    for line1 in file1:
        col1 = line1.split()
        xa_list.append(float(col1[0]))
        ya_list.append(float(col1[1]))

xa = np.array(x_list)
ka = np.zeros(x.size)
ya = np.array(y_list)


file1.close()


plt.style.use('ggplot')
fig, ax = plt.subplots()
ax.plot(x,y,marker = 'o',markersize=3, color = 'red', label='Kinetic vs Potential energy of the earth sun system for circular orbit with verlet')
ax.plot(xa,ya,marker = '',markersize=0.00000001, color = 'blue', label='Kinetic vs Potential energy of the earth sun system for circular orbit with Euler')
plt.xlim([-1.5, 1.5])
plt.ylim([-1.5, 1.5])
ax.set_xlabel('Kinetic Energy')
ax.set_ylabel('Potential Energy') 
ax.axis('equal')
plt.legend(loc='lower right')
plt.show()