#ifndef __WINDOW_H__
#define __WINDOW_H__

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

#endif // __WINDOW_H__
