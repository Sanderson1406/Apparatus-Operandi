/*  ALUNO: Sanderson de Oliveira Machado
    RA: 22301449*/

#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <unordered_map>
#include <filesystem>
#include "utils.h"
#include <iostream>
#include <sstream>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

namespace fs = std::filesystem;

void clearTerminal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

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
        return;
    }
    std::string comando = tokens[0];
    if (tokens.size() > 1) {
        comando += " " + tokens[1];
        tokens.erase(tokens.begin(), tokens.begin() + 2);
    } else {
        tokens.erase(tokens.begin());
    }

    if (commandMap.find(comando) != commandMap.end()) {
        commandMap.at(comando)(tokens);
    } else {
        std::cout << ">> Comando não reconhecido. Digite <ajuda> " << std::endl;
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
        std::cout << ">> Nenhum usuario cadastrado. Crie um novo usuario." << std::endl;
        criarProcesso();
        username = createUser(users);
        atualizarDiretorioUser(username, caminho1);
    } else {
        auto [authenticated, authUsername] = authenticateUser(users);
        if (!authenticated) {
            std::cout << ">>>>>>>> A autenticacao falhou. Programa sera encerrado." << std::endl;
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
        std::cout << ">>>> Faça login para acessar. Digite <login>" << std::endl;
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
        if (!args.empty()){
            listarSubdiretorio(caminho1, args);
        } else {
            listarPastas(caminho1);
        }
    };
    commandMap["criar arquivo"] = [&caminho1](std::vector<std::string> args) {
        criarProcesso();
        if (args.size() >= 2) {
            std::vector<std::string> pathArgs = {args[0]};
            std::vector<std::string> fileArgs = {args[1]};
            pathArgs.insert(pathArgs.end(), fileArgs.begin(), fileArgs.end());
            criarArquivoTxtDir2(caminho1, pathArgs);
        } else {
            std::cout << ">>>> Nome do diretório ou arquivo não especificado." << std::endl;
        }
    };
    commandMap["apagar arquivo"] = [&caminho1](std::vector<std::string> args) {
        criarProcesso();
        if (args.size() >= 2) {
            std::vector<std::string> pathArgs = {args[0]};
            std::vector<std::string> fileArgs = {args[1]};
            pathArgs.insert(pathArgs.end(), fileArgs.begin(), fileArgs.end());
            apagarArquivoDir2(caminho1, pathArgs);
        } else {
            std::cout << ">>>> Nome do diretório ou arquivo não especificado." << std::endl;
        }
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
            if (args.size() > 1 && args.back() == "--force") {
                args.pop_back();
                apagarDiretorioForce(caminho1, args);
            } else {
                apagarDiretorio(caminho1, args);
            }
        } else {
            std::cout << ">>>> Nome do diretório não especificado." << std::endl;
        }
    };
    commandMap["limpar"] = [](std::vector<std::string> args) { clearTerminal(); };
    commandMap["sair"] = [](std::vector<std::string> args) { exit(0);};


    while (true) {
        std::string command = getComando();

        if (command == "sair")
        {
            exit(0);
        }else if (command == "ajuda") {
            std::cout << ":::: criar user" << std::endl;
            std::cout << ":::: login" << std::endl;
            std::cout << ":::: listar " << std::endl;
            std::cout << ":::: listar <nome do diretorio>" << std::endl;
            std::cout << ":::: criar arquivo <Nome do arquivo com .txt>" << std::endl;
            std::cout << ":::: criar arquivo <Nome do diretorio> <Nome do arquivo com .txt>" << std::endl;
            std::cout << ":::: apagar arquivo <Nome do arquivo com .txt>" << std::endl;
            std::cout << ":::: apagar arquivo <Nome do diretorio> <Nome do arquivo com .txt>" << std::endl;
            std::cout << ":::: criar diretorio <Nome do novo diretorio>" << std::endl;
            std::cout << ":::: apagar diretorio <Nome do diretorio>" << std::endl;
            std::cout << ":::: apagar diretorio <Nome do diretorio> --force" << std::endl;
            std::cout << ":::: limpar" << std::endl;
            std::cout << ":::: sair" << std::endl;
        }  else {
            executarComando(commandMap, command);
        }
    }

    return 0;
}