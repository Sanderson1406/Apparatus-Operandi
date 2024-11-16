#include "dir.h"
#include <windows.h>
#include <iostream>

void listarPastas(const std::string& dir) {
    // Declarações de variáveis
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((dir + "\\*").c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Erro ao abrir o diretório." << std::endl;
        return;
    }

    do {
        // Processo de exibição dos arquivos/diretórios
        std::cout << findFileData.cFileName << std::endl;
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}
