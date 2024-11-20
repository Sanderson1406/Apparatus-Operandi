#include "utils.h"
#include <windows.h>
#include <iostream>
#include <fstream> 

void listarPastas(const std::string& dir) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((dir + "//*").c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) 
    {
        std::cerr << "Erro ao abrir o diretorio." << std::endl;
        return;
    }

    do 
    {
        std::cout << findFileData.cFileName << std::endl;
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

void criarArquivoTxt(const std::string& caminho,const std::string& nome) {
    std::string all = caminho + "\\" + nome + ".txt";
    std::ofstream outFile(all);
}

void apagarArquivo(const std::string& caminho, const std::string& nome) {
    std::string all = caminho + "\\" + nome + ".txt";
    
    if (GetFileAttributes(all.c_str()) == INVALID_FILE_ATTRIBUTES) 
    {
        std::cerr << "Arquivo nao encontrado: " << all << std::endl;
        return;
    }

    if (DeleteFile(all.c_str()) == 0) 
    {
        DWORD erro = GetLastError();
        std::cerr << "Erro ao apagar o arquivo " << all << ". Codigo de erro: " << erro << std::endl;
        
        switch (erro) 
        {
            case ERROR_FILE_NOT_FOUND:
                std::cerr << "Erro: Arquivo nao encontrado." << std::endl;
                break;
            case ERROR_ACCESS_DENIED:
                std::cerr << "Erro: Acesso negado. Verifique se o arquivo esta aberto ou se voce tem permissoes necessarias." << std::endl;
                break;
            default:
                std::cerr << "Erro desconhecido." << std::endl;
                break;
        }
    } else 
    {
        std::cout << "Arquivo " << nome << " apagado com sucesso!" << std::endl;
    }
}

void criarDiretorio(const std::string& caminho, const std::string& nome) {
    std::string all = caminho + "\\" + nome;
    if (CreateDirectory(all.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) 
    {
        std::cout << "Diretorio " << nome << " criado com sucesso!" << std::endl;
    } else
    {
        std::cerr << "Erro ao criar o diretorio " << caminho << ". Codigo de erro: " << GetLastError() << std::endl;
    }
}

void apagarDiretorio(const std::string& caminho, const std::string& nome) {
    std::string all = caminho + "\\" + nome;
    if (RemoveDirectory(all.c_str())) {
        std::cout << "Diretorio " << nome << " apagado com sucesso!" << std::endl;
    } else {
        std::cerr << "Erro ao apagar o diretorio " << caminho << ". Codigo de erro: " << GetLastError() << std::endl;
    }
}