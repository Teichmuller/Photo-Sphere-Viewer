#include <CXPL/basic/ErrorHandler.h>

namespace CXPL
{
    ErrorHandler<decltype(cout)> ConsoleErrorHandler;
    function<void(void)> NullAction([](){});
}
