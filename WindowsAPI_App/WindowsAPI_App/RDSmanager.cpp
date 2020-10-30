#include "RDSmanager.h"

// Create a session conext for the remote computer. Set the 
// Domain, User, and Password member to NULL to specify
// the current user.
EVT_HANDLE RDSmanager::ConnectToRemote(LPWSTR lpwszRemote)
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
void RDSmanager::EnumProviders(EVT_HANDLE hRemote)
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
BOOL RDSmanager::IsRemote(DWORD pid, DWORD* exitTag, DWORD* lastErrorCode) {
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
BOOL RDSmanager::GetProcessList()
{
    HANDLE hProcessSnap;
    HANDLE hProcess;
    PROCESSENTRY32 pe32;
    DWORD dwPriorityClass;

    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        printError((TCHAR *)TEXT("CreateToolhelp32Snapshot (of processes)"));
        return(FALSE);
    }

    // Set the size of the structure before using it.
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Retrieve information about the first process,
    // and exit if unsuccessful
    if (!Process32First(hProcessSnap, &pe32))
    {
        printError((TCHAR*)TEXT("Process32First")); // show cause of failure
        CloseHandle(hProcessSnap);          // clean the snapshot object
        return(FALSE);
    }

    // Now walk the snapshot of processes, and
    // display information about each process in turn
    do
    {
        _tprintf(TEXT("\n\n====================================================="));
        _tprintf(TEXT("\nPROCESS NAME:  %s"), pe32.szExeFile);
        _tprintf(TEXT("\n-------------------------------------------------------"));
        // Retrieve the priority class.
        dwPriorityClass = 0;
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
        if (hProcess == NULL)
            printError((TCHAR*)TEXT("OpenProcess"));
        else
        {
            dwPriorityClass = GetPriorityClass(hProcess);
            if (!dwPriorityClass)
                printError((TCHAR*)TEXT("GetPriorityClass"));
            CloseHandle(hProcess);
        }

        _tprintf(TEXT("\n  Process ID        = 0x%08X"), pe32.th32ProcessID);
        _tprintf(TEXT("\n  Thread count      = %d"), pe32.cntThreads);
        _tprintf(TEXT("\n  Parent process ID = 0x%08X"), pe32.th32ParentProcessID);
        _tprintf(TEXT("\n  Priority base     = %d"), pe32.pcPriClassBase);
        if (dwPriorityClass)
            _tprintf(TEXT("\n  Priority class    = %d"), dwPriorityClass);

        // List the modules and threads associated with this process
        ListProcessModules(pe32.th32ProcessID);
        ListProcessThreads(pe32.th32ProcessID);

    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return(TRUE);
}
BOOL RDSmanager::ListProcessModules(DWORD dwPID)
{
    return 0;
}
BOOL RDSmanager::ListProcessThreads(DWORD dwOwnerPID)
{
    return 0;
}
void RDSmanager::printError(TCHAR* msg)
{
    DWORD eNum;
    TCHAR sysMsg[256];
    TCHAR* p;

    eNum = GetLastError();
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, eNum,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
        sysMsg, 256, NULL);

    // Trim the end of the line and terminate it with a null
    p = sysMsg;
    while ((*p > 31) || (*p == 9))
        ++p;
    do { *p-- = 0; } while ((p >= sysMsg) &&
        ((*p == '.') || (*p < 33)));

    // Display the message
    _tprintf(TEXT("\n  WARNING: %s failed with error %d (%s)"), msg, eNum, sysMsg);

}

void RDSmanager::RemoteDesktopTesting()
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