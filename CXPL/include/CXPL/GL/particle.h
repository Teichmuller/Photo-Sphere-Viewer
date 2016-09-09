#ifndef __CXPL_GL_PARTICLE_H__
#define __CXPL_GL_PARTICLE_H__

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <CXPL/GL/shader.h>
#include <CXPL/basic/field.h>

namespace CXPL
{
	using namespace glm;

	#define DELETEPTR(ptr) if ((ptr) != nullptr) delete ptr;
	#define DELETEVERTEXARRAYPTR(ptr) if ((ptr) != 0) glDeleteVertexArrays(1, &ptr);
	#define DELETEBUFFERPTR(ptr) if ((ptr) != 0) glDeleteBuffers(1, &ptr);
	#define DELETEARRAYPTR(ptr) if ((ptr) != nullptr) delete[] (ptr);

	template <class IndependentType, class DependentType>
	class Particle
	{
	public:
		virtual void Draw(Shader *shader) = 0;
		virtual void Reset() = 0;
		uint32_t GetSize() const {return m_count;}

	//    template <class T>
	//    static T *CreateParticle()
	//    {
	//        Particle *_tmp = new T;
	//        if (!_tmp->Generate())
	//            return nullptr;
	//        else
	//            return static_cast<T*>(_tmp);
	//    }

		virtual ~Particle()
		{
			DELETEPTR(m_vertexArray);
	//        DELETEVERTEXARRAYPTR(m_vertexArray);
			DELETEPTR(m_vertexBuffer);
	//        DELETEBUFFERPTR(m_vertexBuffer);
			DELETEPTR(m_indicesBuffer);
	//        DELETEBUFFERPTR(m_indicesBuffer);

	//        DELETEARRAYPTR(m_vertices)
	//        DELETEARRAYPTR(m_indices)

			DELETEPTR(m_displacementBuffer);
	//        DELETEBUFFERPTR(m_displacementBuffer);
			DELETEPTR(m_rotationBuffer);
	//        DELETEBUFFERPTR(m_rotationBuffer);
			DELETEPTR(m_scaleBuffer);
	//        DELETEBUFFERPTR(m_scaleBuffer);

	//        DELETEARRAYPTR(m_rotation)
	//        DELETEARRAYPTR(m_scale)
	//        DELETEARRAYPTR(m_displacement)

	//        DELETEARRAYPTR(m_active)
		};
	protected:
		uint32_t m_count = 0;

		VertexArrayObject *m_vertexArray;
	//    GLuint m_vertexArray = 0;
		BufferObject *m_vertexBuffer;
	//    GLuint m_vertexBuffer = 0;
		BufferObject *m_indicesBuffer;
	//    GLuint m_indicesBuffer = 0;

	//    vector<vec3> m_vertices;
	//    vector<GLuint> m_indices;

		BufferObject *m_displacementBuffer;
	//    GLuint m_displacementBuffer = 0;
		BufferObject *m_rotationBuffer;
	//    GLuint m_rotationBuffer = 0;
		BufferObject *m_scaleBuffer;
	//    GLuint m_scaleBuffer = 0;
		vector<vec3> m_displacement;
		vector<vec3> m_rotation;
		vector<vec3> m_scale;

		vector<bool> m_active;

		Field<IndependentType, DependentType> *m_velocityField = nullptr;
		Field<IndependentType, DependentType> *m_rotationField = nullptr;
		Field<IndependentType, DependentType> *m_scaleField = nullptr;

		//virtual bool Generate() = 0;
		Particle() {};
	};

	template <class IndependentType, class DependentType>
	class TexturedParticle : public Particle<vec3, vec3>
	{
	public:
		virtual ~TexturedParticle()
		{
			DELETEBUFFERPTR(m_texCoordBuffer);
	//        DELETEARRAYPTR(m_texCoord);
		};
	protected:
		GLuint m_texCoordBuffer = 0;
		vector<vector<vec3>> m_texCoords;
		vector<Texture*> m_textures;
		TexturedParticle()
		: Particle<vec3, vec3>() {};
	};

}

#endif
