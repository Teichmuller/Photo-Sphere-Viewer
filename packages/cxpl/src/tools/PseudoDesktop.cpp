/// Reference: https://developers.google.com/streetview/spherical-metadata

#include <vector>
#include <memory>

#include <GL/glew.h>
#include <GL/wglew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cxpl/GL/gl.h>

using namespace glm;

namespace cxpl
{
    namespace GL
    {
        using Size = vec2;
        class Transform
        {
        public:
            Transform() : m_trans(mat4()) {}
            Transform(mat4 &init) : m_trans(init) {}
            operator mat4& ()
            {
                return m_trans;
            }
            mat4 &GetMatrix()
            {
                return m_trans;
            }

        private:
            mat4 m_trans;
        };

        class Drawable
        {
        public:
            virtual void Draw() = 0;
            virtual ~Drawable() {}
        };

        class Control : public Drawable
        {
        public:
            Control() {}
            void Insert(shared_ptr<Control> child)
            {
                m_children.push_back(child);
            }
            shared_ptr<Control> Parent()
            {
                shared_ptr<Control> parent = m_parent.lock();
                return parent;
            }
            vector<shared_ptr<Control>> &Children()
            {
                return m_children;
            }

        protected:
            Transform m_transform;
            Size m_size;
            vector<shared_ptr<Control>> m_children;
            weak_ptr<Control> m_parent;
        };

        class Button : public Control
        {
        public:
            enum State {Up, Down, Hover};
            Button() : m_state(Up) {}
            virtual void Draw() override
            {

            }
         protected:
            State m_state;
        };
    }
}


void ApplyTransform()
{
    ps->GetShader().Use();
    GLint transformLoc = glGetUniformLocation(ps->GetShader().Program, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
    glutPostRedisplay();
}

void ApplyProjection()
{
    ratio = (float)WindowWidth / (float)WindowHeight;
    //projection = ortho<float>(-1, 1, -1, 1, -100, 100);
    projection = perspective<float>(fovy, ratio, 0.01, 1000);
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
            Tcs = Tcs * transform;
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
    transform = AnglesToMat(rotation);
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

    COND_ERROR_HANDLE_RET(Init(filename), "Initialzation failed!", Dispose, 0);

    glutReshapeFunc(Reshape);
    // Deregister idle function to reduce CPU time
//    glutIdleFunc(Idle);
    glutDisplayFunc(Display);
    glutMouseFunc(Mouse);
    glutMotionFunc(Motion);
    glutMouseWheelFunc(MouseWheel);
    glutSpecialFunc(Specialkey);

    MainWindow->MainLoop();

    Dispose();
    return 0;
}

