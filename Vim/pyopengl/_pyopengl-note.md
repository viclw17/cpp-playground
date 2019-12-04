# Modern OpenGL
## 2.2.1 Pipeline
Vertices - Vertex Shader(gl_Position) - Primitives Generation - Rasterization - Fragment Shader(gl_FragColor) - Testing Blending - Framebuffer

## 2.2.2 Buffers
vertices stored on CPU, need to be uploaded to GPU
build buffers onto CPU, send onto GPU
no data changes, no need to upload again
fixed pipeline, data uploaded each render call, only display lists built into GPU memory

## 2.2.3 Variables
attributes
uniform, constant value across all vertices
varying, pass information between vet stage and frag stage, interpolation

## 2.3.1 Bindings
Pyglet, PyOpenGL, ModernGL, Ctypes,

## 2.3.2 Engines
VTK, Processing, NodeBox, Panda3D, VPython

## 2.3.3 Libs
Glumpy, Vispy

# Quickstart
## 3.1.1 Normalize Device Coordinates
## 3.1.2 Triangulation
## 3.1.3 GL Primitives
## 3.1.4 Interpolation

# Hard way
## 3.2.1 Writing shaders
## 3.2.2 Compiling program
## 3.2.3 Uploading data to GPU
Next, we need to build CPU data and the corresponding GPU buffer that will hold a copy of the CPU data (GPU cannot access CPU memory).

This is important because GLES 2.0 floats have to be exactly 32 bits long and a regular Python float would not work (they are actually equivalent to a C double). So let us specify a NumPy array holding 4×2 32-bits float that will correspond to our 4×(x,y) vertices:

## 3.2.4 Rendering
## 3.2.5 Uniform color
## 3.2.6 Varying color

# Easy way
Glumpy is organized around three main modules:

* The **Application layer (app) package** is responsible for opening a window and handling user events such as mouse and keyboard interactions.
* The **OpenGL object oriented layer (gloo) package** is responsible for handling shader programs and syncing CPU/GPU data through the numpy interface.
* The **Graphic layer (graphics) package** provides higher-level common objects such as text, collections and widgets.

# Basic Math

# Render a cube

---

os.open
open

---
# Difference between “texture” vs “texture2d” in OpenGL ES?
```texture2D``` is the same as ```texture```, but it's used in the older versions of glsl. Between glsl 120 and 130 they changed the function to ```texture``` and made it accept every kind of samplers, not just a sampler2D.

# in and out
[How to pass data from shader to shader in OpenGL](https://www.haroldserrano.com/blog/how-to-pass-data-from-shader-to-shader-in-opengl)