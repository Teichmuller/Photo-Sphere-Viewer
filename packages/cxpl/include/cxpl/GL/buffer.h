#ifndef CXPL_GL_BUFFER_H_
#define CXPL_GL_BUFFER_H_

#include <iostream>
#include <vector>
#include <memory>
#include <GL/glew.h>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

namespace cxpl
{
    namespace GL
    {
        /// \class Buffer buffer.h
        /// \brief Base class for OpenGL Buffers
        ///
        /// Provide a universal interface to initialize and delete buffers. Classes inherited from this class
        /// should implement all pure virtual functions and keep constructors private and accessible by this class.
        /// Inherited class should not able to exist as an entity, they must be constructed via static function
        /// Buffer::CreateBuffer(), which returns a pointer if buffer is constructed successfully or nullptr if failed.
        ///
        class Buffer
        {
        public:
            /// Get buffer ID in an explicit way.
            GLuint GetID() {return m_id;}

            /// \brief Create a buffer of any type
            ///
            /// \tparam T Type of buffer
            /// \return a valid pointer of type T, or nullptr
            ///
            template <class T>
            static shared_ptr<T> CreateBuffer()
            {
                shared_ptr<T> ret(new T());
                if (!ret->GenerateBuffer())
                    return nullptr;
                else
                    return ret;
            }
            /// \brief Convert vector of data to array pointer
            ///
            /// \tparam T Data type
            /// \param array Data to be converted
            /// \return the converted pointer
            ///
            template <class T>
            static const T* ToPointer(const vector<T> &array)
            {
                return &array[0];
            }
            /// Implicit conversion to buffer ID.
            operator GLuint() const {return m_id;}
            /// Interface to delete buffer
            virtual ~Buffer()
            {
            }
        protected:
            /// \brief Interface to create a buffer
            ///
            /// \return True if buffer created successfully, otherwise false.
            virtual bool GenerateBuffer() = 0;
            GLuint m_id = 0;
            Buffer() {}
        };

        class BufferObject : public Buffer
        {
        public:
            ~BufferObject()
            {
                if (m_id != 0)
                    glDeleteBuffers(1, &m_id);
            }
            /// \brief Specify data format in the buffer
            ///
            /// \param size The size(in byte) for each unit
            /// \param count The number of units
            /// \tparam T The type of units
            /// \param data The container of data
            ///
            void SetFormat(GLuint size, GLuint count) {m_size = size; m_count = count;}
            template <class T>
            void SetFormat(const vector<T> &data) {SetFormat(sizeof(T), data.size());}
            GLuint GetSize() {return m_size;}
            GLuint GetCount() {return m_count;}
            GLuint GetLength() {return m_size * m_count;}
        private:
            GLuint m_size = 0;
            GLuint m_count = 0;
            bool GenerateBuffer() override
            {
                glGenBuffers(1, &m_id);
                if (m_id == 0)
                    return false;
                else
                    return true;
            }
            friend class Buffer;
            BufferObject() {}
        };

        class VertexArrayObject : public Buffer
        {
        public:
            ~VertexArrayObject()
            {
                if (m_id != 0)
                    glDeleteVertexArrays(1, &m_id);
            }
        private:
            bool GenerateBuffer() override
            {
                glGenVertexArrays(1, &m_id);
                if (m_id == 0)
                    return false;
                else
                    return true;
            }
            friend class Buffer;
            VertexArrayObject() {}
        };
    } //GL
} //cxpl

#endif
