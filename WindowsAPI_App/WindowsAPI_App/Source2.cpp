#ifdef UNICODE
#define SetWindowText  SetWindowTextW
#else
#define SetWindowText  SetWindowTextA
#endif 
#pragma comment(lib, "wevtapi.lib")
#include "RDSmanager.h"
#include "Converter.h"
#include "WindowsManager.h"

#include <wchar.h>
#define BUF_LEN 25

using namespace rds::converter;
using namespace wm;
#define STR_EQUAL 0

int main(void)
{
	Converter convert;
	convert.testing("Testing");
	std::wstring check = convert.stringToWstring("Testing2");
	LPWSTR value = convert.stringToLPWSTR("Testing");// 32-bit pointer to a string of 16-bit Unicode characters,
    
    //wchar_t str1[] = L"There are 15 pines";
    //wprintf(L"The length of the string is %ld characters\n", wcslen(str1));
    //wchar_t buf[20];
    //wcscpy(buf, L"Wuthering");
    //wcscat(buf, L" heights\n");
    //wprintf(buf);
    //if (wcscmp(L"rain", L"rainy") == STR_EQUAL) {

    //    wprintf(L"rain and rainy are equal strings\n");
    //}
    //else {

    //    wprintf(L"rain and rainy are not equal strings\n");
    //}

    //const int MAX_CHARS = 50;
    //size_t count = wcsnlen_s(str1, MAX_CHARS); //wcsnlen_s() computes the lenght of a wide string
    //int r = wcscpy_s(buf, BUF_LEN, L"W");
   
    
    
    SYSTEMTIME st = { 0 };
    wchar_t buf[128] = { 0 };

    GetLocalTime(&st);
    wsprintfW(buf, L"Today is %lu.%lu.%lu\n", st.wDay,
        st.wMonth, st.wYear);

    wprintf(buf);

	//std::cout << check << std::endl;
	return 0;
}


