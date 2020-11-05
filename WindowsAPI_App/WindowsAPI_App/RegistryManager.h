#ifndef REGISTRY_M_H
#define REGISTRY_M_H


#include <Windows.h>
#include <winreg.h>
#include <string>
#include <iostream>
#include <stdexcept>


namespace rm
{
	class RegistryManager
	{
		//BOOL setStringValueToReg(HKEY hRoot, const char * szSubKey, )
	public:
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


		void GetRegistryTest(const char* value)
		{
			HKEY key;
			DWORD data{};
			DWORD dataSize = sizeof(data);


			const DWORD flags = RRF_RT_REG_SZ;// Only read strings(REG_SZ)
			LONG retCode = ::RegGetValueW(key, nullptr, L"Connie", flags, nullptr, nullptr, &dataSize);
			if (retCode != ERROR_SUCCESS)
			{
				std::cout << "ERROR happen. " << std::endl;
			}
		}
	};

	class RegistryError : public std::runtime_error
	{
	public:
		RegistryError(const char* msg, LONG errorCode)
			: std::runtime_error{ msg }, m_errorCode{ errorCode }{}



		LONG ErrorCode() const noexcept
		{
			return m_errorCode;
		}
	private:
		LONG m_errorCode;


	};

}



#endif // !REGISTRY_M_H

