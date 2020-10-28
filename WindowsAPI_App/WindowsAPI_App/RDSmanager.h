//#include <processthreadsapi.h>
#ifndef RDS_M
#define RDS_M


#define BUFFER_SIZE 100
#include <windows.h>
#include <stdio.h>
#include <winevt.h>
#include <tlhelp32.h>
#include <iostream>
class RDSmanager
{
private:

	//ProcessIdToSessionId()
public:
	EVT_HANDLE ConnectToRemote(LPWSTR lpwszRemote);
	void EnumProviders(EVT_HANDLE hRemote);

};


#endif // !RDS_M



