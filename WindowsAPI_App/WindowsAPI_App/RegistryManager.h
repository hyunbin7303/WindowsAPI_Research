#ifndef REGISTRY_M_H
#define REGISTRY_M_H


#include <Windows.h>
#include <winreg.h>
#include <string>
class RegistryManager
{
    //BOOL setStringValueToReg(HKEY hRoot, const char * szSubKey, )

    std::wstring ReadRegistery(LPCTSTR subKey, LPCTSTR name, DWORD type)
    {
        HKEY key;
        TCHAR value[255];
        DWORD length = 255;
        RegOpenKey(HKEY_LOCAL_MACHINE, subKey, &key);
        RegQueryValueEx(key, name, NULL, &type, (LPBYTE)&value, &length);
        RegCloseKey(key);
        wprintf(value);
        return value;
    }


    void WriteRegistry(LPCTSTR subKey, LPCTSTR name, DWORD type, const char* value)
    {
        HKEY key;
        RegOpenKey(HKEY_LOCAL_MACHINE, subKey, &key);
        RegSetValueEx(key, name, 0, type, (LPBYTE)value, strlen(value) * sizeof(char));
        RegCloseKey(key);
    }// Plz don't use this for now.
    //registry_read("Hardware\\Description\\System\\CentralProcessor\\0", "ProcessorNameString", REG_SZ);
    //registry_write("Hardware\\Description\\System\\CentralProcessor\\0", "NewValue", REG_SZ, "Content");
};

#endif // !REGISTRY_M_H

