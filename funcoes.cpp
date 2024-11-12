// funcoes.cpp
#include <iostream>
#include <fstream>
#include <cstdio>
#include <sys/stat.h>
#include <dirent.h>
#include <filesystem>
#include "funcoes.h"

void minhaFuncao() {
    std::cout << "Olá do outro arquivo!" << std::endl;
}

void listar(const std::string& dir) {
    DIR* dp;
    struct dirent* entry;

    if (dir.empty()) {
        dp = opendir(".");
    } else {
        dp = opendir(dir.c_str());
    }

    if (dp == nullptr) {
        std::cerr << "Erro ao abrir diretório: " << dir << std::endl;
        return;
    }

    while ((entry = readdir(dp)) != nullptr) {
        std::cout << entry->d_name << std::endl;
    }

    closedir(dp);
}

void criarArquivo(const std::string& path) {
    std::ofstream file(path);
    if (!file) {
        std::cerr << "Erro ao criar arquivo: " << path << std::endl;
        return;
    }
    file << "Conteúdo aleatório" << std::endl;
    file.close();
}

void apagarArquivo(const std::string& path) {
    if (remove(path.c_str()) != 0) {
        std::cerr << "Erro ao apagar arquivo: " << path << std::endl;
    }
}

void criarDiretorio(const std::string& path) {
    if (mkdir(path.c_str(), 0777) != 0) {
        std::cerr << "Erro ao criar diretório: " << path << std::endl;
    }
}

void apagarDiretorio(const std::string& path, bool force) {
    if (force) {
        std::filesystem::remove_all(path);
    } else {
        if (rmdir(path.c_str()) != 0) {
            std::cerr << "Erro ao apagar diretório: " << path << std::endl;
        }
    }
}
