
#include <GL/glew.h>
#include <GL/wglew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <iostream>

#include <FreeGLUTDemoWindow.h>
#include <PhotoSphere.h>
#include <PhotoSphereProperty.h>
#include <ErrorHandler.h>
#include <exiv2/exiv2.hpp>

using namespace std;
using namespace glm;
using namespace PhotoSphereViewer;

shared_ptr<FreeGLUTDemoWindow> MainWindow;
shared_ptr<PhotoSphere> ps;

mat4 projection(1);
mat4 transform_mat(1);
mat4 Tcs;

vec3 rotation(pi<float>(), -pi<float>() / 4, 0);
vec3 position(0);
vec3 CurrentPos = vec3(0), PrevPos = vec3(0);

int WindowWidth = 800, WindowHeight = 600;
GLdouble ratio = (float)WindowWidth / (float)WindowHeight;
bool IsFullScreen = false;

float fovy = quarter_pi<float>();

vec3 MouseToSphere(vec2 pos)
{
    float cx = (pos.x * 2 - WindowWidth) / WindowWidth;
    float cy = -(pos.y * 2 - WindowHeight) / WindowHeight;
    float tan_phi = cx * ratio * tan(fovy / 2);//, phi = atan(tan_phi);
    float tan_theta = cy * tan(fovy / 2), theta = atan(tan_theta);
//    float alpha = atan(tan_theta / sqrt(1 + tan_phi * tan_phi));
    float beta = atan(tan_phi / sqrt(1 + tan_theta * tan_theta));
    /// minus stands for space rotation rather than basis rotation
    return vec3(-beta, theta, 0);
}


void ApplyTransform()
{
    ps->GetShader().Use();
    GLint transformLoc = glGetUniformLocation(ps->GetShader().Program, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform_mat));
    glutPostRedisplay();
}

void ApplyProjection()
{
    ratio = (float)WindowWidth / (float)WindowHeight;
    //projection = ortho<float>(-1, 1, -1, 1, -100, 100);
    projection = perspective<float>(fovy, ratio, 0.01, 1000);
    ps->GetShader().Use();
    GLint transformLoc = glGetUniformLocation(ps->GetShader().Program, "projection");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glutPostRedisplay();
}

void Reshape(int width, int height)
{
    if (height == 0)
        height = 1;
    WindowWidth = width;
    WindowHeight = height;
    ratio = (float)WindowWidth / (float)WindowHeight;

    glViewport(0, 0, width, height);

    ApplyProjection();
    ApplyTransform();
}

void Display()
{
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//        rotation += vec3(0.01, 0., 0);
//        ApplyTransform();
    ps->Draw();

    glutSwapBuffers();
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
            PrevPos = MouseToSphere(vec2(x, y));
            Tcs = AnglesToMat(-PrevPos);
            Tcs = Tcs * transform_mat;
		}
		else if (state == GLUT_UP)
		{

		}
	}
}

void Motion(int x, int y)
{
    CurrentPos = MouseToSphere(vec2(x, y));
    mat4 Tsc = inverse(AnglesToMat(-CurrentPos));
    PrevPos = CurrentPos;

//    vec3 prev_rotation = rotation;

    mat4 toBeTransform = Tsc * Tcs;
    rotation = MatToAngles(toBeTransform);
    transform_mat = AnglesToMat(rotation);
//    cout << "CurrentPos: " << CurrentPos / pi<float>() * 180.f << endl;
//    cout << "rotation: " << rotation / pi<float>() * 180.f << endl;
//    cout << "transform: " << endl << transform;
//    cout << "toBeTransform: " << endl << toBeTransform;
//    cout << "delta_rot: " << (rotation - prev_rotation) / pi<float>() * 180.f << endl;
//    cout << "delta_pos: " << (CurrentPos - PrevPos) / pi<float>() * 180.f << endl;
    ApplyTransform();
}

void MouseWheel(int wheel, int direction, int x, int y)
{
    if (direction > 0)
        fovy /= 2;
    if (direction < 0)
        fovy *= 2;
    if (fovy < quarter_pi<float>() / 16)
        fovy = quarter_pi<float>() / 16;
    if (fovy > half_pi<float>())
        fovy = half_pi<float>();
    ApplyProjection();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
    {
    case 27:
        glutLeaveMainLoop();
        break;
    default:
        break;
    }
    ApplyTransform();
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
    ApplyTransform();
}

bool Init(const string &filename)
{
    ps = PhotoSphere::FromFile(filename, 104, 52);
    COND_ERROR_HANDLE_FALSE(ps != nullptr, "Failed to create class PhotoSphere!", NOACTION)
//    int value;
//    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &value);

    glEnable(GL_DEPTH_TEST);

    // Enable V-Sync to avoid tearing
    wglSwapIntervalEXT(1);
    return true;
}

void Dispose()
{
}

int main(int argc, char **argv)
{/*
    COND_ERROR_HANDLE_RET(argc > 1, "Usage: PhotoSphereViewer filename", NOACTION, 0);
    string filename(argv[1]);
*/
    string filename("TestImage.jpg");
    /*
    cout << "Entrying" << endl;
    const string panoramaImageName("F:/2016-8-12~14 (Kanas)/PANO_20160813_123415.jpg");
    const string ordinaryImageName("F:/2016-8-12~14 (Kanas)/IMG_20160812_125349.jpg");
    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(panoramaImageName);

    COND_ERROR_HANDLE_RET(image.get() != 0, "Open image failed!", NOACTION, 0);
    cout << "Read successful: " << image.get() << endl;

    image->readMetadata();
    image->printStructure(cout, Exiv2::kpsXMP);

    Exiv2::XmpData& xmp = image->xmpData();
    for (auto i = xmp.begin(); i != xmp.end(); i++)
    {
        cout << i->key() << ' '
             << i->count() << ' '
             << i->size() << ' '
             << i->toString() << endl;
    }
    const string longTestKey("Xmp.GPano.CroppedAreaImageWidthPixels");
    const string floatTestKey("Xmp.GPano.PoseHeadingDegrees");
    const string boolTestKey("Xmp.GPano.UsePanoramaViewer");
    cout << longTestKey << ' ' << xmp[longTestKey].toLong() << endl;
    cout << floatTestKey << ' ' << xmp[floatTestKey].toFloat() << endl;
    cout << boolTestKey << ' ' << xmp[boolTestKey].toLong() << endl;
    shared_ptr<PhotoSphereProperty> ps = PhotoSphereProperty::FromFile(panoramaImageName);
    cout << ps->m_UsePanoramaViewer << endl;
    cout << ps->m_ProjectionType << endl;
    cout << ps->m_CroppedAreaImageWidthPixels << endl;
    cout << ps->m_PoseHeadingDegrees << endl;
    */

    cout << "Creating Window..." << endl;
    FreeGLUTDemoWindowCreationArgs args;
    args.pargc = &argc;
    args.argv = argv;
    args.title = "Photo Sphere Viewer";
    args.width = 800;
    args.height = 600;
    MainWindow = Window::Create<FreeGLUTDemoWindow>(args);
    cout << "Window created." << endl;
    cout << "Instance: " << FreeGLUTDemoWindow::m_instance << endl;
    cout << "ID: " << MainWindow->m_id << endl;

    cout << "Initializing GLEW..." << endl;
    COND_ERROR_HANDLE_RET(glewInit() == GLEW_OK, "GLEW initialization failed!", Dispose, 0);
    cout << "GLEW initialled." << endl;

    COND_ERROR_HANDLE_RET(Init(filename), "Initialzation failed!", Dispose, 0);

    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    cout << "Registering functions..." << endl;
    glutReshapeFunc(Reshape);
    // Deregister idle function to reduce CPU time
//    glutIdleFunc(Idle);
    glutDisplayFunc(Display);
    glutMouseFunc(Mouse);
    glutMotionFunc(Motion);
    glutMouseWheelFunc(MouseWheel);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(Specialkey);
    cout << "Function registered." << endl;

    cout << "Entering main loop..." << endl;
    MainWindow->MainLoop();
    cout << "Left main loop." << endl;

    Dispose();
    cout << "Disposed." << endl;

    return 0;
}

