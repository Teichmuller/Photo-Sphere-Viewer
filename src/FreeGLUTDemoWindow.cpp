<<<<<<< HEAD
#include <PhotoSphereViewer/FreeGLUTDemoWindow.h>

using namespace cxpl;
=======
#include <FreeGLUTDemoWindow.h>
>>>>>>> 49a8da9994ef4d1e1ae89cae56b17c1360461b8e

namespace PhotoSphereViewer
{
	shared_ptr<FreeGLUTDemoWindow> FreeGLUTDemoWindow::Create(FreeGLUTDemoWindowCreationArgs &args)
	{
		if (m_instance == nullptr)
		{
			shared_ptr<FreeGLUTDemoWindow> ret(new FreeGLUTDemoWindow);
<<<<<<< HEAD
            CHECK_MSG_RET_NULLPTR(ret != nullptr, "Creating FreeGLUT window failed!")
=======
			COND_ERROR_HANDLE_NULLPTR(ret != nullptr, "Creating FreeGLUT window failed!", NOACTION)
>>>>>>> 49a8da9994ef4d1e1ae89cae56b17c1360461b8e

			glutInit(args.pargc, args.argv);
			glutInitDisplayMode(args.displayMode);
			glutInitWindowSize(args.width, args.height);
			ret->m_id = glutCreateWindow(args.title.data());

			m_instance = ret;
		}
		return m_instance;
	}
	FreeGLUTDemoWindow::~FreeGLUTDemoWindow() {};

	void FreeGLUTDemoWindow::MainLoop()
	{
		glutMainLoop();
	}
	FreeGLUTDemoWindow::FreeGLUTDemoWindow() {}


    shared_ptr<FreeGLUTDemoWindow> FreeGLUTDemoWindow::m_instance = nullptr;
}

