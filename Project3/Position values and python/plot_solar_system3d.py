# -*- coding: utf-8 -*-
"""
Created on Tue Oct 23 13:23:39 2018

@author: Mooni

from mpl_toolkits import mplot3d
import matplotlib.pyplot as plt
import numpy as np

Script for plotting eigenvalues as a function of omega_r and logarithmic
    plot of iterations as a function of n

rho = []
eigenvec = []
c =[]

with open("Verlet_array_ES.txt", "r") as file:
    # next(file)
    for line in file:
        col = line.split()
        rho.append(float(col[0]))
        eigenvec.append(float(col[1]))
        c.append(float(col[2]))

rho_array = np.array(rho)
eigenvec_array = np.array(eigenvec)
c_array = np.array(c)
file.close()

x_list = []
y_list = []
z_list = []

with open("Verlet_array_JS.txt", "r") as file1:
    # next(file)
    for line1 in file1:
        col1 = line1.split()
        x_list.append(float(col1[0]))
        y_list.append(float(col1[1]))
        z_list.append(float(col1[2]))

x = np.array(x_list)
y = np.array(y_list)
z = np.array(z_list)
file1.close()

xs_list = []
ys_list = []
zs_list = []

with open("Verlet_array_MS.txt", "r") as file2:
    # next(file)
    for line2 in file2:
        col2 = line2.split()
        xs_list.append(float(col2[0]))
        ys_list.append(float(col2[1]))
        zs_list.append(float(col2[2]))

xs = np.array(xs_list)
ys = np.array(ys_list)
zs = np.array(zs_list)
file2.close()

xa_list = []
ya_list = []
za_list = []

with open("Verlet_array_SS.txt", "r") as file3:
    # next(file)
    for line3 in file3:
        col3 = line3.split()
        xa_list.append(float(col3[0]))
        ya_list.append(float(col3[1]))
        za_list.append(float(col3[2]))

xa = np.array(xa_list)
ya = np.array(ya_list)
za = np.array(za_list)
file3.close()

xb_list = []
yb_list = []
zb_list = []

with open("Verlet_array_S.txt", "r") as file4:
    # next(file)
    for line4 in file4:
        col4 = line4.split()
        xb_list.append(float(col4[0]))
        yb_list.append(float(col4[1]))
        zb_list.append(float(col4[2]))

xb = np.array(xb_list)
yb = np.array(yb_list)
zb = np.array(zb_list)
file4.close()

fig = plt.figure()
ax1 = fig.add_subplot(111, projection='3d')
#ax1.plot3D(x,y,z,'blue', label='Earth')
ax1.plot3D(rho_array ,eigenvec_array,c_array,'blue', label='Earth and Sun')
ax1.plot3D(x, y, z,'red', label='Jupiter and Sun')
ax1.plot3D(xs, ys, zs,'green', label='Mercury and Sun')
ax1.plot3D(xa, ya, za,'indigo', label='Saturn and Sun')
#ax1.plot(xb,yb,zb,markerfacecolor='yellow', markeredgecolor='yellow', marker='o', markersize=0.1, alpha=0.06, label='Sun')
ax1.plot([0],[0],[0],markerfacecolor='yellow', markeredgecolor='yellow', marker='o', markersize=10, alpha=0.6, label='Sun')
ax1.legend(loc='upper left')
ax1.axis('equal')

plt.style.use('ggplot')
fig, ax = plt.subplots()
ax.plot(0,0,marker = 'o',markersize=20, color = 'yellow', label='Sun')
ax.plot(xs, ys, marker = 'o', markersize=0.00001, color = 'green', label='Mercury and Sun')
ax.plot(rho_array, eigenvec_array,marker = 'o',markersize=0.00001, color = 'blue', label='Earth and Sun')
ax.plot(x, y, marker = 'o', markersize=0.00001, color = 'red', label='Jupiter and Sun')
ax.plot(xa, ya, marker = 'o', markersize=0.00001, color = 'indigo', label='Saturn and Sun')
#ax.plot(xb, yb, marker = 'o', markersize=20, color = 'yellow', label='Sun')
plt.xlim([-1.5, 1.5])
plt.ylim([-1.5, 1.5])
ax.axis('equal')
plt.legend(loc='upper right')

plt.show()"""
  
import matplotlib.pyplot as plt
import numpy as np
import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import os

# planets = ["0.txt", "1.txt", "2.txt", "3.txt",
# "4.txt", "5.txt", "6.txt", "7.txt", "8.txt", "9.txt"]

planets = ["Verlet_array_ES.txt", "Verlet_array_VS.txt", "Verlet_array_MeS.txt", "Verlet_array_MaS.txt", "Verlet_array_JS.txt", "Verlet_array_SS.txt", "Verlet_array_NS.txt", "Verlet_array_US.txt", "Verlet_array_PS.txt"]
step = np.arange(-1, 1, step=0.5)
# params = {'legend.fontsize': 'large', 'axes.labelsize': 'large',
#           'axes.titlesize': 'large', 'xtick.labelsize': 'large',
#           'ytick.labelsize': 'large'}


# mpl.rcParams.update(params)
mpl.rcParams['xtick.labelsize'] = 15


fig = plt.figure()
ax = fig.gca( projection='3d')
ax.plot([0],[0],[0])
for i in planets:
    x = []
    y = []
    z = []
    with open(i, "r") as file:
        # next(file)
        for line in file:
            col = line.split()
            x.append(float(col[0]))
            y.append(float(col[1]))
            z.append(float(col[2]))
    # os.remove(i)  # Include to delete files when plotting the Solar System
    ax.plot(x, y, z)
    ax.set_xlabel('x [AU]', size=15)
    ax.set_ylabel('y [AU]', size=15)
    ax.set_zlabel('z [AU]', size=15)
    # ax.set_xlim(-1, 1)
    # ax.set_ylim(-1, 1)
    # ax.set_zlim(-1, 1)
    # ax.set_xticks(step)
    # ax.set_yticks(step)
    # ax.set_zticks(step)

    # ax.set_xlim(-1, 1)
    # ax.set_ylim(-1, 1)
    # ax.set_zlim(-1, 1)
    # ax.set_xticks(step)
    # ax.set_yticks(step)
    # ax.set_zticks(step)
    ax.legend(['Sun','Earth', 'Venus','Mercury' , 'Mars',
               'Jupiter', 'Saturn', 'Neptune', 'Uranus', 'Pluto'], fontsize=10)


plt.show()