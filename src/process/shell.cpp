#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string>
#include "auth/auth.h"
#include "file_system/file_system.h"
#include "process_manager.h"
#include "funcoes.h"

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
