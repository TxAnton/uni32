import math

import numpy as np


def equation_plane(d1, d2, d3):
    a1 = d2[0] - d1[0]
    b1 = d2[1] - d1[1]
    c1 = d2[2] - d1[2]
    a2 = d3[0] - d1[0]
    b2 = d3[1] - d1[1]
    c2 = d3[2] - d1[2]
    a = b1 * c2 - b2 * c1
    b = a2 * c1 - a1 * c2
    c = a1 * b2 - b1 * a2
    d = (- a * d1[0] - b * d1[1] - c * d1[2])
    return np.asarray([a, b, c])


def normal(vec):
    return vec / math.sqrt(vec[0] ** 2 + vec[1] ** 2 + vec[2] ** 2)


def task2(n1, n2, n3, vec):
    N11 = np.cross(n2, n3)
    N21 = np.cross(n1, n3)
    N31 = np.cross(n1, n2)

    N1_sh = 1.0 / np.dot(n1, N11) * N11
    N2_sh = 1.0 / np.dot(n2, N21) * N21
    N3_sh = 1.0 / np.dot(n3, N31) * N31

    k1 = np.dot(vec, N1_sh)
    k2 = np.dot(vec, N2_sh)
    k3 = np.dot(vec, N3_sh)

    return np.asarray([k1, k2, k3])


A = np.asarray([6, 3, 0]) # TODO заполнить
B = np.asarray([6, 0, 4])
H = np.asarray([0, 7, 3])
AA = np.asarray([8, 0, 0])
BB = np.asarray([0, 7, 0])
HH = np.asarray([0, 0, 4])

norm_vec = equation_plane(B, A, H)

if norm_vec[0] < 0 and norm_vec[1] < 0 and norm_vec[2] < 0:
    print("\033[31m{}\033[0m".format("Проверь norm_vec" + str(norm_vec)))


print("Для первого задания")
h = normal(norm_vec)
print("h* =", h)
print("max =", np.dot(A, h))


# 2
g = np.asarray([0.6, 0.7, 0.2]) # TODO НАДО ЗАПОЛНИТЬ

p1 = normal(equation_plane(A, B, AA))
p2 = normal(equation_plane(A, H, B))
p3 = normal(equation_plane(A, BB, H))
p4 = normal(equation_plane(A, np.asarray([B[0], B[1], -B[2]]), AA))
p5 = normal(equation_plane(A, np.asarray([H[0], H[1], -H[2]]), BB))
p6 = normal(equation_plane(A, np.asarray([B[0], B[1], -B[2]]), np.asarray([H[0], H[1], -H[2]])))

p = []
p.append(p1)
p.append(p2)
p.append(p3)
p.append(p4)
p.append(p5)
p.append(p6)

for i in range(len(p)):
    if p[i][0] < 0 and p[i][1] < 0 and p[i][2] < 0:
        print("\033[31m{}\033[0m".format("Проверь p" + str(i+1) + " " + str(p[i])))

print("\nДля второго задания")
for i in range(len(p)):
    print(p[i])

for i in range(4):
    for j in range(i+1, 5):
        for t in range(j+1, 6):

            answ = task2(p[i], p[j], p[t], g)
            text = "n_" + str(i+1) + " n_" + str(j+1) + " n_" + str(t+1) + " " + str(answ)

            if (answ[0] >= 0 and answ[1] >= 0 and answ[2] >= 0):
                new_A = str(np.dot(A, (answ[0] * p[i] + answ[1] * p[j] + answ[2] * p[t])))
                print("\033[34m{}\033[0m Max g(A) = {}".format(text, new_A))




            else:
                print(text)










