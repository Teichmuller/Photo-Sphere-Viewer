/// Reference: https://developers.google.com/streetview/spherical-metadata
#ifndef PHOTOSPHEREVIEWER_PHOTOSPHERE_H_
#define PHOTOSPHEREVIEWER_PHOTOSPHERE_H_

#include <PhotoSphereViewer/PhotoSphereProperty.h>

#include <fstream>
#include <string>
#include <vector>
#include <cxpl/GL/buffer.h>
#include <cxpl/GL/shader.h>
#include <cxpl/GL/texture.h>
#include <cxpl/GL/utilities.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;
using namespace cxpl;
using namespace cxpl::GL;

namespace PhotoSphereViewer
{
    class PhotoSphere
    {
    public:
        static shared_ptr<PhotoSphere> FromFile(const string &filename, uint32_t hslice = 25, uint32_t vslice = 25);
        void Draw();
        shared_ptr<Program> GetShader();
        ~PhotoSphere();
    private:
    /// Constants
        const static string m_VertexShaderString;
        const static string m_FragmentShaderString;
    /// Variables
        shared_ptr<PhotoSphereProperty> m_property;
        shared_ptr<Program> m_shader;
        shared_ptr<VertexArrayObject> m_vao;
        shared_ptr<BufferObject> m_vbo;
        shared_ptr<BufferObject> m_tbo;
        shared_ptr<BufferObject> m_ibo;
        shared_ptr<Texture> m_texture;

        void GenerateSphere(uint32_t hslice, uint32_t vslice, vector<vec3> &vertices, vector<vec3> &texCoord, vector<GLuint> &indices);

        void Dispose();
        PhotoSphere();
    };
}

#endif // PHOTOSPHEREVIEWER_PHOTOSPHERE_H_
