#ifndef __PHOTOSPHEREVIEWER_WINDOW_H__
#define __PHOTOSPHEREVIEWER_WINDOW_H__

#include <string>
#include <memory>

using namespace std;

namespace PhotoSphereViewer
{
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
        static shared_ptr<WindowType> Create(CreateArgs &args)
        {
            return WindowType::Create(args);
        }

        virtual ~Window();
    protected:
        Window();
    };
}

#endif // __WINDOW_H__
