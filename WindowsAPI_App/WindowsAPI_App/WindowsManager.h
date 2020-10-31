#ifndef _WINDOWS_M
#define _WINDOWS_M
#define BUFFER_SIZE 100
#include <windows.h>
#include <stdio.h>
#include <winevt.h>
#include <tlhelp32.h>
#include <iostream>
#include <vector>

namespace wm
{
    class WindowsManager
    {
    public:
        static DWORD find_process(const char* targetExeName, DWORD targetSession);
        //Testing method for Creating processes.
        void MakeProcess();
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
        BOOL GetProcessId(LPCTSTR pProgExe, DWORD sessionId, DWORD* pPid)
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
            return TRUE;
        }
    };
}


#endif // !_WINDOWS_M



