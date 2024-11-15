#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <iomanip>

// Função para gerar um hash simples da senha
std::string hashPassword(const std::string& password) {
    std::stringstream ss;
    for (char c : password) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)c;
    }
    return ss.str();
}

// Função para criar um novo usuário
void createUser(std::unordered_map<std::string, std::string>& users) {
    std::string username, password;
    std::cout << "Digite o nome de usuario: ";
    std::cin >> username;
    std::cout << "Digite a senha: ";
    std::cin >> password;

    std::string hashedPassword = hashPassword(password);

    users[username] = hashedPassword;

    // Salvar usuários em um arquivo
    std::ofstream file("users.txt");
    for (const auto& user : users) {
        file << user.first << " " << user.second << std::endl;
    }
    file.close();
}

// Função para autenticar um usuário
bool authenticateUser(const std::unordered_map<std::string, std::string>& users) {
    std::string username, password;
    std::cout << "Digite o nome de usuario: ";
    std::cin >> username;
    std::cout << "Digite a senha: ";
    std::cin >> password;

    auto it = users.find(username);
    if (it != users.end()) {
        std::string hashedPassword = hashPassword(password);

        if (hashedPassword == it->second) {
            std::cout << "Login bem-sucedido!" << std::endl;
            return true;
        }
    }
    std::cout << "Nome de usuario ou senha incorretos." << std::endl;
    return false;
}

int main() {
    std::unordered_map<std::string, std::string> users;

    // Carregar usuários do arquivo
    std::ifstream file("users.txt");
    std::string username, hashedPassword;
    while (file >> username >> hashedPassword) {
        users[username] = hashedPassword;
    }
    file.close();

    if (users.empty()) {
        std::cout << "Nenhum usuário cadastrado. Crie um novo usuário." << std::endl;
        createUser(users);
    } else {
        authenticateUser(users);
    }

    return 0;
}
