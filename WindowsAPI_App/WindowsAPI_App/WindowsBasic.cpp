//#include <stdio.h>
//#include <stdlib.h>
//#include <assert.h>
//#include <windows.h>
//#include <stdio.h>
//#include <winevt.h>
//#include <iostream>
//#define BUFFER_SIZE 100
//LPWSTR ConvertString(const std::string& instr)
//{
//    // Assumes std::string is encoded in the current Windows ANSI codepage
//    int bufferlen = ::MultiByteToWideChar(CP_ACP, 0, instr.c_str(), instr.size(), NULL, 0);
//    if (bufferlen == 0)
//    {
//        return 0;
//    }
//    // Allocate new LPWSTR - must deallocate it later
//    LPWSTR widestr = new WCHAR[bufferlen + 1];
//    ::MultiByteToWideChar(CP_ACP, 0, instr.c_str(), instr.size(), widestr, bufferlen);
//    // Ensure wide string is null terminated
//    widestr[bufferlen] = 0;
//    // Do something with widestr
//    return widestr;
//    //delete[] widestr;
//}
//int main(void)
//{
//    size_t   i;
//    char* pMBBuffer = (char*)malloc(BUFFER_SIZE);
//    //wchar_t* pWCBuffer = L"Hello, world.";
//
//    wchar_t* pWCBuffer=ConvertString("Hello, world.");
//
//    printf("Convert wide-character string:n");
//
//    // Conversion
//    wcstombs_s(&i, pMBBuffer, (size_t)BUFFER_SIZE,
//        pWCBuffer, (size_t)BUFFER_SIZE);
//
//    // Output
//    printf("   Characters converted: %un", i);
//    printf("    Multibyte character: %snn",
//        pMBBuffer);
//
//    // Free multibyte character buffer
//    if (pMBBuffer)
//    {
//        free(pMBBuffer);
//    }
//}