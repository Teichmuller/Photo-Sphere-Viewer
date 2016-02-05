#ifndef __ERRORHANDLER_H__
#define __ERRORHANDLER_H__

#include <iostream>
#include <string>
#include <queue>

using namespace std;

template <class ShowMethod>
class ErrorHandler
{
public:
    static uint32_t Size = 100;
    ErrorHandler& operator << (ErrorHandler &handler, const string &e)
    {
        while (m_ErrorMessages.size() >= 100)
        {
            m_ErrorMessages.pop();
        }
        m_ErrorMessages.push(e);
        return handler;
    }

    void GetLastError(string &e)
    {
        e = m_ErrorMessages.back();
    }

    void Show(string &e)
    {
        ShowMethod(e);
    }

    void ShowAll()
    {
        while (!m_ErrorMessages.empty())
        {
            ShowMethod(m_ErrorMessages.front());
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
    queue<string> m_ErrorMessages;
};

struct ShowInConsole
{
    void operator () (const string &msg)
    {
        cout << msg << endl;
    }
};

ErrorHandler<ShowInConsole> ConsoleErrorHandler;

void NOACTION() {}

#define CURRENT_ERROR_HANDLER                       ConsoleErrorHandler;

#define COND_ERROR_HANDLE(exp, msg)                 COND_ERROR_HANDLE(exp, msg, NOACTION)
#define COND_ERROR_HANDLE_TRUE(exp, msg)            COND_ERROR_HANDLE_TRUE(exp, msg, NOACTION)
#define COND_ERROR_HANDLE_FALSE(exp, msg, act)      COND_ERROR_HANDLE_FALSE(exp, msg, NOACTION)
#define COND_ERROR_HANDLE_NULLPTR(exp, msg, act)    COND_ERROR_HANDLE_NULLPTR(exp, msg, NOACTION)
#define COND_ERROR_HANDLE_EXIT(exp, msg, act)       COND_ERROR_HANDLE_EXIT(exp, msg, NOACTION)
#define COND_ERROR_HANDLE_EXIT(exp, msg, act, n)    COND_ERROR_HANDLE_EXIT(exp, msg, NOACTION, n)

#define COND_ERROR_HANDLE(exp, msg, act)            {if (x)     {CURRENT_ERROR_HANDLER.Show(msg); (act)();                    }}
#define COND_ERROR_HANDLE_TRUE(exp, msg, act)       {if (x)     {CURRENT_ERROR_HANDLER.Show(msg); (act)();    return true;    }}
#define COND_ERROR_HANDLE_FALSE(exp, msg, act)      {if (x)     {CURRENT_ERROR_HANDLER.Show(msg); (act)();    return false;   }}
#define COND_ERROR_HANDLE_NULLPTR(exp, msg, act)    {if (x)     {CURRENT_ERROR_HANDLER.Show(msg); (act)();    return nullptr; }}
#define COND_ERROR_HANDLE_EXIT(exp, msg, act)       {if (x)     {CURRENT_ERROR_HANDLER.Show(msg); (act)();    exit(1);        }}
#define COND_ERROR_HANDLE_EXIT(exp, msg, act, n)    {if (x)     {CURRENT_ERROR_HANDLER.Show(msg); (act)();    exit(n);        }}

#endif // __ERRORHANDLER_H__
