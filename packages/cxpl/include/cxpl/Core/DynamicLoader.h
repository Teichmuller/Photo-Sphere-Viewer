#ifndef CXPL_BASIC_DYNAMICLOADER_H_
#define CXPL_BASIC_DYNAMICLOADER_H_

#ifdef _WIN32
#include <direct.h>
#include <windows.h>
#else
#include <sys/type.h>
#include <dlfcn.h>
#endif

#include <functional>
#include <memory>

#include <cxpl/Core/ErrorHandler.h>
using namespace std;

namespace cxpl
{
    class HotPlugBase
    {
    public:
        virtual ~HotPlugBase() = 0;
    };
    inline HotPlugBase::~HotPlugBase() {}

    class DynamicLibrary
    {
    public:
        ~DynamicLibrary()
        {
            if (m_handle != NULL)
            {
#ifdef _WIN32
                FreeLibrary(m_handle);
#else
                dlclose(m_handle);
#endif
            }
        }
        template <typename FunPtrType>
        FunPtrType LoadSymbol(const string &symbol)
        {
             FunPtrType fp = nullptr;
#ifdef _WIN32
             fp = reinterpret_cast<FunPtrType>(GetProcAddress(m_handle, symbol.data()));
             CHECK_MSG_RET_NULLPTR(fp != NULL, "Cannot load symbol: " << symbol << endl << "Error: " << GetLastError());
#else
             dlerror();
             fp = reinterpret_cast<FunPtrType>(dlsym(m_handle, symbol.data()));
             const char *error_msg = dlerror();
             CHECK_MSG_RET_NULLPTR(error_msg != NULL, "Cannot load symbol: " << symbol << endl << "Error: " << error_msg);
#endif
             return fp;
        }

    private:
        DynamicLibrary() {}
#ifdef _WIN32
        HINSTANCE m_handle;
#else
        void *m_handle;
#endif
        friend class DynamicLoader;
    };

    class DynamicLoader
    {
    public:
        static shared_ptr<DynamicLibrary> Load(const string &file)
        {
            shared_ptr<DynamicLibrary> ret(new DynamicLibrary);
#ifdef _WIN32
            ret->m_handle = LoadLibrary(file.data());
            CHECK_MSG_RET_NULLPTR(ret->m_handle != NULL, "Cannot load dynamic library: " << file)
#else
            ret->m_handle = dlopen(file.data(), RTLD_LAZY);
            CHECK_MSG_RET_NULLPTR(ret->m_handle != NULL, "Cannot load dynamic library: " << file << endl << "Error: " << dlerror());
#endif
            return ret;
        }
    };
}

#endif
