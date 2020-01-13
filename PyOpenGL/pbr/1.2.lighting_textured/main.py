import numpy as np
from PIL import Image
from glumpy import app, gl, glm, gloo, data
from glumpy.geometry import primitives
from glumpy.transforms import Trackball, Position


vertex_shader = open('1.2.pbr.vs').read()
fragment_shader = open('1.2.pbr.fs').read()

window = app.Window(width=800, height=800, color=(0,0,0,1))

def update():
    model = obj['transform']['model'].reshape(4,4)
    view  = obj['transform']['view'].reshape(4,4)
    obj['view']  = view
    obj['model'] = model
    # obj['normal'] = np.array(np.matrix(np.dot(view, model)).I.T) 
    pass

@window.event
def on_draw(dt):
    window.clear()
    gl.glDisable(gl.GL_BLEND)
    gl.glEnable(gl.GL_DEPTH_TEST)
    obj.draw(gl.GL_TRIANGLES, I)
    obj['time'] += dt

# @window.event
# def on_resize(width, height):
#     obj['projection'] = glm.perspective(45.0, width / float(height), 2.0, 100.0)

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

@window.event
def on_character(character):
    global p
    print('Character entered (chracter: %s)'% character)
    if (character == ' '): p = 0
    if (character == 'p'): p = (p+1) % 11
    obj['p'] = p



'''Models'''
# V, I = primitives.sphere() 
V, I = primitives.teapot() 
# V, I = primitives.cube()
# V, I = primitives.cubesphere()
# V, I = primitives.tube() 
# V, I = data.get('teapot.obj')
path = '../models/bunny.obj'
# V, I = data.load(path)

obj = gloo.Program(vertex_shader, fragment_shader)
obj.bind(V)

trackball = Trackball(Position("position"))
obj['transform'] = trackball
trackball.theta, trackball.phi, trackball.zoom = 45,45,25 #40, 135, 25

'''lights'''
# obj["lightPositions[0]"] =  np.array((10,  10, -10))
# obj["lightPositions[1]"] =  np.array((0,  5, +10))
# obj["lightPositions[2]"] =  np.array((-5, 0, +10))
# obj["lightPositions[3]"] =  np.array((0, -5, +10))
# obj['lightPositions'] = np.array((0,0,10))
obj['lightColors'] = np.array((1,1,1)) * 500

obj['camPos'] = np.array((0,0,5)) 

'''textures'''
obj['albedoMap'] = np.array(Image.open("../textures/chipped-paint-metal/chipped-paint-metal-albedo.png"))
obj['normalMap'] = np.array(Image.open("../textures/chipped-paint-metal/chipped-paint-metal-normal-dx.png"))
obj['metallicMap'] = np.array(Image.open("../textures/chipped-paint-metal/chipped-paint-metal-metal.png"))
obj['roughnessMap'] = np.array(Image.open("../textures/chipped-paint-metal/chipped-paint-metal-rough2.png"))
obj['aoMap'] = np.array(Image.open("../textures/chipped-paint-metal/chipped-paint-ao.png"))

# obj['albedoMap'] = np.array(Image.open("../textures/rustediron/rustediron2_basecolor.png"))
# obj['normalMap'] = np.array(Image.open("../textures/rustediron/rustediron2_normal.png"))
# obj['metallicMap'] = np.array(Image.open("../textures/rustediron/rustediron2_metallic.png"))
# obj['roughnessMap'] = np.array(Image.open("../textures/rustediron/rustediron2_roughness.png"))
# obj['aoMap'] = np.array(Image.open("../textures/rustediron/ao.png"))



window.attach(obj['transform'])

app.run(framerate = 120)






