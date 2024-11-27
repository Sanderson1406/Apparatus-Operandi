/*  ALUNO: Sanderson de Oliveira Machado
    RA: 22301449*/

#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <unordered_map>
#include <filesystem>
#include "utils.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

namespace fs = std::filesystem;

// Função para limpar o terminal
void clearTerminal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    std::cout << "Bem-vindo(a) ao Apparatus Operandi" << std::endl;

    createDirectories();
    clearTerminal();

    std::unordered_map<std::string, std::pair<std::string, std::string>> users = loadUsersFromFile();
    std::string username; // Variável para armazenar o nome do usuário

    if (users.empty()) {
        std::cout << ">> Nenhum usuário cadastrado. Crie um novo usuário." << std::endl;
        criarProcesso();
        createUser(users);
    } else {
        auto [authenticated, authUsername] = authenticateUser(users);
        if (!authenticated) {
            std::cout << ">>>>>>>> A autenticação falhou. Programa será encerrado." << std::endl;
            return 1;
        } else {
            username = authUsername;
            std::string caminho1;
            atualizarDiretorioUser(username, caminho1);
        }
    }

    std::string caminho1;
    atualizarDiretorioUser(username, caminho1);
    std::string caminho2 = "./directories";

    std::unordered_map<std::string, std::function<void()>> commandMap;

    commandMap["criar user"] = [&users]() { createUser(users); };
    commandMap["login"] = [&users, &username, &caminho1]() { 
        auto [authenticated, authUsername] = authenticateUser(users);
        if (authenticated) { 
            username = authUsername;
            atualizarDiretorioUser(username, caminho1);
        }
    };
    commandMap["listar dir1"] = [&caminho1]() {
        criarProcesso();
        for (const auto& entry : fs::directory_iterator(caminho1)) {
            std::cout << entry.path().filename().string() << std::endl;
        }
    };
    commandMap["criar arquivo dir1"] = [&caminho1]() {
        criarProcesso();
        std::string nometxt;
        std::cout << ">>>> Digite o nome do arquivo: ";
        std::cin >> nometxt;
        criarArquivoTxt(caminho1, nometxt);
    };
    commandMap["criar arquivo"] = [&caminho2]() {
        criarProcesso();
        std::string nometxt;
        std::cout << ">>>> Digite o nome do arquivo: ";
        std::cin >> nometxt;
        criarArquivoTxt(caminho2, nometxt);
    };
    commandMap["apagar arquivo dir1"] = [&caminho1]() {
        criarProcesso();
        std::string nometxt;
        std::cout << ">>>> Digite o nome do arquivo: ";
        std::cin >> nometxt;
        apagarArquivo(caminho1, nometxt);
    };
    commandMap["apagar arquivo"] = [&caminho2]() {
        criarProcesso();
        std::string nometxt;
        std::cout << ">>>> Digite o nome do arquivo: ";
        std::cin >> nometxt;
        if (nometxt == "users") {
            std::cout << "Você não tem permissão para deletar esse arquivo" << std::endl;
            return;
        }
        apagarArquivo(caminho2, nometxt);
    };
    commandMap["criar diretorio dir1"] = [&caminho1]() {
        criarProcesso();
        std::string nometxt;
        std::cout << ">>>> Digite o nome do diretório: ";
        std::cin >> nometxt;
        criarDiretorio(caminho1, nometxt);
    };
    commandMap["apagar diretorio dir1"] = [&caminho1]() {
        criarProcesso();
        std::string nometxt;
        std::cout << ">>>> Digite o nome do diretório: ";
        std::cin >> nometxt;
        apagarDiretorio(caminho1, nometxt);
    };
    commandMap["apagar diretorio dir1 --force"] = [&caminho1] () {
        criarProcesso();
        std::string nometxt;
        std::cout << ">>>> Digite o nome do diretório: ";
        std::cin >> nometxt;
        apagarDiretorioForce(caminho1, nometxt);
    };
    commandMap["limpar"] = []() { clearTerminal(); };

    // Loop principal
    while (true) {
        std::string command;
        std::cout << ">>>> ";
        std::getline(std::cin, command);

        if (command == "sair") {
            break;
        } else if (commandMap.find(command) != commandMap.end()) {
            commandMap[command]();
        } else {
            std::cout << ">> Comando não reconhecido: " << command << std::endl;
        }
    }

    return 0;
}
