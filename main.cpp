#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "auth.h"
#include "dir.h"

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

    // Carregar usuários do arquivo
    std::ifstream file("users.txt");
    std::string username, salt, hashedPassword;
    while (file >> username >> salt >> hashedPassword) {
        users[username] = {salt, hashedPassword};
    }
    file.close();

    if (users.empty()) {
        std::cout << "Nenhum usuário cadastrado. Crie um novo usuário." << std::endl;
        createUser(users);
    } else if (!authenticateUser(users)) {
        std::cout << "A autenticação falhou. Programa será encerrado." << std::endl;
        return 1;
    }

    std::string command;
    while (true) {
        std::cout << "> ";
        std::cin >> command;

        if (command == "sair") {
            break;
        } else if (command == "criar") {
            createUser(users);
        } else if (command == "login") {
            authenticateUser(users);
        } else if(command == "listar") {
            listarPastas("C:/Users/sande/DevOper/Code - Faculdade/4 Semestre/Sistemas Operacionais/Apparatus-Operandi/directories");
        } else {
            std::cout << "Comando não reconhecido: " << command << std::endl;
        } 
    }

    return 0;
}