#ifndef PHOTOSPHEREVIEWER_FREEGLUTDEMOWINDOW_H_
#define PHOTOSPHEREVIEWER_FREEGLUTDEMOWINDOW_H_

#include <iostream>
#include <string>
#include <memory>
#include <GL/freeglut.h>

#include <cxpl/Core/ErrorHandler.h>
#include <PhotoSphereViewer/Window.h>

using namespace std;

namespace PhotoSphereViewer
{
    struct FreeGLUTDemoWindowCreationArgs : WindowCreationArgs
    {
        int *pargc;
        char **argv;
        unsigned int displayMode = GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE;
    };

    class FreeGLUTDemoWindow : public Window
    {
    public:
        static shared_ptr<FreeGLUTDemoWindow> Create(FreeGLUTDemoWindowCreationArgs &args);
        virtual ~FreeGLUTDemoWindow();

        void MainLoop();
    //private:
        static shared_ptr<FreeGLUTDemoWindow> m_instance;
        int m_id;
        FreeGLUTDemoWindow();
    };
}

#endif // PHOTOSPHEREVIEWER_FREEGLUTDEMOWINDOW_H_
