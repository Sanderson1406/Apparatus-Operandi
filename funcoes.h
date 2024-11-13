#ifndef FUNCOES_H
#define FUNCOES_H

void listar(const std::string& dir);
void criarArquivo(const std::string& path);
void apagarArquivo(const std::string& path);
void criarDiretorio(const std::string& path);
void apagarDiretorio(const std::string& path, bool force);

// Adicione a declaração da função iniciarShell
void iniciarShell();

#endif
