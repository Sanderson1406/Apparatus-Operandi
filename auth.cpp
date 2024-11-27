#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <random>
#include <openssl/sha.h>
#include <nlohmann/json.hpp>
#include <termios.h>
#include <unistd.h>
#include "utils.h"

using json = nlohmann::json;
namespace fs = std::filesystem;

std::string hashPassword(const std::string& password, const std::string& salt) {
    std::string saltedPassword = salt + password;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)saltedPassword.c_str(), saltedPassword.size(), hash);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
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
    struct termios oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ECHO | ICANON); 
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while (read(STDIN_FILENO, &ch, 1) && ch != '\n') {
        if (ch == 127 || ch == 8) { 
            if (!password.empty()) {
                std::cout << "\b \b";
                password.pop_back();
            }
        } else {
            password += ch;
            std::cout << '*';
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    std::cout << std::endl;
    return password;
}

void saveUsersToFile(const std::unordered_map<std::string, std::pair<std::string, std::string>>& users) {
    json j;
    for (const auto& user : users) {
        j[user.first] = {{"salt", user.second.first}, {"hashedPassword", user.second.second}};
    }
    std::ofstream file("users.json");
    file << j.dump(4);
}

std::unordered_map<std::string, std::pair<std::string, std::string>> loadUsersFromFile() {
    std::unordered_map<std::string, std::pair<std::string, std::string>> users;
    std::ifstream file("users.json");
    if (file) {
        json j;
        file >> j;
        for (auto& [username, data] : j.items()) {
            users[username] = {data["salt"], data["hashedPassword"]};
        }
    }
    return users;
}

std::pair<bool, std::string> authenticateUser(const std::unordered_map<std::string, std::pair<std::string, std::string>>& users) {
    std::string username;
    std::cout << ">>>> Digite o nome de usuario: ";
    std::cin >> username;
    std::cout << ">>>> Digite a senha: ";
    std::cout.flush();  
    std::string password = getPassword();

    auto it = users.find(username);
    if (it != users.end()) {
        std::string salt = it->second.first;
        std::string hashedPassword = hashPassword(password, salt);

        if (hashedPassword == it->second.second) {
            std::cout << ">>>> Login bem-sucedido!" << std::endl;
            return {true, username};
        }
    }
    std::cout << ">>>> Nome de usuario ou senha incorretos." << std::endl;
    return {false, ""};
}

std::string createUser(std::unordered_map<std::string, std::pair<std::string, std::string>>& users) {
    std::string username;
    std::cout << ">>>> Digite o nome de usuario: ";
    std::cin >> username;

    std::cout << ">>>> Digite a senha: ";
    std::cout.flush();  
    std::string password = getPassword();

    std::string salt = generateSalt();
    std::string hashedPassword = hashPassword(password, salt);

    users[username] = {salt, hashedPassword};
    saveUsersToFile(users);

    fs::path userDir = "directories/" + username;
    if (!fs::exists(userDir)) {
        fs::create_directory(userDir);
        std::cout << ">>>> Diretorio para o usuario '" << username << "' criado.\n";
    } 

    return username;
}

void atualizarDiretorioUser(const std::string& username, std::string& caminho1) {
    caminho1 = "./directories/" + username;
}