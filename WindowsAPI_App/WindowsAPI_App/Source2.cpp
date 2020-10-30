#ifdef UNICODE
#define SetWindowText  SetWindowTextW
#else
#define SetWindowText  SetWindowTextA
#endif 
#pragma comment(lib, "wevtapi.lib")
#include "RDSmanager.h"
#include "Converter.h"
#include "WindowsManager.h"

using namespace rds::converter;
using namespace wm;


int main(void)
{
	Converter convert;
	convert.testing("Testing");
	std::wstring check = convert.s2ws("Testing2");
	//std::cout << check << std::endl;
	return 0;
}


