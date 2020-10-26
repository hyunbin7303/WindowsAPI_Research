#ifdef UNICODE
#define SetWindowText  SetWindowTextW
#else
#define SetWindowText  SetWindowTextA
#endif 


#include <windows.h>
#include <stdio.h>
#include <winevt.h>
#include <iostream>
#pragma comment(lib, "wevtapi.lib")
//typedef wchar_t WCHAR;
EVT_HANDLE ConnectToRemote(LPWSTR lpwszRemote);
void EnumProviders(EVT_HANDLE hRemote);
LPWSTR ConvertString(const std::string& instr)
{
    // Assumes std::string is encoded in the current Windows ANSI codepage
    int bufferlen = ::MultiByteToWideChar(CP_ACP, 0, instr.c_str(), instr.size(), NULL, 0);
    if (bufferlen == 0)
    {
        return 0;
    }
    // Allocate new LPWSTR - must deallocate it later
    LPWSTR widestr = new WCHAR[bufferlen + 1];
    ::MultiByteToWideChar(CP_ACP, 0, instr.c_str(), instr.size(), widestr, bufferlen);
    // Ensure wide string is null terminated
    widestr[bufferlen] = 0;
    // Do something with widestr
    return widestr;
    //delete[] widestr;
}
void main(void)
{
    EVT_HANDLE hRemote = NULL;
    LPWSTR pwsComputerName = ConvertString("Checking Remote computer");
    //LPCSTR is defined as const char*, not const wchar_t*. Use LPCWSTR, or LPCTSTR with UNICODE defined.

    // Enumerate the registered providers on the local computer.
    wprintf(L"Registered providers on the local computer\n\n");
    EnumProviders(hRemote);

    hRemote = ConnectToRemote(pwsComputerName);
    if (NULL == hRemote)
    {
        wprintf(L"Failed to connect to remote computer. Error code is %d.\n", GetLastError());
        goto cleanup;
    }

    // Enumerate the registered providers on the remote computer.
    // To access a remote computer, the remote computer must enable 
    // Remote Event Log Management as an exception in the firewall;
    // otherwise, the remote call fails with RPC_S_SERVER_UNAVAILABLE.
    wprintf(L"\n\nRegistered providers on the remote computer\n\n");
    EnumProviders(hRemote);

cleanup:

    if (hRemote)
        EvtClose(hRemote);
}

// Create a session conext for the remote computer. Set the 
// Domain, User, and Password member to NULL to specify
// the current user.
EVT_HANDLE ConnectToRemote(LPWSTR lpwszRemote)
{
    EVT_HANDLE hRemote = NULL;
    EVT_RPC_LOGIN Credentials;

    RtlZeroMemory(&Credentials, sizeof(EVT_RPC_LOGIN));
    /*
    LPCWSTR is a pointer to a const string buffer. LPWSTR is a pointer to a non-const string buffer. 
    Just create a new array of wchar_t and copy the contents of the LPCWSTR to it and use it in the function taking a LPWSTR.
    */
    Credentials.Server = lpwszRemote;
    Credentials.Domain = NULL;
    Credentials.User = NULL;
    Credentials.Password = NULL;
    Credentials.Flags = EvtRpcLoginAuthNegotiate;

    // This call creates a remote session context; it does not actually
    // create a connection to the remote computer. The connection to
    // the remote computer happens when you use the context.
    hRemote = EvtOpenSession(EvtRpcLogin, &Credentials, 0, 0);

    SecureZeroMemory(&Credentials, sizeof(EVT_RPC_LOGIN));

    return hRemote;
}

// Enumerate the registered providers on the computer.
void EnumProviders(EVT_HANDLE hRemote)
{
    EVT_HANDLE hPublishers = NULL;
    WCHAR wszPublisherName[255 + 1];
    DWORD dwBufferUsed = 0;
    DWORD status = ERROR_SUCCESS;

    hPublishers = EvtOpenPublisherEnum(hRemote, 0);
    if (NULL == hPublishers)
    {
        wprintf(L"EvtOpenPublisherEnum failed with %d\n", GetLastError());
        goto cleanup;
    }

    while (true)
    {
        if (EvtNextPublisherId(hPublishers, sizeof(wszPublisherName) / sizeof(WCHAR), wszPublisherName, &dwBufferUsed))
        {
            wprintf(L"%s\n", wszPublisherName);
        }
        else
        {
            status = GetLastError();
            if (ERROR_NO_MORE_ITEMS == status)
            {
                break;
            }
            else
            {
                wprintf(L"EvtNextPublisherId failed with 0x%ud\n", GetLastError());
            }
        }
    }

cleanup:

    if (hPublishers)
        EvtClose(hPublishers);
}