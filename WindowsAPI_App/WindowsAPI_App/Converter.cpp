#include "Converter.h"
LPWSTR Converter::ConvertString(const std::string& instr)
{
    // Assumes std::string is encoded in the current Windows ANSI codepage
    int bufferlen = ::MultiByteToWideChar(CP_ACP, 0, instr.c_str(), instr.size(), NULL, 0);
    if (bufferlen == 0)
    {
        return 0;
    }
    // Allocate new LPWSTR - must deallocate it later
    LPWSTR widestr = new WCHAR[bufferlen + 1];
    ::MultiByteToWideChar(CP_ACP, 0, instr.c_str(), instr.size(), widestr, bufferlen);
    // Ensure wide string is null terminated
    widestr[bufferlen] = 0;
    // Do something with widestr
    return widestr;
    //delete[] widestr;
}

std::wstring Converter::s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}