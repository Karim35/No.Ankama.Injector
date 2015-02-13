// No.Ankama.Injector.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <Windows.h>
#include <detours.h>

#pragma comment(lib, "detours.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_SHOW;

	if(!DetourCreateProcessWithDllEx(TEXT("Dofus.exe"), 
                                        NULL, NULL, NULL, TRUE, 
                                        CREATE_DEFAULT_ERROR_MODE | CREATE_SUSPENDED,
                                        NULL, NULL, &si, &pi, 
                                        "No.Ankama.dll", NULL))
        MessageBox(0, TEXT("dll injection failed"), 0, 0);
    else
        MessageBox(0, TEXT("dll injection success"), 0, 0);

    ResumeThread(pi.hThread);

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(&si);
    CloseHandle(&pi);

    return EXIT_SUCCESS;
}

