<<<<<<< HEAD
#include <CXPL/basic/ErrorHandler.h>

namespace CXPL
{
    ErrorHandler<decltype(cout)> ConsoleErrorHandler;
    function<void(void)> NullAction([](){});
=======
#include <ErrorHandler.h>

namespace PhotoSphereViewer
{

    ErrorHandler<ShowInConsole> ConsoleErrorHandler;

    void NOACTION()
    {
    }
>>>>>>> 49a8da9994ef4d1e1ae89cae56b17c1360461b8e
}
