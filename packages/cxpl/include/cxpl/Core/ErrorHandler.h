#ifndef CXPL_ERRORHANDLER_H_
#define CXPL_ERRORHANDLER_H_

#include <iostream>
#include <string>
#include <functional>
#include <memory>

using namespace std;

namespace cxpl
{
    template <typename OStream>
    class ErrorHandler
    {
    public:
        using StreamType = OStream;
        template <typename Derived>
        static StreamType &Message()
        {
            return Derived::GetStream();
        }
        virtual ~ErrorHandler() {}
    };

    class ConsoleErrorHandler : public ErrorHandler<decltype(cout)>
    {
    public:
        static StreamType &GetStream()
        {
            static StreamType &os = cout;
            return os;
        }
    };

#ifndef CURRENT_ERROR_HANDLER
#define CURRENT_ERROR_HANDLER                       ConsoleErrorHandler
#endif
#define MSG(msg)                                    {CURRENT_ERROR_HANDLER::Message<CURRENT_ERROR_HANDLER>()\
<< "ERROR: " << __FILE__ << " (line: " << __LINE__ << ") in " << __func__ << " :\n" << msg << endl;}

#define MSG_FINAL(msg, act)                         {MSG(msg) {act}}

#define CHECK_MSG(exp, msg)                         {if (!(exp))    {MSG(msg)}}
#define CHECK_MSG_FINAL(exp, msg, act)              {if (!(exp))    {MSG_FINAL(msg, act)}}

#define CHECK_MSG_RET(exp, msg, val)                CHECK_MSG_FINAL(exp, msg, return (val);)
#define CHECK_MSG_RET_TRUE(exp, msg)                CHECK_MSG_RET(exp, msg, true)
#define CHECK_MSG_RET_FALSE(exp, msg)               CHECK_MSG_RET(exp, msg, false)
#define CHECK_MSG_RET_NULLPTR(exp, msg)             CHECK_MSG_RET(exp, msg, nullptr)

}

#endif // CXPL_ERRORHANDLER_H_
