#ifndef __PHOTOSPHERE_H__
#define __PHOTOSPHERE_H__

#include "PhotoSphereProperty.h"

#include <fstream>
#include <string>
#include <vector>
#include <GL/buffer.h>
#include <GL/shader.h>
#include <GL/texture.h>
#include <GL/utilities.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

class PhotoSphere
{
public:
    static PhotoSphere *FromFile(const string &filename, uint32_t hslice = 25, uint32_t vslice = 25);
    void Draw();
    Shader GetShader();
    ~PhotoSphere();
private:
/// Constants
    const static string m_VertexShaderString;
    const static string m_FragmentShaderString;
/// Variables
    PhotoSphereProperty *m_property;
    Shader *m_shader;
    VertexArrayObject *m_vao;
    BufferObject *m_vbo;
    BufferObject *m_tbo;
    BufferObject *m_ibo;
    Texture *m_texture;

    void GenerateSphere(uint32_t hslice, uint32_t vslice, vector<vec3> &vertices, vector<vec3> &texCoord, vector<GLuint> &indices);

    void Dispose();
    PhotoSphere();
};

#endif // __PHOTOSPHERE_H__
