import math

def update():
    model = obj['transform']['model'].reshape(4,4)
    view  = obj['transform']['view'].reshape(4,4)
    obj['view']  = view
    obj['model'] = model
    obj['normal'] = np.array(np.matrix(np.dot(view, model)).I.T)

    # r = trackball.distance
    # theta = math.radians(trackball.theta)
    # phi = math.radians(trackball.phi)
    # x = r * math.sin( theta ) * math.cos( phi )
    # y = r * math.sin( theta ) * math.sin( phi )
    # z = r * math.cos( theta )
    # obj['camPos'] = np.array((x,y,z))
    # obj['camPos'] = np.array((0,0,-10)) 
    pass


# target = np.zeros(3)
# camDir = camPos-target
# camDir = camDir/np.linalg.norm(camDir)
# up = np.array((0,1,0))
# right = np.cross(up,camDir)
# right = right/np.linalg.norm(right)
# lookat = np.array((right,up,camDir))
# lookat = np.vstack(lookat,np.array((0,0,0)))
# view = np.eye(4, dtype=np.float32) 
# obj['view'] = glm.translate(view, camPos[0], camPos[1], camPos[2])
# obj['model'] = np.eye(4, dtype=np.float32)

