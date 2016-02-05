#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <iostream>
#include <string>
using namespace std;

struct WindowCreationArgs
{
    string title;
    int width;
    int height;
};

class Window
{
public:
    template <class WindowType, class CreateArgs>
    static WindowType *Create(CreateArgs &args)
    {
        return WindowType::Create(args);
    }

    virtual ~Window() {}
protected:
    Window() {}
};

#include <GL/freeglut.h>

struct FreeGLUTWindowCreationArgs : WindowCreationArgs
{
    int *pargc;
    char **argv;
    unsigned int displayMode = GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE;
};

class FreeGLUTWindow : public Window
{
public:
    static FreeGLUTWindow *Create(FreeGLUTWindowCreationArgs &args)
    {
        if (m_instance == nullptr)
        {
            FreeGLUTWindow *ret = new FreeGLUTWindow();
            if (ret == nullptr)
            {
                cout << "Creating FreeGLUT window failed!" << endl;
                return nullptr;
            }
            glutInit(args.pargc, args.argv);
            glutInitDisplayMode(args.displayMode);
            glutInitWindowSize(args.width, args.height);
            glutCreateWindow(args.title.data());

            m_instance = ret;
        }
        return m_instance;
    }
    virtual ~FreeGLUTWindow() {};

    void MainLoop()
    {
        glutMainLoop();
    }
private:
    static FreeGLUTWindow *m_instance;
    FreeGLUTWindow() {}
};

FreeGLUTWindow *FreeGLUTWindow::m_instance = nullptr;

#endif // __WINDOW_H__
