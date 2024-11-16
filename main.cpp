#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <iomanip>
#include <conio.h>
#include <random>

// Função para gerar um hash simples da senha com salt
std::string hashPassword(const std::string& password, const std::string& salt) {
    std::stringstream ss;
    std::string saltedPassword = salt + password;
    for (char c : saltedPassword) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)c;
    }
    return ss.str();
}

// Função para gerar um salt aleatório
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

// Função para ocultar a senha ao digitá-la
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

// Função para criar um novo usuário
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

// Função para autenticar um usuário
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

// Função principal que gerencia o shell
int main() {
    std::unordered_map<std::string, std::pair<std::string, std::string>> users;

    // Carregar usuários do arquivo
    std::ifstream file("users.txt");
    std::string username, salt, hashedPassword;
    while (file >> username >> salt >> hashedPassword) {
        users[username] = {salt, hashedPassword};
    }
    file.close();

    if (users.empty()) {
        std::cout << "Nenhum usuario cadastrado. Crie um novo usuario." << std::endl;
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
        } else {
            std::cout << "Comando nao reconhecido: " << command << std::endl;
        }
    }

    return 0;
}
