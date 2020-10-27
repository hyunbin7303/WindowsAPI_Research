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
std::wstring s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}
void testing()
{
    size_t   i;
    char* pMBBuffer = (char*)malloc(BUFFER_SIZE);
    const wchar_t* pWCBuffer = L"Hello, world.";
    printf("Convert wide-character string:\n");
    //Converts a sequence of wide characters to a corresponding sequence of multibyte characters.
    wcstombs_s(&i, pMBBuffer, (size_t)BUFFER_SIZE,
        pWCBuffer, (size_t)BUFFER_SIZE);

    // Output
    printf("   Characters converted: %u\n", i);
    printf("    Multibyte character: %s\n\n",
        pMBBuffer);

    // Free multibyte character buffer
    if (pMBBuffer)
    {
        free(pMBBuffer);
    }
}

void Testing2()
{

}

// Needs to test asap.
static DWORD find_process(const char* targetExeName, DWORD targetSession)
{
    PROCESSENTRY32 pe32 = { 0 };

    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap == INVALID_HANDLE_VALUE) {
        return 0;
    }


    //ProcessEntry32 : Describes an entry from a list of the processes residing in the system address space when a snapshot was taken.
    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(hSnap, &pe32)) {
        CloseHandle(hSnap);
        return 0;
    }

    do
    {
        if (_stricmp((const char *)pe32.szExeFile, targetExeName) == 0) {
            DWORD sessId = 0;
            if (ProcessIdToSessionId(pe32.th32ProcessID, &sessId)
                && sessId == targetSession)
            {
                /* found target process */
                CloseHandle(hSnap);
                return pe32.th32ProcessID;
            }
        }
    } while (Process32Next(hSnap, &pe32));

    CloseHandle(hSnap);
    return 0;
}

static BOOL IsRemote(DWORD pid, DWORD* exitTag, DWORD* lastErrorCode) {
    DWORD sessionId;
    if (FALSE == ProcessIdToSessionId(pid, &sessionId)) {
        *exitTag = 1;
        *lastErrorCode = GetLastError();
        return FALSE;
    }

    OSVERSIONINFOW osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOW));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOW);

    GetVersionExW(&osvi);
    if (osvi.dwMajorVersion > 5) {
        // The case of Vista/Server 2008: 0 and 1 means local, greater than 1 - remote.
        return (0 != sessionId) && (1 != sessionId);
    }
    else if ((osvi.dwMajorVersion == 5) && (osvi.dwMinorVersion >= 1)) {
        // The case of XP/Server 2003: 0 is local, another value means remote.
        return (0 != sessionId);
    }
    else {
        *exitTag = 2;
        return FALSE;
    }
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
    // Enumerate the registered providers on the remote computer.To access a remote computer, the remote computer must enable 
    // Remote Event Log Management as an exception in the firewall; otherwise, the remote call fails with RPC_S_SERVER_UNAVAILABLE.
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