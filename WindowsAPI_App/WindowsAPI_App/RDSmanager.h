//#include <processthreadsapi.h>


#ifndef RD_H
#define RD_H
#ifdef UNICODE
#define SetWindowText  SetWindowTextW
#else
#define SetWindowText  SetWindowTextA
#endif 
#define BUFFER_SIZE 100
#include <windows.h>
#include <stdio.h>
#include <winevt.h>
#include <tlhelp32.h>
#include <iostream>
#include <windows.h>
#include <tchar.h>

#pragma warning(disable : 4996)
class RDSmanager
{

public:
	EVT_HANDLE ConnectToRemote(LPWSTR lpwszRemote);
	void EnumProviders(EVT_HANDLE hRemote);
	BOOL IsRemote(DWORD pid, DWORD* exitTag, DWORD* lastErrorCode);

	// ms website sources;
	//https://docs.microsoft.com/en-us/windows/win32/toolhelp/taking-a-snapshot-and-viewing-processes

	BOOL GetProcessList();
	BOOL ListProcessModules(DWORD dwPID);
	BOOL ListProcessThreads(DWORD dwOwnerPID);

	void printError(TCHAR* msg);

};


#endif // !RDS_M



