#ifdef UNICODE
#define SetWindowText  SetWindowTextW
#else
#define SetWindowText  SetWindowTextA
#endif 
#pragma comment(lib, "wevtapi.lib")
#include "RDSmanager.h"
#include "Converter.h"
#include "WindowsManager.h"
#include "RegistryManager.h"
#include <wchar.h>
#include <exception>
#include <vector>

#define BUF_LEN 25

using namespace rds::converter;
using namespace wm;
#define STR_EQUAL 0

int main(void)
{

	// WindowsManager Testing
	WindowsManager winM;
	winM.DisplayToday();
	//winM.GetProcessId(L"Testing", "", "");
	//winM.find_process("", 1234);
	winM.DisplayAllProcess();
	//winM.testingSnapshot();

	//Converter Testing
	Converter convert;
	convert.testing("Testing");
	std::wstring check = convert.stringToWstring("Testing2");
	LPWSTR value = convert.stringToLPWSTR("Testing");// 32-bit pointer to a string of 16-bit Unicode characters,
	


	// RegistryManager Testing
	rm::RegistryManager rManager;
	std::wstring checkRegistry = rManager.ReadRegistery(L"Hardware\\Description\\System\\CentralProcessor\\0", L"ProcessorNameString", REG_SZ);
	//rm.WriteRegistry("Hardware\\Description\\System\\CentralProcessor\\0", "NewValue", REG_SZ, "Content");

	
	
	return 0;
}


