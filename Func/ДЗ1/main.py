import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from mpl_toolkits.mplot3d.art3d import Poly3DCollection
import numpy as np
import math


def print_surf(points, f):
    x = [p[0] for p in points]
    y = [p[1] for p in points]
    z = [p[2] for p in points]
    vert = list(zip(x, y, z))
    if f == 0:
        ax.add_collection3d(Poly3DCollection(vert, alpha=.4, facecolor='#e66d55', edgecolors='r'))
    else:
        for p in points:
            ax.plot([0, p[0]], [0, p[1]], [0, p[2]], "r")


def print_side(output, i0):
    print_surf([output[i0], output[i0 + 1], output[i0 + 2]], 0)
    print_surf([output[i0], output[i0 + 4], output[i0 + 2]], 0)
    print_surf([output[i0], output[i0 + 1], output[i0 + 3]], 0)
    print_surf([output[i0 + 5], output[i0 + 1], output[i0 + 2]], 0)


output = []
output.append([6, 3, 0])
output.append([6, 0, 4])
output.append([0, 7, 3])
output.append([8, 0, 0])
output.append([0, 6, 0])
output.append([0, 0, 4])
fig = plt.figure()
ax = Axes3D(fig)
temp = output.copy()

print_side(output, 0)

for p in temp:
    output.append([p[0], -1 * p[1], p[2]])
print_side(output, 6)

temp = output.copy()

for p in temp:
    output.append([-1 * p[0], p[1], p[2]])
print_side(output, 12)

temp = output.copy()

for p in temp:
    output.append([p[0], p[1], -1 * p[2]])
print_side(output, 18)
print_side(output, 24)
print_side(output, 30)
print_side(output, 36)
print_side(output, 42)

w1 = np.array([-4, 8, -7])
w2 = np.array([7, -8, -5])
w3 = w1 + w2
#ax.plot(w1[0], w1[1], w1[2], "bo")
#ax.plot(w2[0], w2[1], w2[2], "bo")
#ax.plot(w3[0], w3[1], w3[2], "bo")
# создание угла
p = []
p.append([2 * x for x in output[31]])
p.append([2 * x for x in output[32]])
p.append([2 * x for x in output[35]])
p.append([0, 0, 0])
#print_surf([p[0], p[1], p[3]], 1)
#print_surf([p[1], p[2], p[3]], 1)
#print_surf([p[0], p[2], p[3]], 1)
OA = np.array(output[31])
OB = np.array(output[32])
OH = np.array(output[35])
print(OA)
print(OB)
print(OH)
OA1 = np.cross(OB, OH)
OB1 = np.cross(OA, OH)
OH1 = np.cross(OA, OB)
# print(OA1)
# print(OB1)
# print(OH1)
d1 = np.dot(OA1, OA)
d2 = np.dot(OB1, OB)
d3 = np.dot(OH1, OH)
OA1 = [x / d1 for x in OA1]
OB1 = [x / d2 for x in OB1]
OH1 = [x / d3 for x in OH1]
print(OA1)
print(OB1)
print(OH1)

k1 = np.dot(w3, OA1)
k2 = np.dot(w3, OB1)
k3 = np.dot(w3, OH1)
print("For w1: ", k1, "* OA + ", k2, "* OB + ", k3, "* OH")
print(k1 + k2 + k3)
M = max((x[0] ** 2 + x[1] ** 2 + x[2] ** 2) ** (1 / 2) for x in output[0:6])
print(M)
u, v = np.mgrid[0:2 * np.pi:0.05, 0:np.pi:0.05]
x = 9 * np.cos(u) * np.sin(v)
y = 9 * np.sin(u) * np.sin(v)
z = 9 * np.cos(v)
#ax.plot_surface(x, y, z, color="b", alpha=.3) # сфера максимума
c1 = np.array(output[0]) + np.array(output[1]) + np.array(output[2])
c1 = np.array([x / 3 for x in c1])
c2 = np.array(output[0]) + np.array(output[4]) + np.array(output[2])
c2 = np.array([x / 3 for x in c2])
c3 = np.array(output[0]) + np.array(output[1]) + np.array(output[3])
c3 = np.array([x / 3 for x in c3])
c4 = np.array(output[5]) + np.array(output[1]) + np.array(output[2])
c4 = np.array([x / 3 for x in c4])
c = [c1, c2, c3, c4]
c.append(output[0])
c.append(output[1])
c.append(output[2])
c.append(output[3])
c.append(output[4])
c.append(output[5])
m = min((x[0] ** 2 + x[1] ** 2 + x[2] ** 2) ** (1 / 2) for x in c)
print(m)
u, v = np.mgrid[0:2 * np.pi:0.05, 0:np.pi:0.05]
x = m * np.cos(u) * np.sin(v)
y = m * np.sin(u) * np.sin(v)
z = m * np.cos(v)
ax.plot_surface(x, y, z, color="b", alpha=.3)  # сфера минимума
plt.show()