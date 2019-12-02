import numpy as np
from glumpy import app, gl, glm, gloo, data

def cube():
    vtype = [('position', np.float32, 3),
             ('texcoord', np.float32, 2),
             ('normal', np.float32, 3)]
    itype = np.uint32

    # Vertices positions
    p = np.array([[1, 1, 1], [-1, 1, 1], [-1, -1, 1], [1, -1, 1],
                  [1, -1, -1], [1, 1, -1], [-1, 1, -1], [-1, -1, -1]],
                 dtype=float)
    # Texture coords
    t = np.array([[0, 0], [0, 1], [1, 1], [1, 0]])
    # Normal vectors
    n = np.array([[1,0,0],[0,1,0],[0,0,1],[-1,0,0],[0,-1,0],[0,0,-1]],dtype=float) # +x +y +z -x -y -z

    faces_p = [0, 1, 2, 3,  0, 3, 4, 5,   0, 5, 6, 1, # +z +x +y
               1, 6, 7, 2,  7, 4, 3, 2,   4, 7, 6, 5] # -x -y -z
    faces_t = [0, 1, 2, 3,  0, 1, 2, 3,   0, 1, 2, 3,
               3, 2, 1, 0,  0, 1, 2, 3,   0, 1, 2, 3]
    faces_n = [2, 2, 2, 2,  0, 0, 0, 0,   1, 1, 1, 1, 
               3, 3, 3, 3,  4, 4, 4, 4,   5, 5, 5, 5]

    vertices = np.zeros(24, vtype) # 4 vertex per face * 6
    vertices['position'] = p[faces_p]
    vertices['texcoord'] = t[faces_t]
    vertices['normal'] = n[faces_n]

    # print (vertices['aPos'])
    # print (vertices['aTexCoords'])
    # print (vertices['aNormal'])

    filled = np.resize(np.array([0, 1, 2, 0, 2, 3], dtype=itype), 6 * (2 * 3))
    # [0 1 2 0 2 3 0 1 2 0 2 3 0 1 2 0 2 3 0 1 2 0 2 3 0 1 2 0 2 3 0 1 2 0 2 3]
    filled += np.repeat(4 * np.arange(6, dtype=itype), 6) # stride
    # [ 0  0  0  0  0  0  4  4  4  4  4  4  8  8  8  8  8  8 12 12 12 12 12 12 16 16 16 16 16 16 20 20 20 20 20 20]
    # [ 0  1  2  0  2  3  4  5  6  4  6  7  8  9 10  8 10 11 12 13 14 12 14 15 16 17 18 16 18 19 20 21 22 20 22 23]
    V = vertices.view(gloo.VertexBuffer)
    I = filled.view(gloo.IndexBuffer)
    # print ('VertexBuffer stride: ' + str(V.stride))
    # print ('VertexBuffer offset: ' + str(V.offset))
    # print ('IndexBuffer stride: ' + str(I.stride))
    # print ('IndexBuffer offset: ' + str(I.offset))
    return V, I