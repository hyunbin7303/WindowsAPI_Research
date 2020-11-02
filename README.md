# WindowsAPI_Research
My own research project related to Windows API.


## Windows Remote API investigation.

### Use the Windows Event Log API.
- To accessdata on the local pc or on a remote pc.
- Call the EvtOpenSession fucntion to create a remote session context. 



source : https://docs.microsoft.com/en-us/windows/win32/wes/accessing-remote-computers


Try this one : 
https://github.com/FreeRDP/FreeRDP/tree/master/client/Windows
https://docs.microsoft.com/en-us/windows/win32/api/_rdp/



https://docs.microsoft.com/en-us/windows/win32/termserv/detecting-the-terminal-services-environment



Good for understanding Remote Desktop Services : https://docs.microsoft.com/en-us/windows/win32/termserv/connection-sequence



The RDS api enables me to enumerate and manage remote desktop session Host servers, client sessions, and processes.
https://docs.microsoft.com/en-us/windows/win32/termserv/terminal-services-administration






### Others..

#### Command u can use.

* View remote desktop servicesTermServiceProcess PID
```
tasklist /svc | find "Ter"
```

* View the port used by the remote desktop
```
netstat -ano | find "[Number from Above]"
```

* View Registry.
Start button -> enter registry.
* Find HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\TerminalServer\Wds\rdpwd\tds\tcp
*  Find HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\TerminalServer\WinStaions\RDP-Tcp

