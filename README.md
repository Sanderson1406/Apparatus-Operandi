# Apparatus-Operandi# Projeto de Autenticação de Usuário

Este projeto implementa um sistema simples de autenticação de usuário em C++. Ele permite a criação de novos usuários, armazenamento seguro de senhas e autenticação de usuários existentes.

## Funcionalidades

- **Criação de Usuário**: No primeiro acesso, se não houver usuários cadastrados, o sistema solicitará a criação de um novo usuário e senha.
- **Autenticação de Usuário**: Se houver usuários cadastrados, o sistema solicitará o nome de usuário e a senha para login.
- **Armazenamento Seguro**: As senhas são armazenadas em formato hash para maior segurança.
- **Persistência de Dados**: Os dados dos usuários são salvos em um arquivo (`users.txt`) para persistência entre execuções.

## Estrutura do Código

- `hashPassword`: Função que gera um hash simples da senha.
- `createUser`: Função que cria um novo usuário e salva suas informações.
- `authenticateUser`: Função que autentica um usuário existente.
- `main`: Função principal que gerencia o fluxo do programa.

## Como Compilar e Executar

1. **Compilar o Código**:
   ```sh
   g++ -o AP main.cpp

2. **Rodar Código**:
   ```sh
   .\AP