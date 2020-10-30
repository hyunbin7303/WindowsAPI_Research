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

	void RemoteDesktopTesting()
	{
        EVT_HANDLE hRemote = NULL;
        LPWSTR pwsComputerName = Converter::ConvertString("Checking Remote computer");
        //LPCSTR is defined as const char*, not const wchar_t*. Use LPCWSTR, or LPCTSTR with UNICODE defined.
        // Enumerate the registered providers on the local computer.
        wprintf(L"Registered providers on the local computer\n\n");

        RDSmanager rdsManager;
        rdsManager.EnumProviders(hRemote);
        //EnumProviders(hRemote);
        hRemote = rdsManager.ConnectToRemote(pwsComputerName);
        if (NULL == hRemote)
        {
            wprintf(L"Failed to connect to remote computer. Error code is %d.\n", GetLastError());
            goto cleanup;
        }
        // Enumerate the registered providers on the remote computer.To access a remote computer, the remote computer must enable 
        // Remote Event Log Management as an exception in the firewall; otherwise, the remote call fails with RPC_S_SERVER_UNAVAILABLE.
        wprintf(L"\n\nRegistered providers on the remote computer\n\n");
        rdsManager.EnumProviders(hRemote);
    cleanup:
        if (hRemote)
            EvtClose(hRemote);
	}
};


#endif // !RDS_M



