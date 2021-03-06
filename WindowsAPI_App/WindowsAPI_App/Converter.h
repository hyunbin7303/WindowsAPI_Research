#ifndef CONVERTER_H
#define CONVERTER_H
//#ifdef UNICODE
//#define SetWindowText  SetWindowTextW
//#else
//#define SetWindowText  SetWindowTextA
//#endif 
#define BUFFER_SIZE 100
#include <windows.h>
#include <stdio.h>
#include <winevt.h>
#include <tlhelp32.h>
#include <iostream>
#include <memory>
#include <vector>

namespace rds {
    namespace converter {
        class Converter
        {
            public:
                static LPWSTR stringToLPWSTR(const std::string& instr);
                std::wstring stringToWstring(const std::string& str);
                void testing(const std::string& s);
        };


    }
}




#endif // !CONVERTER_H


