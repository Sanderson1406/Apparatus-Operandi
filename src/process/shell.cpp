#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include "auth/auth.h"
#include "file_system/file_system.h"
#include "process_manager.h"

int main() {
    std::string nome, senha;
    
    // Criação de usuário
    std::cout << "Digite o nome de usuário: ";
    std::cin >> nome;
    std::cout << "Digite a senha: ";
    std::cin >> senha;
    if (criar_usuario(nome, senha)) {
        std::cout << "Usuário criado com sucesso!\n";
    }

    // Autenticação de usuário
    std::cout << "Digite o nome de usuário para login: ";
    std::cin >> nome;
    std::cout << "Digite a senha para login: ";
    std::cin >> senha;
    if (autenticar_usuario(nome, senha)) {
        std::cout << "Usuário autenticado com sucesso!\n";
    } else {
        std::cout << "Falha na autenticação.\n";
    }

    return 0;
}
