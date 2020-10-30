/* Things to Study tomorrow morning.
* https://github.com/microsoft/wil
* https://docs.microsoft.com/en-us/windows/win32/toolhelp/snapshots-of-the-system
* https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-openprocess
* https://docs.microsoft.com/en-us/windows/win32/toolhelp/taking-a-snapshot-and-viewing-processes
*/

#ifndef RD_H
#define RD_H
#ifdef UNICODE
#define SetWindowText  SetWindowTextW
#else
#define SetWindowText  SetWindowTextA
#endif 
#define BUFFER_SIZE 100
#pragma warning(disable : 4996)


#include "Converter.h"


#include <windows.h>
#include <stdio.h>
#include <winevt.h>
#include <tlhelp32.h>
#include <iostream>
#include <windows.h>
#include <tchar.h>


using namespace rds::converter;

class RDSmanager
{

public:
	EVT_HANDLE ConnectToRemote(LPWSTR lpwszRemote);
	void EnumProviders(EVT_HANDLE hRemote);
	BOOL IsRemote(DWORD pid, DWORD* exitTag, DWORD* lastErrorCode);
	// ms website sources; https://docs.microsoft.com/en-us/windows/win32/toolhelp/taking-a-snapshot-and-viewing-processes
	BOOL GetProcessList();
	BOOL ListProcessModules(DWORD dwPID);
	BOOL ListProcessThreads(DWORD dwOwnerPID);
	void printError(TCHAR* msg);

	void RemoteDesktopTesting();

};


#endif // !RDS_M



