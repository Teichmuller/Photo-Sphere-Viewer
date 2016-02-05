#ifndef __FREEGLUTDEMOWINDOW_H__
#define __FREEGLUTDEMOWINDOW_H__

#include <iostream>
#include <string>
#include <ErrorHandler.h>
#include <Window.h>
#include <GL/freeglut.h>

struct FreeGLUTDemoWindowCreationArgs : WindowCreationArgs
{
    int *pargc;
    char **argv;
    unsigned int displayMode = GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE;
};

class FreeGLUTDemoWindow : public Window
{
public:
    static FreeGLUTDemoWindow *Create(FreeGLUTDemoWindowCreationArgs &args)
    {
        if (m_instance == nullptr)
        {
            FreeGLUTDemoWindow *ret = new FreeGLUTDemoWindow();
            COND_ERROR_HANDLE_NULLPTR(ret != nullptr, "Creating FreeGLUT window failed!", NOACTION)

            glutInit(args.pargc, args.argv);
            glutInitDisplayMode(args.displayMode);
            glutInitWindowSize(args.width, args.height);
            ret->m_id = glutCreateWindow(args.title.data());

            m_instance = ret;
        }
        return m_instance;
    }
    virtual ~FreeGLUTDemoWindow() {};

    void MainLoop()
    {
        glutMainLoop();
    }
private:
    static FreeGLUTDemoWindow *m_instance;
    int m_id;
    FreeGLUTDemoWindow() {}
};
FreeGLUTDemoWindow *FreeGLUTDemoWindow::m_instance = nullptr;

#endif // FREEGLUTDEMOWINDOW_H
