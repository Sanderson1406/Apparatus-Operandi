#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <unordered_map>

std::string hashPassword(const std::string& password, const std::string& salt);
std::string generateSalt();
std::string getPassword();
std::string createUser(std::unordered_map<std::string, std::pair<std::string, std::string>>& users);
std::pair<bool, std::string> authenticateUser(const std::unordered_map<std::string, std::pair<std::string, std::string>>& users);
void saveUsersToFile(const std::unordered_map<std::string, std::pair<std::string, std::string>>& users) ;
std::unordered_map<std::string, std::pair<std::string, std::string>> loadUsersFromFile();
void atualizarDiretorioUser(const std::string& username, std::string& caminho);
void createDirectories();

void listarPastas(const std::string& dir);
void criarDiretorio(const std::string& caminho, const std::string& nome);
void apagarDiretorio(const std::string& caminho, const std::string& nome);
void criarArquivoTxt(const std::string& caminho, const std::string& nome);
void criarArquivoTxtDir2(const std::string& caminho, const std::string& nome, const std::string& dir2txt);
void apagarArquivo(const std::string& caminho, const std::string& nome);
void apagatArquivoTxtDir2(const std::string& caminho, const std::string& nome, const std::string& dir2txt) ;
void apagarDiretorioForce(const std::string& caminho, const std::string& nome);

void criarProcesso();

#endif