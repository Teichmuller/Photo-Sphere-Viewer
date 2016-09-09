#ifndef __PHOTOSPHEREVIEWER_ERRORHANDLER_H__
#define __PHOTOSPHEREVIEWER_ERRORHANDLER_H__

#include <iostream>
#include <string>
#include <queue>
#include <map>

using namespace std;

namespace PhotoSphereViewer
{

    template <class ShowMethod>
    class ErrorHandler
    {
    public:
        static uint32_t Size;
        ErrorHandler& operator << (const string &e)
        {
            while (m_ErrorMessages.size() >= Size)
            {
                m_ErrorMessages.pop();
            }
            m_ErrorMessages.push(e);
            return *this;
        }

        void GetLastError(string &e)
        {
            e = m_ErrorMessages.back();
        }

        void Show(const string &e)
        {
            m_show(e);
        }

        void ShowAll()
        {
            while (!m_ErrorMessages.empty())
            {
                m_show(m_ErrorMessages.front());
                m_ErrorMessages.pop();
            }
        }

        void Clear()
        {
            while (!m_ErrorMessages.empty())
            {
                m_ErrorMessages.pop();
            }
        }

        ErrorHandler() {}
        virtual ~ErrorHandler() {}
    private:
        ShowMethod m_show;
        queue<string> m_ErrorMessages;
    };

    struct ShowInConsole
    {
        void operator () (const string &msg)
        {
            cout << msg << endl;
            cout << endl;
        }
    };

    template <class T>
    uint32_t ErrorHandler<T>::Size = 100;
    extern ErrorHandler<ShowInConsole> ConsoleErrorHandler;

    void NOACTION();

    #define CURRENT_ERROR_HANDLER                       ConsoleErrorHandler

    #define ERROR_PREFIX(msg)                           (string("ERROR: ") + __FILE__ + " (line: " + to_string(__LINE__) + ") in " + __func__ + " :\n" + (msg))

    #define COND_ERROR_HANDLE(exp, msg, act)            {if (!(exp))     {CURRENT_ERROR_HANDLER.Show(ERROR_PREFIX(msg)); (act)();                    }}
    #define COND_ERROR_HANDLE_TRUE(exp, msg, act)       {if (!(exp))     {CURRENT_ERROR_HANDLER.Show(ERROR_PREFIX(msg)); (act)();    return true;    }}
    #define COND_ERROR_HANDLE_FALSE(exp, msg, act)      {if (!(exp))     {CURRENT_ERROR_HANDLER.Show(ERROR_PREFIX(msg)); (act)();    return false;   }}
    #define COND_ERROR_HANDLE_NULLPTR(exp, msg, act)    {if (!(exp))     {CURRENT_ERROR_HANDLER.Show(ERROR_PREFIX(msg)); (act)();    return nullptr; }}
    #define COND_ERROR_HANDLE_RET(exp, msg, act, ret)   {if (!(exp))     {CURRENT_ERROR_HANDLER.Show(ERROR_PREFIX(msg)); (act)();    return ret;     }}
    #define COND_ERROR_HANDLE_EXIT(exp, msg, act, n)    {if (!(exp))     {CURRENT_ERROR_HANDLER.Show(ERROR_PREFIX(msg)); (act)();    exit(n);        }}
}

#endif // __ERRORHANDLER_H__
