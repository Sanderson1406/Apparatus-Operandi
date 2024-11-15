#ifndef UTILS_H
#define UTILS_H

void iniciarShell();
void listar(const std::string& dir);
void criarArquivo(const std::string& path);
void apagarArquivo(const std::string& path);
void criarDiretorio(const std::string& path);
void apagarDiretorio(const std::string& path, bool force);
void obterCredenciais(std::string &nome, std::string &senha);
void executarShell();
bool autenticar_usuario(const std::string& usuario, const std::string& senha);
bool criar_usuario(const std::string& nome, const std::string& senha);

#endif