/*  ALUNO: Sanderson de Oliveira Machado
    RA: 22301449*/

#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <unordered_map>
#include "utils.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// Função para limpar o terminal
void clearTerminal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    clearTerminal();

    std::unordered_map<std::string, std::pair<std::string, std::string>> users;

    std::ifstream file("users.txt");
    std::string username, salt, hashedPassword;
    while (file >> username >> salt >> hashedPassword) {
        users[username] = {salt, hashedPassword};
    }
    file.close();

    if (users.empty()) {
        std::cout << ">> Nenhum usuario cadastrado. Crie um novo usuario." << std::endl;
        createUser(users);
    } else if (!authenticateUser(users)) {
        std::cout << ">>>>>> A autenticacao falhou. Programa sera encerrado." << std::endl;
        return 1;
    }

    std::unordered_map<std::string, std::function<void()>> commandMap;
    std::string caminho1 = "C:../Apparatus-Operandi/directories";
    std::string caminho2 = "C:../Apparatus-Operandi";

    commandMap["criar"] = [&users]() { createUser(users); };
    commandMap["login"] = [&users]() { authenticateUser(users); };
    commandMap["listar dir1"] = [caminho1]() {
        std::string comando = "dir";
        criarProcesso(comando);
        listarPastas(caminho1);
    };
    commandMap["criar arquivo dir1"] = [caminho1]() {
        std::string comando = "mkdir";
        criarProcesso(comando);
        std::string nometxt;
        std::cout << ">>>> Digite o nome do arquivo: ";
        std::cin >> nometxt;
        criarArquivoTxt(caminho1, nometxt);
    };
    commandMap["criar arquivo"] = [caminho2]() {
        std::string comando = "mkdir";
        criarProcesso(comando);
        std::string nometxt;
        std::cout << ">>>> Digite o nome do arquivo: ";
        std::cin >> nometxt;
        criarArquivoTxt(caminho2, nometxt);
    };
    commandMap["limpar"] = []() { clearTerminal(); };

    while (true) {
        std::string command;
        std::cout << ">>>> ";
        std::getline(std::cin, command);

        if (command == "sair") {
            break;
        } else if (commandMap.find(command) != commandMap.end()) {
            commandMap[command]();
        } else {
            std::cout << ">> Comando nao reconhecido: " << command << std::endl;
        }
    }

    return 0;
}
