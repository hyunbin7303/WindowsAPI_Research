#include "Converter.h"


LPWSTR rds::converter::Converter::stringToLPWSTR(const std::string& instr)
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
std::wstring rds::converter::Converter::stringToWstring(const std::string& str)
{
    int len;
    int slength = (int)str.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), slength, buf, len);
    std::wstring r(buf);
    std::wcout << r << std::endl;
    delete[] buf;
    return r;
}
void rds::converter::Converter::testing(const std::string& s)
{
    size_t   i;
    char* pMBBuffer = (char*)malloc(BUFFER_SIZE);
    const wchar_t* pWCBuffer = L"Hello, world.";
    printf("Convert wide-character string:\n");
    //Converts a sequence of wide characters to a corresponding sequence of multibyte characters.
    wcstombs_s(&i, pMBBuffer, (size_t)BUFFER_SIZE,
        pWCBuffer, (size_t)BUFFER_SIZE);

    // Output
    printf("   Characters converted: %u\n", i);
    printf("    Multibyte character: %s\n\n",
        pMBBuffer);

    // Free multibyte character buffer
    if (pMBBuffer)
    {
        free(pMBBuffer);
    }
}
