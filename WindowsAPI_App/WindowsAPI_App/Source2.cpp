#ifdef UNICODE
#define SetWindowText  SetWindowTextW
#else
#define SetWindowText  SetWindowTextA
#endif 


#pragma comment(lib, "wevtapi.lib")

#include "RDSmanager.h"
#include "Converter.h"





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
        //printError(TEXT)
    }
    //https://cpp.hotexamples.com/examples/-/-/ProcessIdToSessionId/cpp-processidtosessionid-function-examples.html
    // Please review this.
    // COpy some information from here! https://github.com/cginternals/cppfs
    //https://stackoverflow.com/questions/5866129/rsa-encryption-problem-size-of-payload-data RSA encryption

    return TRUE;

}


void testingSnapshot()
{
    std::vector<DWORD> pids;
    std::wstring targetProcessName = L"notepad.exe";
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // getting all processes

    PROCESSENTRY32W entry;
    entry.dwSize = sizeof entry;
    if (!Process32FirstW(snap, &entry)) {
        return;
    }

    do {
        if (std::wstring(entry.szExeFile) == targetProcessName)
        {
            pids.emplace_back(entry.th32ProcessID);
        }

    } while (Process32NextW(snap, &entry));

    for (int i(0); pids.size(); ++i)
    {
        std::cout << pids[i] << std::endl;
    }

}


int main(void)
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


