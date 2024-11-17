#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <unordered_map>

std::string hashPassword(const std::string& password, const std::string& salt);
std::string generateSalt();
std::string getPassword();
void createUser(std::unordered_map<std::string, std::pair<std::string, std::string>>& users);
bool authenticateUser(const std::unordered_map<std::string, std::pair<std::string, std::string>>& users);
void listarPastas(const std::string& dir);
void criarArquivoTxt(const std::string& caminho, const std::string& nome);
void criarProcesso(const std::string& comando);

#endif