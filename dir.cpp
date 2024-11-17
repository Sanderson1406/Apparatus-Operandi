#include "utils.h"
#include <windows.h>
#include <iostream>
#include <fstream> 

void listarPastas(const std::string& dir) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((dir + "//*").c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Erro ao abrir o diretorio." << std::endl;
        return;
    }

    do {
        // Processo de exibição dos arquivos/diretórios
        std::cout << findFileData.cFileName << std::endl;
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

void criarArquivoTxt(const std::string& caminho,const std::string& nome) {
    std::string all = caminho + "/" + nome + ".txt";
    std::ofstream outFile(all);
}