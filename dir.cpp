#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "utils.h"

namespace fs = std::filesystem;

void listarPastas(const std::string& caminho) {
    try {
        fs::path fullPath = fs::path(caminho);
        for (const auto& entry : fs::directory_iterator(fullPath)) {
            if (fs::is_directory(entry.status())) {
                std::cout << "::" << entry.path().filename().string() << std::endl;
            } else if (entry.path().extension() == ".txt") {
                std::cout << "::" << entry.path().filename().string() << std::endl;
            } 
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro ao listar pasta: " << e.what() << std::endl;
    }
}

void criarArquivoTxtDir2(const std::string& caminho1, const std::vector<std::string>& args) {
    try {
        fs::path fullPath = fs::path(caminho1);
        for (const auto& part : args) {
            fullPath /= part;
        }
        std::ofstream outFile(fullPath);
        if (!outFile) {
            throw std::ios_base::failure("Nao foi possivel criar o arquivo.");
        }
        std::cout << "Arquivo criado no subdiretorio: " << fullPath.string() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao criar o arquivo no subdiretorio: " << e.what() << std::endl;
    }
}

void listarSubdiretorio(const std::string& caminho, const std::vector<std::string>& nomeSubdiretorio) {
    try {
        fs::path fullPath = fs::path(caminho);
        for (const auto& part : nomeSubdiretorio) {
            fullPath /= part;
        }
        if (!fs::exists(fullPath)) {
            std::cerr << "Erro: O subdiretorio " << fullPath.string() << " nao existe." << std::endl;
            return;
        }
        for (const auto& entry : fs::directory_iterator(fullPath)) {
            if (fs::is_directory(entry.status())) {
                std::cout << "::" << entry.path().filename().string() << std::endl;
            } else if (entry.path().extension() == ".txt") {
                std::cout << "::" << entry.path().filename().string() << std::endl;
            } 
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro ao listar o subdiretorio: " << e.what() << std::endl;
    }
}


void apagarArquivoDir2(const std::string& caminho1, const std::vector<std::string>& args) {
    try {
        fs::path fullPath = fs::path(caminho1);
        for (const auto& part : args) {
            fullPath /= part;
        }
        if (fs::remove(fullPath)) {
            std::cout << "Arquivo no subdiretorio " << fullPath.string() << " apagado com sucesso!" << std::endl;
        } else {
            std::cerr << "Arquivo nao encontrado no subdiretorio: " << fullPath.string() << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro ao apagar o arquivo no subdiretorio: " << e.what() << std::endl;
    }
}

void criarArquivoTxt(const std::string& caminho, const std::vector<std::string>& args) {
    try {
        fs::path fullPath = fs::path(caminho);
        for (const auto& part : args) {
            fullPath /= part;
        }
        std::ofstream outFile(fullPath);
        if (!outFile) {
            throw std::ios_base::failure("Nao foi possivel criar o arquivo.");
        }
        std::cout << "Arquivo criado: " << fullPath.string() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao criar o arquivo: " << e.what() << std::endl;
    }
}

void apagarArquivo(const std::string& caminho, const std::vector<std::string>& args) {
    try {
        fs::path fullPath = fs::path(caminho);
        for (const auto& part : args) {
            fullPath /= part;
        }
        if (fs::remove(fullPath)) {
            std::cout << "Arquivo " << fullPath.string() << " apagado com sucesso!" << std::endl;
        } else {
            std::cerr << "Arquivo nao encontrado: " << fullPath.string() << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro ao apagar o arquivo: " << e.what() << std::endl;
    }
}

void criarDiretorio(const std::string& caminho, const std::vector<std::string>& args) {
    try {
        fs::path fullPath = fs::path(caminho);
        for (const auto& part : args) {
            fullPath /= part;
        }
        if (fs::create_directory(fullPath)) {
            std::cout << "Diretorio " << fullPath.string() << " criado com sucesso!" << std::endl;
        } else {
            std::cerr << "Erro: Diretorio ja existe ou nao pode ser criado." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro ao criar o diretorio: " << e.what() << std::endl;
    }
}

void apagarDiretorio(const std::string& caminho, const std::vector<std::string>& args) {
    try {
        fs::path fullPath = fs::path(caminho);
        for (const auto& part : args) {
            fullPath /= part;
        }
        if (fs::exists(fullPath) && fs::is_directory(fullPath)) {
            if (fs::is_empty(fullPath)) {
                fs::remove(fullPath);
                std::cout << ">>>> Diretorio removido: " << fullPath.string() << std::endl;
            } else {
                std::cerr << ">>>> Diretorio nao esta vazio" << std::endl;
            }
        } else {
            std::cerr << ">>>> Diretorio nao encontrado: " << fullPath.string() << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro ao apagar o diretorio: " << e.what() << std::endl;
    }
}

void apagarDiretorioForce(const std::string& caminho, std::vector<std::string> args) {
    try {
        if (!args.empty() && args.back() == "--force") {
            args.pop_back(); 
        }
        fs::path fullPath = fs::path(caminho);
        for (const auto& part : args) {
            fullPath /= part;
        }
        if (fs::remove_all(fullPath) > 0) {
            std::cout << "Diretorio apagado com sucesso: " << fullPath.string() << std::endl;
        } else {
            std::cerr << "Erro: Diretorio nao encontrado ou nao pode ser apagado." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro ao apagar o diretorio: " << e.what() << std::endl;
    }
}

void createDirectories() {
    if (!fs::exists("directories")) {
        fs::create_directories("directories");
    }
}