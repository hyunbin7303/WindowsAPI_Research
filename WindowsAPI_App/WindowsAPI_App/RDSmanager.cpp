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