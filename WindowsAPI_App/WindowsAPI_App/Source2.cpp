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

BOOL GetProcessId(LPCTSTR pProgExe, DWORD sessionId, DWORD *pPid)
{
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        printError(TEXT)
    }
    //https://cpp.hotexamples.com/examples/-/-/ProcessIdToSessionId/cpp-processidtosessionid-function-examples.html
    // Please review this.
    // COpy some information from here! https://github.com/cginternals/cppfs
    //https://stackoverflow.com/questions/5866129/rsa-encryption-problem-size-of-payload-data RSA encryption

}
//std::string currentUserUid()
//{
//    DWORD sessId = 0;
//    ProcessIdToSessionId(GetCurrentProcessId(), &sessId);
//    return tfm::format("%d", sessId);
//}
// Needs to test asap.

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


