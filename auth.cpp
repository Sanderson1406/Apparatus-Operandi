#include "auth.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <conio.h>
#include <random>

std::string hashPassword(const std::string& password, const std::string& salt) {
    std::stringstream ss;
    std::string saltedPassword = salt + password;
    for (char c : saltedPassword) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)c;
    }
    return ss.str();
}

std::string generateSalt() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    std::stringstream ss;
    for (int i = 0; i < 16; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << dis(gen);
    }
    return ss.str();
}

std::string getPassword() {
    std::string password;
    char ch;
    while ((ch = _getch()) != 13) {
        if (ch == 8) { 
                if (!password.empty()) {
                std::cout << "\b \b";
                password.pop_back();
            }
        } else {
            password += ch;
            std::cout << '*';
        }
    }
    std::cout << std::endl;
    return password;
}

void createUser(std::unordered_map<std::string, std::pair<std::string, std::string>>& users) {
    std::string username;
    std::cout << "Digite o nome de usuario: ";
    std::cin >> username;
    std::cout << "Digite a senha: ";
    std::string password = getPassword();

    std::string salt = generateSalt();
    std::string hashedPassword = hashPassword(password, salt);

    users[username] = {salt, hashedPassword};

    // Salvar usuários em um arquivo
    std::ofstream file("users.txt");
    for (const auto& user : users) {
        file << user.first << " " << user.second.first << " " << user.second.second << std::endl;
    }
    file.close();
}

bool authenticateUser(const std::unordered_map<std::string, std::pair<std::string, std::string>>& users) {
    std::string username;
    std::cout << "Digite o nome de usuario: ";
    std::cin >> username;
    std::cout << "Digite a senha: ";
    std::string password = getPassword();

    auto it = users.find(username);
    if (it != users.end()) {
        std::string salt = it->second.first;
        std::string hashedPassword = hashPassword(password, salt);

        if (hashedPassword == it->second.second) {
            std::cout << "Login bem-sucedido!" << std::endl;
            return true;
        }
    }
    std::cout << "Nome de usuario ou senha incorretos." << std::endl;
    return false;
}
