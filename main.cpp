/// https://developers.google.com/streetview/spherical-metadata

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "PhotoSphere.h"
#include "PhotoSphereProperty.h"


using namespace glm;

PhotoSphere *ps;

mat4 projection;
vec3 rotation(0, 0, 0);
vec3 position(0, 0, 0);
int mx = 0, my = 0;
int WindowWidth = 800, WindowHeight = 600;

float fovy = quarter_pi<float>();
float RotateVStep, RotateHStep;



void ApplyTransform()
{
    mat4 transform = mat4(1);
    transform = translate(transform, position);
    transform = rotate(transform, rotation.t, vec3(1, 0, 0));
    transform = rotate(transform, rotation.s, vec3(0, 1, 0));
//    transform = scale(transform, vec3(10, 10, 10));
    ps->GetShader().Use();
    GLint transformLoc = glGetUniformLocation(ps->GetShader().Program, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}

void ApplyProjection()
{
    GLdouble ratio = (float)WindowWidth / (float)WindowHeight;
    //projection = ortho<float>(-1, 1, -1, 1, -100, 100);
    projection = perspective<float>(fovy, ratio, 0.01, 1000);
    ps->GetShader().Use();
    GLint transformLoc = glGetUniformLocation(ps->GetShader().Program, "projection");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void Reshape(int width, int height)
{
    if (height == 0)
        height = 1;
    WindowWidth = width;
    WindowHeight = height;
    RotateHStep = fovy / height;
    RotateVStep = RotateHStep;

    glViewport(0, 0, width, height);

    ApplyProjection();
    ApplyTransform();
}

void Idle()
{
    static const int interval[] = {17, 16, 17}, nextState[] = {1, 2, 0};
    static int prevTime = 0, currentTime, currentState = 0, jump, difference;
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    difference = currentTime - prevTime;
    if (difference > interval[currentState])
    {
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//        rotation += vec3(0.01, 0., 0);
//        ApplyTransform();
        ps->Draw();

        glutSwapBuffers();

        jump = difference % 50;
        prevTime += difference - jump;
        while (jump > interval[currentState])
        {
            jump -= interval[currentState];
            prevTime += interval[currentState];
            currentState = nextState[currentState];
        }
    }
}

void Display()
{
//    glutSwapBuffers();
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mx = x;
			my = y;
//			lbuttonDown = true;
		}
		else
		{
//			lbuttonDown = false;
		}
	}
}

void Motion(int x, int y)
{
//    static int px, py;
//    static float step = 50;
    rotation.t -= (float)(y - my) * RotateVStep;
    if (rotation.t > half_pi<float>())
        rotation.t = half_pi<float>();
    if (rotation.t < -half_pi<float>())
        rotation.t = -half_pi<float>();
    rotation.s -= (float)(x - mx) * RotateHStep * (1 + abs(rotation.t));
    if (rotation.s > two_pi<float>())
        rotation.s -= two_pi<float>();
    if (rotation.s < 0)
        rotation.s += two_pi<float>();
    mx = x;
    my = y;
    ApplyTransform();
}

void MouseWheel(int wheel, int direction, int x, int y)
{
    if (direction > 0)
        fovy /= 2;
    if (direction < 0)
        fovy *= 2;
    if (fovy < quarter_pi<float>() / 9)
        fovy = quarter_pi<float>() / 9;
    if (fovy > quarter_pi<float>())
        fovy = quarter_pi<float>();
    ApplyProjection();
}

void Specialkey(int key, int x, int y)
{
    static float step = 0.01;
	if (key == GLUT_KEY_LEFT)
	{
//	    position += vec3(-step, 0, 0);
        rotation.s -= step;
	}
	if (key == GLUT_KEY_RIGHT)
	{
//	    position += vec3(step, 0, 0);
        rotation.s += step;
	}
	if (key == GLUT_KEY_UP)
	{
//	    position += vec3(0, 0, -step);
        rotation.t += step;
	}
	if (key == GLUT_KEY_DOWN)
	{
//	    position += vec3(0, 0, step);
        rotation.t -= step;
	}
    ApplyTransform();
}

void Init()
{
    ps = PhotoSphere::FromFile("../assets/PhotoSphereTestImage.jpg", 52, 52);
    int value;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &value);
    glEnable(GL_DEPTH_TEST);
    //glDisable(GL_CULL_FACE);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Photo Sphere Viewer");

    GLenum msg = glewInit();
    if (msg != GLEW_OK)
    {
        cout << "glew initialization failed!" << endl;
        exit(0);
    }

    Init();

    glutReshapeFunc(Reshape);
    glutIdleFunc(Idle);
    glutDisplayFunc(Display);
    glutMouseFunc(Mouse);
    glutMotionFunc(Motion);
    glutMouseWheelFunc(MouseWheel);
    glutSpecialFunc(Specialkey);


    glutMainLoop();
    delete ps;
    return 0;
}

