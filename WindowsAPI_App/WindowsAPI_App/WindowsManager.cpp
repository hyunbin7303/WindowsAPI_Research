#include "WindowsManager.h"



DWORD WindowsManager::find_process(const char* targetExeName, DWORD targetSession)
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
        if (_stricmp((const char*)pe32.szExeFile, targetExeName) == 0) {
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
