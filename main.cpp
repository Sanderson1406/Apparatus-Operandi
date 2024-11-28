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

#include <iostream>
#include <sstream>
#include <vector>

std::vector<std::string> splitString(const std::string& str) {
    std::istringstream iss(str);
    std::vector<std::string> result;
    std::string word;
    while (iss >> word) {
        result.push_back(word);
    }
    return result;
}

std::string getComando() {
    std::string command;
    std::cout << ">>>> ";
    std::getline(std::cin, command);
    return command;
}

void executarComando(const std::unordered_map<std::string, std::function<void(std::vector<std::string>)>>& commandMap, const std::string& command) {
    std::vector<std::string> tokens = splitString(command);
    if (tokens.empty()) {
        std::cout << ">> Comando não reconhecido: " << command << std::endl;
        return;
    }
    std::string comando = tokens[0] + (tokens.size() > 1 ? " " + tokens[1] : "");
    if (tokens.size() > 1) {
        tokens.erase(tokens.begin(), tokens.begin() + 2);
    } else {
        tokens.erase(tokens.begin());
    }

    std::cout << "Comando recebido: " << comando << std::endl;
    for (const auto& arg : tokens) {
        std::cout << "Argumento: " << arg << std::endl;
    }

    if (commandMap.find(comando) != commandMap.end()) {
        commandMap.at(comando)(tokens);
    } else {
        std::cout << ">> Comando não reconhecido: " << comando << std::endl;
    }
}

int main() {
    std::cout << "Bem-vindo(a) ao Apparatus Operandi" << std::endl;

    createDirectories();
    clearTerminal();

    std::unordered_map<std::string, std::pair<std::string, std::string>> users = loadUsersFromFile();
    std::string username;
    std::string caminho1;

    if (users.empty()) {
        std::cout << ">> Nenhum usuário cadastrado. Crie um novo usuário." << std::endl;
        criarProcesso();
        username = createUser(users);
        atualizarDiretorioUser(username, caminho1);
    } else {
        auto [authenticated, authUsername] = authenticateUser(users);
        if (!authenticated) {
            std::cout << ">>>>>>>> A autenticação falhou. Programa será encerrado." << std::endl;
            return 1;
        } else {
            username = authUsername;
            atualizarDiretorioUser(username, caminho1);
        }
    } 

    std::unordered_map<std::string, std::function<void(std::vector<std::string>)>> commandMap;

        commandMap["criar user"] = [&users, &username, &caminho1](std::vector<std::string> args) { 
        criarProcesso();
        createUser(users);
        std::cout << ":::::::::::: Faça login para acessar (Comando: login)" << std::endl;
        atualizarDiretorioUser(username, caminho1);
    };
    commandMap["login"] = [&users, &username, &caminho1](std::vector<std::string> args) { 
        criarProcesso();
        auto [authenticated, authUsername] = authenticateUser(users);
        if (authenticated) { 
            username = authUsername;
            atualizarDiretorioUser(username, caminho1);
        }
    };
    commandMap["listar"] = [&caminho1](std::vector<std::string> args) {
        criarProcesso();
        listarPastas(caminho1);
    };

    commandMap["criar arquivo"] = [&caminho1](std::vector<std::string> args) {
        criarProcesso();
        if (!args.empty()) {
            criarArquivoTxt(caminho1, args);
        } else {
            std::cout << ">>>> Nome do arquivo não especificado." << std::endl;
        }
    };

    commandMap["apagar arquivo"] = [&caminho1](std::vector<std::string> args) {
        criarProcesso();
        if (!args.empty()) {
            apagarArquivo(caminho1, args);
        } else {
            std::cout << ">>>> Nome do arquivo não especificado." << std::endl;
        }
    };

    commandMap["criar diretorio"] = [&caminho1](std::vector<std::string> args) {
        criarProcesso();
        if (!args.empty()) {
            criarDiretorio(caminho1, args);
        } else {
            std::cout << ">>>> Nome do diretório não especificado." << std::endl;
        }
    };

    commandMap["apagar diretorio"] = [&caminho1](std::vector<std::string> args) {
        criarProcesso();
        if (!args.empty()) {
            apagarDiretorio(caminho1, args);
        } else {
            std::cout << ">>>> Nome do diretório não especificado." << std::endl;
        }
    };

    commandMap["apagar diretorio --force"] = [&caminho1](std::vector<std::string> args) {
        criarProcesso();
        if (!args.empty()) {
            apagarDiretorioForce(caminho1, args);
        } else {
            std::cout << ">>>> Nome do diretório não especificado." << std::endl;
        }
    };

    commandMap["limpar"] = [](std::vector<std::string> args) { clearTerminal(); };

    while (true) {
        std::string command = getComando();

        if (command == "sair") {
            return 1;
        } else if (command == "ajuda") {
            std::cout << ":::: criar user" << std::endl;
            std::cout << ":::: login" << std::endl;
            std::cout << ":::: listar" << std::endl;
            std::cout << ":::: criar arquivo" << std::endl;
            std::cout << ":::: apagar arquivo" << std::endl;
            std::cout << ":::: criar diretorio" << std::endl;
            std::cout << ":::: apagar diretorio" << std::endl;
            std::cout << ":::: apagar diretorio --force" << std::endl;
            std::cout << ":::: limpar" << std::endl;
        } else {
            executarComando(commandMap, command);
        }
    }

    return 0;
}