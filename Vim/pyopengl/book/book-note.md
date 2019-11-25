2.2.1 Pipeline
Vertices - Vertex Shader(gl_Position) - Primitives Generation - Rasterization - Fragment Shader(gl_FragColor) - Testing Blending - Framebuffer

2.2.2 Buffers
vertices stored on CPU, need to be uploaded to GPU
build buffers onto CPU, send onto GPU
no data changes, no need to upload again
fixed pipeline, data uploaded each render call, only display lists built into GPU memory

2.2.3 Variables
attributes
uniform, constant value across all vertices
varying, pass information between vet stage and frag stage, interpolation

2.3.1 Bindings
Pyglet, PyOpenGL, ModernGL, Ctypes,
2.3.2 Engines
VTK, Processing, NodeBox, Panda3D, VPython
2.3.3 Libs
Glumpy, Vispy


Next, we need to build CPU data and the corresponding GPU buffer that will hold a copy of the CPU data (GPU cannot access CPU memory).

This is important because GLES 2.0 floats have to be exactly 32 bits long and a regular Python float would not work (they are actually equivalent to a C double). So let us specify a NumPy array holding 4×2 32-bits float that will correspond to our 4×(x,y) vertices:
