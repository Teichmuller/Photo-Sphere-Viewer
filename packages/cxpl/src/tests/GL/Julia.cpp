#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include <cxpl/Core/ErrorHandler.h>
#include <cxpl/GL/gl.h>

using namespace std;
using namespace glm;
using namespace cxpl;
using namespace cxpl::GL;

namespace
{
    // Window
    float WindowRatio;
    bool IsFullScreen = false;
    int WindowWidth = 640, WindowHeight = 480;

    // Julia rendering handles
    shared_ptr<Program> JuliaShader = nullptr;
    GLuint Julia_VBO, Julia_VAO, Julia_IBO;
    mat4 transform, projection;

    // Julia configuration
    GLint LocArgC, LocMaxIter, LocProj, LocTrans;
    int MaxIter = 256;
    GLfloat ArgC[2] = {.0f, .0f}, ArgS[2] = {.9f, .27f};
    GLfloat AccelMagABS = 2e-4f, AccelAng = 1e-4f, AccelMag = AccelMagABS;
    float PI = pi<float>();

    static const string vShaderStr =
R"(
#version 400
layout (location = 0) in vec2 vertex;

out vec2 colorInfo;

uniform mat4 Transform;
uniform mat4 Projection;

void main()
{
    colorInfo = vertex;
    gl_Position = Projection * Transform * vec4(vertex, 0., 1.);
})";

    static const string fShaderStr =
R"(
#version 400

in vec2 colorInfo;
out vec4 Color;
uniform vec2 C;
uniform int MaxIter;

void main()
{
    vec2 x = colorInfo.xy;
    int i;
    float color, xx = x.x * x.x, yy = x.y * x.y;
    for (i = 0; i < MaxIter; i++)
    {
        x = vec2(xx - yy, 2.0 * x.x * x.y) + C;
        xx = x.x * x.x;
        yy = x.y * x.y;
        if (xx + yy > 4.)
            break;
    }
    if (i < MaxIter)
    {
        float r = float(log(i + 1)) / float(log(MaxIter + 1));
        float g = float(log(i + 1)) / float(log(MaxIter + 1));
        float b = (colorInfo.x + 2) / 4;
        Color = vec4(r, g, b, 1.);
    }
    else
    {
        Color = vec4(0, 0, 0, 1.);
    }
}
)";

    static const float JuliaVertexData[] =
    {
         2.f,  2.f,
        -2.f,  2.f,
        -2.f, -2.f,
         2.f, -2.f
    };

    static const unsigned int JuliaIndexData[] =
    {
        0, 1, 2, 3
    };
    static const unsigned int JuliaVertCount = 4;


    void IncArgs(float delta)
    {
        //ArgS[0] += AccelMag * delta;
        ArgS[1] += AccelAng * delta;
        if (ArgS[0] > 1.5f)
            AccelMag = -AccelMagABS;
        if (ArgS[0] < -1.5f)
            AccelMag = AccelMagABS;
        if (ArgS[1] > PI)
            ArgS[1] -= PI * 2;
        ArgC[0] = ArgS[0] * cos(ArgS[1]);
        ArgC[1] = ArgS[0] * sin(ArgS[1]);
    }
    void DecArgs(float delta)
    {
        ArgS[0] -= AccelMag * delta;
        ArgS[1] -= AccelAng * delta;
        if (ArgS[0] > 1.5f)
            AccelMag = -AccelMagABS;
        if (ArgS[0] < -1.5f)
            AccelMag = AccelMagABS;
        if (ArgS[1] < -PI)
            ArgS[1] += PI * 2;
        ArgC[0] = ArgS[0] * cos(ArgS[1]);
        ArgC[1] = ArgS[0] * sin(ArgS[1]);
    }

    void KeyDown(unsigned char key, int x, int y)
    {
        switch (key)
        {
        case VK_ESCAPE:
            glutLeaveMainLoop();
            break;
        default:
            break;
        }
    }

    void Specialkey(int key, int x, int y)
    {
        if (key == GLUT_KEY_F1)
        {
            if (IsFullScreen)
            {
                glutLeaveFullScreen();
                IsFullScreen = false;
            }
            else
            {
                glutFullScreen();
                IsFullScreen = true;
            }
        }
    }

    void Resize(int width, int height)
    {
        if (height == 0)
            height = 1;
        WindowWidth = width;
        WindowHeight = height;
        WindowRatio = static_cast<float>(width) / static_cast<float>(height);
        glViewport(0, 0, WindowWidth, WindowHeight);

        if (width > height)
        {
            float h = 2 / WindowRatio;
            projection = ortho<float>(-2, 2, -h, h, -2, 2);
        }
        else
        {
            float w = 2 * WindowRatio;
            projection = ortho<float>(-w, w, -2, 2, -2, 2);
        }
        JuliaShader->Use();
        glUniformMatrix4fv(LocProj, 1, GL_FALSE, value_ptr(projection));
        glUniformMatrix4fv(LocTrans, 1, GL_FALSE, value_ptr(transform));
        glutPostRedisplay();
    }

    void Idle()
    {
        static int prev_time = 0;
        static bool start = true;
        int cur = glutGet(GLUT_ELAPSED_TIME);
        if (!start)
        {
            IncArgs(cur - prev_time);
            JuliaShader->Use();
            glUniform2fv(LocArgC, 1, ArgC);
            glutPostRedisplay();
        }
        else start = false;
        prev_time = cur;
    }

    void Display()
    {
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        JuliaShader->Use();
        glBindVertexArray(Julia_VAO);
        glDrawElements(GL_QUADS, JuliaVertCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glutSwapBuffers();
    }

    bool Init(int argc, char **argv)
    {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
        glutInitWindowSize(WindowWidth, WindowHeight);
        glutCreateWindow("Julia");

        glutKeyboardFunc(KeyDown);
        glutSpecialFunc(Specialkey);
        glutReshapeFunc(Resize);
        glutDisplayFunc(Display);
        glutIdleFunc(Idle);
        glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

        CHECK_MSG_RET(glewInit() == GLEW_OK, "GLEW initialization failed!", 0);

        JuliaShader = Program::FromStrings(vShaderStr, fShaderStr);
        CHECK_MSG_RET_FALSE(JuliaShader, "Failed to create shader program.")

        JuliaShader->Use();
        LocArgC = glGetUniformLocation(JuliaShader->ID(), "C");
        LocMaxIter = glGetUniformLocation(JuliaShader->ID(), "MaxIter");
        LocProj = glGetUniformLocation(JuliaShader->ID(), "Projection");
        LocTrans = glGetUniformLocation(JuliaShader->ID(), "Transform");
        glUniform2fv(LocArgC, 1, ArgC);
        glUniform1i(LocMaxIter, MaxIter);

        glClearColor(.0f, .0f, .0f, 1.f);
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_DEPTH_TEST);

        glGenVertexArrays(1, &Julia_VAO);
        glBindVertexArray(Julia_VAO);

        glGenBuffers(1, &Julia_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, Julia_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(JuliaVertexData), JuliaVertexData, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glGenBuffers(1, &Julia_IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Julia_IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(JuliaVertexData), JuliaIndexData, GL_STATIC_DRAW);

        glBindVertexArray(0);

        return true;
    }


}
int main(int argc, char **argv)
{
    CHECK_MSG_RET(Init(argc, argv), "Initialize failed!", 0)

    glutMainLoop();

    return 0;
}
