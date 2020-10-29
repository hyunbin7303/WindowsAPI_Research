#ifndef _WINDOWS_M
#define _WINDOWS_M
#define BUFFER_SIZE 100
#include <windows.h>
#include <stdio.h>
#include <winevt.h>
#include <tlhelp32.h>
#include <iostream>

class WindowsManager
{
public:
	static DWORD find_process(const char* targetExeName, DWORD targetSession);
	//Testing method for Creating processes.
	void MakeProcess();

};
#endif // !_WINDOWS_M



