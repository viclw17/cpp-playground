def sphere():
    vtype = [('aPos', np.float32, 3),
        ('aTexCoords', np.float32, 2),
        ('aNormal', np.float32, 3)]
    
    itype = np.uint32

    X_SEGMENTS = 8;
    Y_SEGMENTS = 8;
    p = np.array([[0,0,0]])
    t = np.array([[0,0]])
    n = np.array([[0,0,0]])

    vertices = np.zeros(X_SEGMENTS*Y_SEGMENTS, vtype)
    for y in range(Y_SEGMENTS):
        for x in range(X_SEGMENTS):
            xSegment = x / X_SEGMENTS
            ySegment = y / Y_SEGMENTS
            xPos = np.cos(xSegment*2*np.pi)*np.sin(ySegment*np.pi)
            yPos = np.cos(ySegment*np.pi)
            zPos = np.sin(xSegment*2*np.pi)*np.sin(ySegment*np.pi)
            # pos = np.array([[xPos, yPos, zPos]])
            # print (pos)
            p = np.append(p,np.array([[xPos, yPos, zPos]]), axis = 0)
            t = np.append(t,np.array([[xSegment, ySegment]]), axis = 0)
            n = np.append(n,np.array([[xPos, yPos, zPos]]), axis = 0)
    # print (p)
    # print (t)
    # print (n)
    vertices['aPos']  = p[1:]
    vertices['aTexCoords'] = t[1:]
    vertices['aNormal'] = n[1:]

    indices = np.array([0]) #np.zeros(X_SEGMENTS*Y_SEGMENTS, itype)
    oddRow = False;
    for y in range(Y_SEGMENTS):
        if not oddRow:
            for x in range(X_SEGMENTS):
                indices = np.append(indices, (y       * (X_SEGMENTS + 1) + x))
                indices = np.append(indices, ((y + 1) * (X_SEGMENTS + 1) + x))
        else:
            for x in range(X_SEGMENTS):
                indices = np.append(indices, ((y + 1) * (X_SEGMENTS + 1) + x))
                indices = np.append(indices, (y       * (X_SEGMENTS + 1) + x))
        oddRow = not oddRow
    
    print (indices)
    return vertices, indices 



    '''
std::vector<glm::vec3> positions;
std::vector<glm::vec2> uv;
std::vector<glm::vec3> normals;
std::vector<unsigned int> indices;

const unsigned int X_SEGMENTS = 64;
const unsigned int Y_SEGMENTS = 64;
const float PI = 3.14159265359;
for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
{
    for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
    {
        float xSegment = (float)x / (float)X_SEGMENTS;
        float ySegment = (float)y / (float)Y_SEGMENTS;
        float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
        float yPos = std::cos(ySegment * PI);
        float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

        positions.push_back(glm::vec3(xPos, yPos, zPos));
        uv.push_back(glm::vec2(xSegment, ySegment));
        normals.push_back(glm::vec3(xPos, yPos, zPos));
    }
}



bool oddRow = false;
for (int y = 0; y < Y_SEGMENTS; ++y)
{
    if (!oddRow) // even rows: y == 0, y == 2; and so on
    {
        for (int x = 0; x <= X_SEGMENTS; ++x)
        {
            indices.push_back(y       * (X_SEGMENTS + 1) + x);
            indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
        }
    }
    else
    {
        for (int x = X_SEGMENTS; x >= 0; --x)
        {
            indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
            indices.push_back(y       * (X_SEGMENTS + 1) + x);
        }
    }
    oddRow = !oddRow;
}
indexCount = indices.size();
'''