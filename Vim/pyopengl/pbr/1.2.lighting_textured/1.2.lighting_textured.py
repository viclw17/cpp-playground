import numpy as np
from PIL import Image
from glumpy import app, gl, glm, gloo, data
from glumpy.geometry import primitives
from glumpy.transforms import Trackball, Position

vertex_shader = open('1.2.pbr.vs').read()
fragment_shader = open('1.2.pbr.fs').read()

window = app.Window(width=1024, height=1024, color=(0,0,0,1))

def update():
    model = obj['transform']['model'].reshape(4,4)
    view  = obj['transform']['view'].reshape(4,4)
    obj['view']  = view
    obj['model'] = model
    obj['normal'] = np.array(np.matrix(np.dot(view, model)).I.T)
    pass

@window.event
def on_draw(dt):
    global phi, theta
    window.clear()
    gl.glDisable(gl.GL_BLEND)
    gl.glEnable(gl.GL_DEPTH_TEST)
    obj.draw(gl.GL_TRIANGLES, I)
    
    # model rotation
    # theta += 1 # degrees
    # phi   += 1 # degrees
    # model = np.eye(4, dtype=np.float32)
    # glm.rotate(model, theta, 0, 0, 1)
    # glm.rotate(model, phi,   0, 1, 0)
    # obj['model'] = model

@window.event
def on_resize(width, height):
    obj['projection'] = glm.perspective(45.0, width / float(height), 2.0, 100.0)

@window.event
def on_mouse_drag(x, y, dx, dy, button):
    update()
    pass

@window.event
def on_init():
    gl.glEnable(gl.GL_DEPTH_TEST)
    # gl.glPolygonMode(gl.GL_FRONT_AND_BACK, gl.GL_LINE)
    update()
    pass

'''Models'''
# V, I = primitives.sphere() 
V, I = primitives.teapot() 
# V, I = primitives.cube()
# V, I = primitives.cubesphere()
# V, I = primitives.tube() 
# V, I = data.get('teapot.obj')
path = '../models/bunny.obj'
V, I = data.load(path)

obj = gloo.Program(vertex_shader, fragment_shader)
obj.bind(V)

trackball = Trackball(Position("position"))
obj['transform'] = trackball
trackball.theta, trackball.phi, trackball.zoom = 0,0,25 #40, 135, 25

# obj["light_position[0]"] =  3, 0, 0+10
# obj["light_position[1]"] =  0, 3, 0+10
# obj["light_position[2]"] = -3, -3, +10
# obj["light_color[0]"]    = 1, 0, 0
# obj["light_color[1]"]    = 0, 1, 0
# obj["light_color[2]"]    = 0, 0, 1

obj['albedoMap'] = np.array(Image.open("../textures/chipped-paint-metal/chipped-paint-metal-albedo.png"))
obj['normalMap'] = np.array(Image.open("../textures/chipped-paint-metal/chipped-paint-metal-normal-dx.png"))
obj['metallicMap'] = np.array(Image.open("../textures/chipped-paint-metal/chipped-paint-metal-metal.png"))
obj['roughnessMap'] = np.array(Image.open("../textures/chipped-paint-metal/chipped-paint-metal-rough2.png"))
obj['aoMap'] = np.array(Image.open("../textures/chipped-paint-metal/chipped-paint-ao.png"))

# rusty metal
# obj['albedoMap'] = np.array(Image.open("./textures/rustediron/rustediron2_basecolor.png"))
# obj['normalMap'] = np.array(Image.open("./textures/rustediron/rustediron2_normal.png"))
# obj['metallicMap'] = np.array(Image.open("./textures/rustediron/rustediron2_metallic.png"))
# obj['roughnessMap'] = np.array(Image.open("./textures/rustediron/rustediron2_roughness.png"))
# obj['aoMap'] = np.array(Image.open("./textures/rustediron/ao.png"))


obj['lightPositions'] = np.array((0,0,5))
obj['lightColors'] = np.array((1,1,1)) * 200
obj['camPos'] = np.array((0,0,5)) #!!!!

# obj['model'] = np.eye(4, dtype=np.float32) 
# obj['view'] = glm.translation(0, 0, -5)
# phi, theta = 0,0

window.attach(obj['transform'])

app.run(framerate = 120)






