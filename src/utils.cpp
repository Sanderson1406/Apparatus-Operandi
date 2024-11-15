#include <iostream>
#include <fstream>
#include <cstdio>
#include <sys/stat.h>
#include <dirent.h>
#include <cstring>  // Para usar strcmp
#include "funcoes.h"
#include "auth/auth.h"
#include "file_system/file_system.h"
#include "process/process_manager.h"

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
    if (mkdir(path.c_str()) != 0) {  // Remove o segundo argumento `0777`
        std::cerr << "Erro ao criar diretório: " << path << std::endl;
    }
}

// Função para remover um diretório recursivamente
void removerDiretorioRecursivo(const std::string& path) {
    DIR* dir = opendir(path.c_str());
    if (dir == nullptr) return;

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        std::string fullPath = path + "/" + entry->d_name;
        if (entry->d_type == DT_DIR) {
            removerDiretorioRecursivo(fullPath);
            rmdir(fullPath.c_str());
        } else {
            remove(fullPath.c_str());
        }
    }
    closedir(dir);
    rmdir(path.c_str());
}

void apagarDiretorio(const std::string& path, bool force) {
    if (force) {
        removerDiretorioRecursivo(path);
    } else {
        if (rmdir(path.c_str()) != 0) {
            std::cerr << "Erro ao apagar diretório: " << path << std::endl;
        }
    }
}

// Funções do shell.cpp
void obterCredenciais(std::string &nome, std::string &senha) {
    std::cout << "Digite o nome de usuário: ";
    std::cin >> nome;
    std::cout << "Digite a senha: ";
    std::cin >> senha;
}

void executarShell() {
    std::string comando;
    while (true) {
        std::cout << "$ ";
        std::cin >> comando;

        if (comando == "listar") {
            std::string dir;
            std::cin >> dir;
            listar(dir);
        } else if (comando == "criarArquivo") {
            std::string path;
            std::cin >> path;
            criarArquivo(path);
        } else if (comando == "apagarArquivo") {
            std::string path;
            std::cin >> path;
            apagarArquivo(path);
        } else if (comando == "criarDiretorio") {
            std::string path;
            std::cin >> path;
            criarDiretorio(path);
        } else if (comando == "apagarDiretorio") {
            std::string path;
            std::cin >> path;
            apagarDiretorio(path, false);
        } else if (comando == "apagarDiretorio --force") {
            std::string path;
            std::cin >> path;
            apagarDiretorio(path, true);
        } else if (comando == "sair") {
            break;
        } else {
            std::cout << "Comando não reconhecido.\n";
        }
    }
}

void iniciarShell() {
    std::string nome, senha;

    // Criação de usuário
    obterCredenciais(nome, senha);
    if (criar_usuario(nome, senha)) {
        std::cout << "Usuário criado com sucesso!\n";
    }

    // Autenticação de usuário
    obterCredenciais(nome, senha);
    if (autenticar_usuario(nome, senha)) {
        std::cout << "Usuário autenticado com sucesso!\n";
        executarShell();
    } else {
        std::cout << "Falha na autenticação.\n";
    }
}
