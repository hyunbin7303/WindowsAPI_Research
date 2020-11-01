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
    
    
    SYSTEMTIME st = { 0 };
    wchar_t buf[128] = { 0 };

    GetLocalTime(&st);
    wsprintfW(buf, L"Today is %lu.%lu.%lu\n", st.wDay,
        st.wMonth, st.wYear);

    wprintf(buf);

	//std::cout << check << std::endl;
	return 0;
}


