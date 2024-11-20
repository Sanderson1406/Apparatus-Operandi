#include "utils.h"
#include <windows.h>
#include <iostream>

void criarProcesso(const std::string& comando) 
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcess(NULL,
        const_cast<LPSTR>(comando.c_str()),
        NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
        std::cerr << "Falha ao criar o processo. Erro: " << GetLastError() << std::endl;
        return;
    }

    std::cout << ">> Processo criado com PID: " << pi.dwProcessId << std::endl;

    size_t memorySize = 1024 * 1024; 
    char* buffer = new char[memorySize];

    std::cout << ">> Memoria alocada: " << memorySize << " bytes" << std::endl;

    WaitForSingleObject(pi.hProcess, INFINITE);

    delete[] buffer;

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}
