#ifndef CXPL_GL_SHADER_H_
#define CXPL_GL_SHADER_H_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>

#include <GL/glew.h>
#include <cxpl/Core/ErrorHandler.h>

using namespace std;

namespace cxpl
{
    namespace GL
    {
        class Shader
        {
        public:
            operator GLuint()
            {
                return m_id;
            }

            GLuint ID()
            {
                return m_id;
            }
            template <typename ShaderType>
            static shared_ptr<ShaderType> FromFile(const string &path)
            {
                ifstream shader_ifstream;
                // ensures ifstream objects are in good states:
                shader_ifstream.open(path);
                CHECK_MSG_RET_NULLPTR(shader_ifstream.is_open(), "Cannot open " << path)
                // read vertex shader string
                shader_ifstream.seekg(0, shader_ifstream.end);
                auto len = shader_ifstream.tellg();
                string shader_str(static_cast<size_t>(len), 0);
                shader_ifstream.seekg(0, shader_ifstream.beg);
                shader_ifstream.read(&shader_str[0], static_cast<streamsize>(len));
                shader_ifstream.close();
                return FromString<ShaderType>(shader_str);
            }
            template <typename ShaderType>
            static shared_ptr<ShaderType> FromString(const string &str)
            {
                shared_ptr<ShaderType> ret(new ShaderType);

                // Predefs
                GLint success;
                string infoLog(static_cast<size_t>(LogBufferSize()), 0);
                const GLchar *p_str = str.data();

                // Compile Shader implemented separately
                success = ret->Create();
                CHECK_MSG_RET_NULLPTR(success, "Failed to create shader!")
                glShaderSource(ret->m_id, 1, &p_str, NULL);
                glCompileShader(ret->m_id);
                glGetShaderiv(ret->m_id, GL_COMPILE_STATUS, &success);
                if (success == 0)
                {
                    glGetShaderInfoLog(ret->m_id, LogBufferSize(), NULL, &infoLog[0]);
                    MSG_FINAL("Shader compilation failed:\n" << infoLog, return nullptr;)
                }
                return ret;
            }
            static void LogBufferSize(GLsizei new_size)
            {
                CHECK_MSG(new_size < 8, "Log buffer size may be too small.")
                GetLogBufferSize() = new_size;
            }
            static GLsizei LogBufferSize()
            {
                return GetLogBufferSize();
            }
            virtual ~Shader()
            {
                glDeleteShader(m_id);
            }
        protected:
            GLuint m_id;
            static GLsizei &GetLogBufferSize()
            {
                static GLsizei logBufferSize = 1024;
                return logBufferSize;
            }
            Shader() : m_id(0) {}
            virtual bool Create() = 0;
        };

        class VertexShader : public Shader
        {
        public:
            static shared_ptr<VertexShader> FromFile(const string &path)
            {
                return Shader::FromFile<VertexShader>(path);
            }
            static shared_ptr<VertexShader> FromString(const string &str)
            {
                return Shader::FromString<VertexShader>(str);
            }

        private:
            VertexShader() : Shader() {}
            bool Create() override
            {
                m_id = glCreateShader(GL_VERTEX_SHADER);
                CHECK_MSG_RET_FALSE(m_id != 0, "Failed to create vertex shader!")
                return true;
            }
            friend class Shader;
        };

        class FragmentShader : public Shader
        {
        public:
            static shared_ptr<FragmentShader> FromFile(const string &path)
            {
                return Shader::FromFile<FragmentShader>(path);
            }
            static shared_ptr<FragmentShader> FromString(const string &str)
            {
                return Shader::FromString<FragmentShader>(str);
            }
        private:
            FragmentShader() : Shader() {}
            bool Create() override
            {
                m_id = glCreateShader(GL_FRAGMENT_SHADER);
                CHECK_MSG_RET_FALSE(m_id != 0, "Failed to create fragment shader!")
                return true;
            }
            friend class Shader;
        };

        class Program
        {
        public:
            operator GLuint()
            {
                return m_id;
            }
            GLuint ID()
            {
                return m_id;
            }
            static shared_ptr<Program> FromShaders(const shared_ptr<VertexShader> &vs, const shared_ptr<FragmentShader> &fs = nullptr)
            {
                shared_ptr<Program> ret(new Program);

                CHECK_MSG_RET_NULLPTR(vs, "There must be a valid vertex shader!")

                // Shader Program
                ret->m_id = glCreateProgram();
                CHECK_MSG_RET_NULLPTR(ret->m_id != 0, "Failed to create shader program!")
                glAttachShader(ret->m_id, vs->ID());
                if (fs) glAttachShader(ret->m_id, fs->ID());
                glLinkProgram(ret->m_id);
                // Print linking errors if any
                GLint success;
                string infoLog(static_cast<size_t>(LogBufferSize()), 0);
                glGetProgramiv(ret->m_id, GL_LINK_STATUS, &success);
                if (!success)
                {
                    glGetProgramInfoLog(ret->m_id, LogBufferSize(), NULL, &infoLog[0]);
                    MSG_FINAL("Program compilation failed:\n" << infoLog, return nullptr;)
                }
                return ret;
            }
            static shared_ptr<Program> FromFiles(const string &vPath, const string &fPath = string())
            {
                // Create Shaders
                shared_ptr<VertexShader> vs = VertexShader::FromFile(vPath);
                shared_ptr<FragmentShader> fs = (fPath.empty() ? nullptr : FragmentShader::FromFile(fPath));
                CHECK_MSG_RET_NULLPTR(vs, "There must be a valid vertex shader!")
                CHECK_MSG_RET_NULLPTR(fPath.empty() || (!fPath.empty() && fs), "The fragment shader is invalid!")

                return FromShaders(vs, fs);
            }
            static shared_ptr<Program> FromStrings(const string &vStr, const string &fStr = string())
            {
                // Create Shaders
                shared_ptr<VertexShader> vs = VertexShader::FromString(vStr);
                shared_ptr<FragmentShader> fs = (fStr.empty() ? nullptr : FragmentShader::FromString(fStr));
                CHECK_MSG_RET_NULLPTR(vs, "There must be a valid vertex shader!")
                CHECK_MSG_RET_NULLPTR(fStr.empty() || (!fStr.empty() && fs), "The fragment shader is invalid!")

                return FromShaders(vs, fs);
            }
            void Use()
            {
                glUseProgram(m_id);
            }
            static void LogBufferSize(GLsizei new_size)
            {
                CHECK_MSG(new_size < 8, "Log buffer size may be too small.")
                GetLogBufferSize() = new_size;
            }
            static GLsizei LogBufferSize()
            {
                return GetLogBufferSize();
            }
            ~Program()
            {
                glDeleteProgram(m_id);
            }
        private:
            GLuint m_id;
            static GLsizei &GetLogBufferSize()
            {
                static GLsizei logBufferSize = 1024;
                return logBufferSize;
            }
        };
    } //GL
} //cxpl

#endif
