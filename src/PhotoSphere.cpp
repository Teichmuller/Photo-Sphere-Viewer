#include "PhotoSphere.h"
#include "ErrorHandler.h"


PhotoSphere *PhotoSphere::FromFile(const string &filename, uint32_t hslice, uint32_t vslice)
{
    PhotoSphere *ret = new PhotoSphere();
    COND_ERROR_HANDLE_NULLPTR(ret != nullptr, "Creating class PhotoSphere failed!", NOACTION);

    PhotoSphereProperty *property = PhotoSphereProperty::FromFile(filename);
    COND_ERROR_HANDLE_NULLPTR(property != nullptr, "Creating class PhotoSphereProperty failed!", NOACTION);
    ret->m_property = property;

    ret->m_shader = new Shader(m_VertexShaderString.data(), m_FragmentShaderString.data());
    COND_ERROR_HANDLE_NULLPTR(ret->m_shader != nullptr, "Creating shader failed!", ret->Dispose);

    vector<vec3> vertices, texCoords;
    vector<GLuint> indices;
    ret->GenerateSphere(hslice, vslice, vertices, texCoords, indices);

    ret->m_vao = Buffer::CreateBuffer<VertexArrayObject>();
    COND_ERROR_HANDLE_NULLPTR(ret->m_vao != nullptr, "Creating Vertex Array failed!", ret->Dispose);

    ret->m_vbo = Buffer::CreateBuffer<BufferObject>();
    COND_ERROR_HANDLE_NULLPTR(ret->m_vbo != nullptr, "Creating Vertex Buffer failed!", ret->Dispose);
    ret->m_vbo->SetFormat(vertices);

    ret->m_tbo = Buffer::CreateBuffer<BufferObject>();
    COND_ERROR_HANDLE_NULLPTR(ret->m_tbo != nullptr, "Creating UV Buffer failed!", ret->Dispose);
    ret->m_tbo->SetFormat(texCoords);

    ret->m_ibo = Buffer::CreateBuffer<BufferObject>();
    COND_ERROR_HANDLE_NULLPTR(ret->m_ibo != nullptr, "Creating Index Buffer failed!", ret->Dispose);
    ret->m_ibo->SetFormat(indices);

    Image *image = Image::ReadImage(filename);
    COND_ERROR_HANDLE_NULLPTR(image != nullptr, "Cannot read " + filename +  "!", ret->Dispose);

    ret->m_texture = Texture::FromImage(image);
    COND_ERROR_HANDLE_NULLPTR(ret->m_texture != nullptr, "Creating texture failed!", ret->Dispose);

    glBindTexture(GL_TEXTURE_2D, *ret->m_texture);
    /// clamp-to-edge to remove stiching line
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(vec4(.0, .0, .0, .0)));
    glBindTexture(GL_TEXTURE_2D, 0);
    delete image;

    glBindVertexArray(*ret->m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, *ret->m_vbo);
    glBufferData(GL_ARRAY_BUFFER, ret->m_vbo->GetLength(), Buffer::ToPointer(vertices), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, *ret->m_tbo);
    glBufferData(GL_ARRAY_BUFFER, ret->m_tbo->GetLength(), Buffer::ToPointer(texCoords), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (GLvoid*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ret->m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ret->m_ibo->GetLength(), Buffer::ToPointer(indices), GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return ret;
}

void PhotoSphere::Draw()
{
    m_shader->Use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, *m_texture);
    glUniform1i(glGetUniformLocation(m_shader->Program, "Texture"), 0);
    glBindVertexArray(*m_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *m_ibo);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, m_ibo->GetCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Shader PhotoSphere::GetShader() {return *m_shader;}

void PhotoSphere::GenerateSphere(uint32_t hslice, uint32_t vslice, vector<vec3> &vertices, vector<vec3> &texCoords, vector<GLuint> &indices)
{
    double _half_pi = half_pi<double>(), _two_pi = two_pi<double>(), _pi = pi<double>();
    if (hslice < 4) hslice = 4;
    if (vslice < 2) vslice = 2;
    uint32_t vertex_count = (hslice + 1) * (vslice + 1), index_count = 3 * 2 * hslice * vslice;

    /// spherical-to-Cartesian transform
    /// theta = (-pi/2, pi/2)
    /// phi = (0, 2pi)
    /// rhs w/ y-axis up, x-axis right
//    ofstream dump("dump.txt");
//    int counter = 0;
    double v_rad_start = _half_pi - m_property->m_CroppedAreaTopPixels * _pi / m_property->m_FullPanoHeightPixels;
    double v_rad_end = _half_pi - (m_property->m_CroppedAreaTopPixels + m_property->m_CroppedAreaImageHeightPixels) * _pi / m_property->m_FullPanoHeightPixels;
    double h_rad_start = m_property->m_CroppedAreaLeftPixels * _two_pi / m_property->m_FullPanoWidthPixels;
    double h_rad_end = (m_property->m_CroppedAreaLeftPixels + m_property->m_CroppedAreaImageWidthPixels) * _two_pi / m_property->m_FullPanoWidthPixels;
    for (uint32_t v = 0; v < (vslice + 1); v++)
    {
        for (uint32_t h = 0; h < (hslice + 1); h++)
        {
            double v_rad = v_rad_start - v * (v_rad_start - v_rad_end) / vslice;
            double h_rad = h * (h_rad_end - h_rad_start) / hslice;
            /// Pre-generate cartesian coordinates, reduce energy consumption and protect environment :)
            double sv = sin(v_rad), cv = cos(v_rad), sh = sin(h_rad), ch = cos(h_rad);
            vec3 cartesian(cv * ch, sv, cv * sh);
            vertices.push_back(cartesian);
            vec3 uv_coord(h_rad / (h_rad_end - h_rad_start), (v_rad - v_rad_end) / (v_rad_start - v_rad_end), 0);
            texCoords.push_back(uv_coord);
//            dump << counter << ": " << cartesian.x << " " << cartesian.y << " " << cartesian.z << endl;
//            dump << counter << ": " << uv_coord.x << " " << uv_coord.y << endl;
//            counter++;
        }
    }
    for (uint32_t v = 0; v < vslice; v++)
    {
        for (uint32_t h = 0; h < hslice; h++)
        {
            GLuint base = v * (hslice + 1) + h;
            indices.push_back(base);
            indices.push_back(base + (hslice + 1));
            indices.push_back(base + (hslice + 1) + 1);
//            dump << base << " " << base + (hslice + 1) << " " << base + (hslice + 1) + 1 << endl;

            indices.push_back(base);
            indices.push_back(base + (hslice + 1) + 1);
            indices.push_back(base + 1);
//            dump << base << " " << base + (hslice + 1) + 1 << " " << base + 1 << endl;
        }
    }
    vertices.resize(vertex_count);
    texCoords.resize(vertex_count);
    indices.resize(index_count);
}

void PhotoSphere::Dispose()
{
    SAFE_DELETE(m_property);
    SAFE_DELETE(m_shader);
    SAFE_DELETE(m_texture);
    SAFE_DELETE(m_vao);
    SAFE_DELETE(m_vbo);
    SAFE_DELETE(m_tbo);
    SAFE_DELETE(m_ibo);
}

PhotoSphere::PhotoSphere()
{
}

PhotoSphere::~PhotoSphere()
{
    Dispose();
}

const string PhotoSphere::m_VertexShaderString = "shader.vert";

const string PhotoSphere::m_FragmentShaderString = "shader.frag";

