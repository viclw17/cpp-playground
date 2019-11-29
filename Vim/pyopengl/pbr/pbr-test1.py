import numpy as np
from PIL import Image
from glumpy import app, gl, glm, gloo, data

vertex_shader = open('pbr1.vs').read()
fragment_shader = open('pbr1.fs').read()

def cube():
    vtype = [('aPos', np.float32, 3),
             ('aTexCoords', np.float32, 2),
             ('aNormal', np.float32, 3)]
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
    vertices['aPos'] = p[faces_p]
    vertices['aTexCoords'] = t[faces_t]
    vertices['aNormal'] = n[faces_n]

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


window = app.Window(width=1024, height=1024, color=(0,0,0,1))

@window.event
def on_draw(dt):
    global phi, theta
    window.clear()
    gl.glDisable(gl.GL_BLEND)
    gl.glEnable(gl.GL_DEPTH_TEST)
    cube.draw(gl.GL_TRIANGLES, I)

    # Rotate cube
    theta += 1.0 # degrees
    phi += 1.0 # degrees
    model = np.eye(4, dtype=np.float32)
    glm.rotate(model, theta, 0, 0, 1)
    glm.rotate(model, phi, 0, 1, 0)
    # glm.rotate(model, theta, 1, 0, 0)
    cube['model'] = model

@window.event
def on_resize(width, height):
    cube['projection'] = glm.perspective(45.0, width / float(height), 2.0, 100.0)

@window.event
def on_init():
    gl.glEnable(gl.GL_DEPTH_TEST)


V, I = cube()
cube = gloo.Program(vertex_shader, fragment_shader)
cube.bind(V)

cube['albedoMap'] = np.array(Image.open("./textures/albedo.png"))
cube['normalMap'] = np.array(Image.open("./textures/normal.png"))
cube['metallicMap'] = np.array(Image.open("./textures/metallic.png"))
cube['roughnessMap'] = np.array(Image.open("./textures/roughness.png"))
cube['aoMap'] = np.array(Image.open("./textures/ao.png"))
cube['lightPositions'] = np.array((0,5,10))
cube['lightColors'] = np.array((150, 150, 150))


cube['model'] = np.eye(4, dtype=np.float32) 
cube['view'] = glm.translation(0, 0, -20)
phi, theta = 0,0

app.run()






