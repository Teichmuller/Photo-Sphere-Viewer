#include <FreeGLUTDemoWindow.h>

namespace PhotoSphereViewer
{
	shared_ptr<FreeGLUTDemoWindow> FreeGLUTDemoWindow::Create(FreeGLUTDemoWindowCreationArgs &args)
	{
		if (m_instance == nullptr)
		{
			shared_ptr<FreeGLUTDemoWindow> ret(new FreeGLUTDemoWindow);
			COND_ERROR_HANDLE_NULLPTR(ret != nullptr, "Creating FreeGLUT window failed!", NOACTION)

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

