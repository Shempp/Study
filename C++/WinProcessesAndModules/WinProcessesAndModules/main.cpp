#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <conio.h>

VOID PrintSystemError(const CHAR* additionalMsg)
{
	auto errMsgID = GetLastError();
	if (!errMsgID)
		return;

	LPSTR messageBuffer = nullptr;
	auto size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errMsgID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

	std::string resultMsg(messageBuffer, size);

	// Display the message
	std::cout << additionalMsg << ": " << resultMsg << std::endl;

	// Free the buffer
	LocalFree(messageBuffer);
}

BOOL SetPrivilege(HANDLE hToken, LPCTSTR lpszPrivilege, BOOL bEnablePrivilege)
{
	TOKEN_PRIVILEGES tp{};
	LUID luid{};

	// Convert a program name (lpszPrivilege) to a LUID
    if (!LookupPrivilegeValue(NULL, lpszPrivilege, &luid))        
    {
		PrintSystemError("LookupPrivilegeValue");
        return FALSE; 
    }
 
    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    if (bEnablePrivilege)
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    else
        tp.Privileges[0].Attributes = 0;
 
	// Enable the privilege or disable all privileges
    if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), (PTOKEN_PRIVILEGES)NULL, (PDWORD)NULL)) 
    { 
		PrintSystemError("AdjustTokenPrivileges");
		return FALSE; 
    } 
 
    return TRUE;
}

VOID ListProcessModules(CONST DWORD dwProcessId)
{
	MODULEENTRY32 me{};
	auto hSnapshotModules = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE|TH32CS_SNAPMODULE32, dwProcessId);

	// Take a snapshot of all modules in the specified process.
	if (hSnapshotModules == INVALID_HANDLE_VALUE) 
	{
		if (GetLastError() == ERROR_ACCESS_DENIED)
		{
			PrintSystemError("CreateToolhelp32Snapshot WARNING: This process is most likely a system process and it's impossible to obtain its modules");
			goto cleanup;
		}
		else 
		{
			PrintSystemError("CreateToolhelp32Snapshot");
			goto cleanup;
		}
	}

	// Set the size of the structure before using it
	me.dwSize = sizeof(MODULEENTRY32);

	// Retrieve information about the first module
	if (!Module32First(hSnapshotModules, &me))
	{
		PrintSystemError("Module32First");
		goto cleanup;
	}

	// Now walk the module list of the process,
	// and display information about each module
	std::wcout << "Full path: " << me.szExePath << std::endl;
	std::cout << "Modules: ";
	do 
	{
		std::wcout << me.szModule << ";";
	} while(Module32Next(hSnapshotModules, &me));

cleanup:
	if (hSnapshotModules && hSnapshotModules != INVALID_HANDLE_VALUE)
		CloseHandle(hSnapshotModules);
}

VOID ListProcesses()
{
	auto countOfProcesses = 0;
	PROCESSENTRY32 pe32{};
	HANDLE hProcess{};
	HANDLE hToken{};
	// Take a snapshot of all running processes (TH32CS_SNAPPROCESS)
	auto hSnapshotProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
																					
	if (hSnapshotProcess == INVALID_HANDLE_VALUE)										
	{
		PrintSystemError("CreateToolhelp32Snapshot with flag TH32CS_SNAPPROCESS");
		goto cleanup;
	}

	// Fill in the size of the structure before using it
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// Retrieve information about the first process
	if (!Process32First(hSnapshotProcess, &pe32))		
	{
		PrintSystemError("Process32First");
		goto cleanup;
	}

	// All process privileges are stored in a token, it is also called an access token 
	// Having received it, you can add/remove privileges from the process/thread
	// Get token for current process (TOKEN_QUERY - get token and TOKEN_ADJUST_PRIVILEGES - enable or disable the privileges in an access token)
	if (!OpenProcessToken (GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
	{
		PrintSystemError("OpenProcessToken");
		goto cleanup;
	}

	// Enabling a privilege in an access token allows the process to perform system-level actions that it could not previously
	// Set privelege for current process (SE_DEBUG_NAME)
	if (!SetPrivilege(hToken, SE_DEBUG_NAME, TRUE))
	{
		// PrintSystemError inside function
		goto cleanup;
	}

	/*
	// Get handle of process
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pe32.th32ProcessID);
	if (GetLastError())
	{
		if (GetLastError() != 87 && pe32.th32ProcessID == 0)
		{
			PrintSystemError("OpenProcess");
			goto cleanup;
		}
	}	
	*/

	// After retrieving the first process in the list, you can traverse the process list for subsequent entries
	do 
	{
		std::cout << "\n\nCounter of process: " << countOfProcesses << std::endl;
		std::cout << "ID:" << pe32.th32ProcessID;
		std::wcout << "\tProcess name:" << pe32.szExeFile;
		std::cout << "\tNumber of threads:" << pe32.cntThreads << std::endl;

		// List the modules and threads associated with this process
		ListProcessModules(pe32.th32ProcessID);

		_getch();
		countOfProcesses++;
	} while(Process32Next(hSnapshotProcess, &pe32));

cleanup:
	if (hProcess && hProcess != INVALID_HANDLE_VALUE)
		CloseHandle(hProcess);
	if (hSnapshotProcess && hSnapshotProcess != INVALID_HANDLE_VALUE)
		CloseHandle(hSnapshotProcess);
}

INT main()
{
	// For display correctly in the Windows console
	SetConsoleOutputCP(1251);
	ListProcesses();

	ExitProcess(EXIT_SUCCESS);
}