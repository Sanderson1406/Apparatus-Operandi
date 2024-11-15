#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <iomanip>
#include <conio.h>

// Função para gerar um hash simples da senha
std::string hashPassword(const std::string& password) {
    std::stringstream ss;
    for (char c : password) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)c;
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
void createUser(std::unordered_map<std::string, std::string>& users) {
    std::string username;
    std::cout << "Digite o nome de usuario: ";
    std::cin >> username;
    std::cout << "Digite a senha: ";
    std::string password = getPassword();

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
    std::string username;
    std::cout << "Digite o nome de usuario: ";
    std::cin >> username;
    std::cout << "Digite a senha: ";
    std::string password = getPassword();

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

// Função principal que gerencia o shell
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
        std::cout << "Nenhum usuario cadastrado. Crie um novo usuario." << std::endl;
        createUser(users);
    } else if (!authenticateUser(users)) {
        std::cout << "A autenticacao falhou. Programa sera encerrado." << std::endl;
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
