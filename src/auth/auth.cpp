#include "auth.h"
#include <iostream>
#include <fstream>
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>
#include <random>

// Função para gerar um salt aleatório
std::string gerar_salt() {
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 255);
    std::string salt = "";
    
    for (int i = 0; i < 16; ++i) {
        salt += static_cast<char>(dist(rd));
    }

    return salt;
}

// Função para gerar o hash SHA-512 de uma senha com salt
std::string gerar_hash(const std::string& senha, const std::string& salt) {
    std::string senha_com_salt = senha + salt;
    unsigned char hash[SHA512_DIGEST_LENGTH];
    SHA512_CTX sha512_ctx;
    SHA512_Init(&sha512_ctx);
    SHA512_Update(&sha512_ctx, senha_com_salt.c_str(), senha_com_salt.length());
    SHA512_Final(hash, &sha512_ctx);

    std::stringstream ss;
    for (int i = 0; i < SHA512_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    return ss.str();
}

// Função para criar um novo usuário
bool criar_usuario(const std::string& nome, const std::string& senha) {
    std::string salt = gerar_salt();
    std::string hash = gerar_hash(senha, salt);

    // Armazenando o nome do usuário, salt e hash no arquivo
    std::ofstream arquivo("data/users.dat", std::ios::app); // 'app' para adicionar ao arquivo
    if (!arquivo) {
        std::cerr << "Erro ao abrir o arquivo de usuários.\n";
        return false;
    }

    arquivo << nome << " " << salt << " " << hash << std::endl;
    arquivo.close();
    std::cout << "Usuário criado com sucesso.\n";
    return true;
}

// Função para autenticar um usuário
bool autenticar_usuario(const std::string& nome, const std::string& senha) {
    std::ifstream arquivo("data/users.dat");
    if (!arquivo) {
        std::cerr << "Erro ao abrir o arquivo de usuários.\n";
        return false;
    }

    std::string nome_arquivo, salt_arquivo, hash_arquivo;
    while (arquivo >> nome_arquivo >> salt_arquivo >> hash_arquivo) {
        if (nome_arquivo == nome) {
            std::string hash_tentativa = gerar_hash(senha, salt_arquivo);
            if (hash_tentativa == hash_arquivo) {
                std::cout << "Autenticação bem-sucedida.\n";
                arquivo.close();
                return true;
            } else {
                std::cout << "Senha incorreta.\n";
                arquivo.close();
                return false;
            }
        }
    }

    std::cout << "Usuário não encontrado.\n";
    arquivo.close();
    return false;
}
