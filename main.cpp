/// https://developers.google.com/streetview/spherical-metadata

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

#include <FreeGLUTDemoWindow.h>
#include <PhotoSphere.h>
#include <PhotoSphereProperty.h>
#include <ErrorHandler.h>

using namespace glm;

FreeGLUTDemoWindow *MainWindow;
PhotoSphere *ps;

mat4 projection(1);
mat4 transform(1);
vec3 rotation(0);
vec3 position(0);
int mx = 0, my = 0;
vec3 CurrentPos = vec3(0), PrevPos = vec3(0);
int WindowWidth = 800, WindowHeight = 600;
GLdouble ratio = (float)WindowWidth / (float)WindowHeight;
bool IsFullScreen = false;

float fovy = quarter_pi<float>();
float RotateVStep, RotateHStep;

vec3 MouseToSphere(vec2 pos)
{
    float cx = (pos.x * 2 - WindowWidth) / WindowWidth;
    float cy = (pos.y * 2 - WindowHeight) / WindowHeight;
    return vec3(atan(cx * tan(fovy * ratio / 2)), atan(cy * tan(fovy / 2)), 0);//
}

void ApplyTransform()
{
    transform = mat4(1);
    transform = translate(transform, position);
//    float cot_H = 1 / tan(rotation.s), cot_V = 1 / tan(rotation.t), ch2 = cot_H * cot_H, cv2 = cot_V * cot_V;
//    float z_angle = half_pi<float>() - acos(sqrt(1 / (1 + cv2 + cv2 * ch2)));
//    if ((rotation.t > 0 && rotation.s > pi<float>()) || (rotation.t < 0 && rotation.s < pi<float>())) z_angle *= -1;
//    transform = rotate(transform, z_angle, vec3(0, 0, 1));
    transform = rotate(transform, rotation.t, vec3(1, 0, 0));
    transform = rotate(transform, rotation.s, vec3(0, 1, 0));
//    cout << "theta = " << rotation.t / pi<float>() * 180 << endl;
//    cout << "phi = " << rotation.s / pi<float>() * 180 << endl;
//    cout << "z = " << z_angle / pi<float>() * 180 << endl;
//    cout << endl;
//    transform = scale(transform, vec3(10, 10, 10));
    ps->GetShader().Use();
    GLint transformLoc = glGetUniformLocation(ps->GetShader().Program, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}

void ApplyProjection()
{
    ratio = (float)WindowWidth / (float)WindowHeight;
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
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
//			mx = x;
//			my = y;
            CurrentPos = MouseToSphere(vec2(x, y));
		}
		else
		{
		}
	}
}

void Motion(int x, int y)
{
//    mx = x;
//    my = y;
    PrevPos = CurrentPos;
    CurrentPos = MouseToSphere(vec2(x, y));
    rotation -= (CurrentPos - PrevPos);
    if (rotation.t > half_pi<float>())
        rotation.t = half_pi<float>();
    if (rotation.t < -half_pi<float>())
        rotation.t = -half_pi<float>();
    if (rotation.s > two_pi<float>())
        rotation.s -= two_pi<float>();
    if (rotation.s < 0)
        rotation.s += two_pi<float>();
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
        rotation.s -= step;
	}
	if (key == GLUT_KEY_RIGHT)
	{
        rotation.s += step;
	}
	if (key == GLUT_KEY_UP)
	{
        rotation.t += step;
	}
	if (key == GLUT_KEY_DOWN)
	{
        rotation.t -= step;
	}
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
    ApplyTransform();
}

bool Init(const string &filename)
{
    ps = PhotoSphere::FromFile(filename, 104, 52);
    COND_ERROR_HANDLE_FALSE(ps != nullptr, "Failed to create class PhotoSphere!", NOACTION)
//    int value;
//    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &value);

    glEnable(GL_DEPTH_TEST);
    //glDisable(GL_CULL_FACE);
    return true;
}

void Dispose()
{
    SAFE_DELETE(ps)
    SAFE_DELETE(MainWindow)
}

int main(int argc, char **argv)
{
    COND_ERROR_HANDLE_RET(argc > 1, "Usage: PhotoSphereViewer filename", NOACTION, 0);
    string filename(argv[1]);

    FreeGLUTDemoWindowCreationArgs args;
    args.pargc = &argc;
    args.argv = argv;
    args.title = "Photo Sphere Viewer";
    args.width = 800;
    args.height = 600;
    MainWindow = Window::Create<FreeGLUTDemoWindow>(args);

    COND_ERROR_HANDLE_RET(glewInit() == GLEW_OK, "GLEW initialization failed!", Dispose, 0);

    COND_ERROR_HANDLE_EXIT(Init(filename), "Initialzation failed!", Dispose, 0);

    glutReshapeFunc(Reshape);
    glutIdleFunc(Idle);
    glutDisplayFunc(Display);
    glutMouseFunc(Mouse);
    glutMotionFunc(Motion);
    glutMouseWheelFunc(MouseWheel);
    glutSpecialFunc(Specialkey);

    MainWindow->MainLoop();

    Dispose();
    return 0;
}

