#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include "utils.h"

namespace fs = std::filesystem;

void listarPastas(const std::string& dir) {
    try {
        for (const auto& entry : fs::directory_iterator(dir)) {
            if (fs::is_directory(entry.status())) {
                std::cout << entry.path().filename().string() << std::endl;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro ao listar pastas: " << e.what() << std::endl;
    }
}

void criarArquivoTxt(const std::string& caminho, const std::string& nome) {
    try {
        std::string fullPath = fs::path(caminho) / (nome + ".txt");
        std::ofstream outFile(fullPath);
        if (!outFile) {
            throw std::ios_base::failure("Nao foi possivel criar o arquivo.");
        }
        std::cout << "Arquivo criado: " << fullPath << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao criar o arquivo: " << e.what() << std::endl;
    }
}

void apagarArquivo(const std::string& caminho, const std::string& nome) {
    try {
        std::string fullPath = fs::path(caminho) / (nome + ".txt");
        if (fs::remove(fullPath)) {
            std::cout << "Arquivo " << nome << " apagado com sucesso!" << std::endl;
        } else {
            std::cerr << "Arquivo nao encontrado: " << fullPath << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro ao apagar o arquivo: " << e.what() << std::endl;
    }
}

void criarDiretorio(const std::string& caminho, const std::string& nome) {
    try {
        std::string fullPath = fs::path(caminho) / nome;
        if (fs::create_directory(fullPath)) {
            std::cout << "Diretorio " << nome << " criado com sucesso!" << std::endl;
        } else {
            std::cerr << "Erro: Diretorio ja existe ou não pode ser criado." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro ao criar o diretorio: " << e.what() << std::endl;
    }
}

void createDirectories() {
    if (!fs::exists("directories")) {
        fs::create_directories("directories");
    }
}

void apagarDiretorio(const std::string& caminho, const std::string& nome) {
    if (fs::exists(caminho) && fs::is_directory(caminho)) {
        if (fs::is_empty(caminho)) {
            fs::remove(caminho);
            std::cout << ">>>> Diretorio removido: " << caminho << std::endl;
        } else {
            std::cerr << ">>>> Diretorio nao esta vazio: " << caminho << std::endl;
        }
    } else {
        std::cerr << ">>>> Diretorio nao encontrado: " << caminho << std::endl;
    }
}

void apagarDiretorioForce(const std::string& caminho, const std::string& nome) {
    try {
        std::string fullPath = fs::path(caminho) / nome;
        if (fs::remove_all(fullPath) > 0) {
            std::cout << "Diretorio apagado com sucesso!" + fullPath << std::endl;
        } else {
            std::cerr << "Erro: Diretorio nao encontrado ou nao pode ser apagado." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro ao apagar o diretorio: " << e.what() << std::endl;
    }
}