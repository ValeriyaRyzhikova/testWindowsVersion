#include<iostream>
#include<string>
#include<windows.h>

std::string getVersion(OSVERSIONINFO osvi) {
    std::string result;

    switch (osvi.dwMajorVersion)
    {
    case 10:
        result = "Windows 10";
        break;
    case 6:
        switch (osvi.dwMinorVersion)
        {
        case 3:
            result = "Windows 8.1";
            break;
        case 2:
            result = "Windows 8";
            break;
        case 1:
            result = "Windows 7";
            break;
        case 0:
            result = "Windows Vista";
            break;
        }
        break;
    case 5:
        switch (osvi.dwMinorVersion)
        {
        case 2:
            result = "Windows XP Edition";
            break;
        case 1:
            result = "Windows XP";
            break;
        case 0:
            result = "Windows 2000";
            break;
        }
        break;
    }

    return result;
}

BOOL Is64BitWindows()
{
#if defined(_WIN64)
    return TRUE;  // 64-bit programs run only on Win64
#elif defined(_WIN32)
    // 32-bit programs run on both 32-bit and 64-bit Windows
    // so must sniff
    BOOL f64 = FALSE;
    IsWow64Process(GetCurrentProcess(), &f64);
    return  f64;
#else
    return FALSE; // Win64 does not support Win16
#endif
}

std::string getBit()
{
    if (Is64BitWindows())
        return "x64";
    return "x32";
}

OSVERSIONINFO getInfoOS()
{
    OSVERSIONINFO osvi;
    BOOL bIsWindowsXPorLater;

    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    GetVersionEx(&osvi);

    return osvi;
}

int main()
{
    OSVERSIONINFO osvi = getInfoOS();
    std::cout << "Operating System: " << getVersion(osvi) << " " << getBit() << " (Build " << osvi.dwBuildNumber << ")";
    return 0;
}
