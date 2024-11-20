# Apparatus-Operandi

## Funcionalidades

- **Criação de Usuário**: No primeiro acesso, se não houver usuários cadastrados, o sistema solicitará a criação de um novo usuário e senha.
- **Autenticação de Usuário**: Se houver usuários cadastrados, o sistema solicitará o nome de usuário e a senha para login.
- **Armazenamento Seguro**: As senhas são armazenadas em formato hash para maior segurança.
- **Persistência de Dados**: Os dados dos usuários são salvos em um arquivo (`users.txt`) para persistência entre execuções.
- **Listagem de Pastas**: O sistema pode listar os arquivos e diretórios presentes em um caminho especificado.
- **Criação de Arquivo `.txt`**: O sistema permite a criação de arquivos `.txt` com um nome variável especificado pelo usuário, em um caminho fixo.

## Estrutura do Código

- `hashPassword`: Função que gera um hash simples da senha.
- `createUser`: Função que cria um novo usuário e salva suas informações.
- `authenticateUser`: Função que autentica um usuário existente.
- `listarPastas`: Função que lista os arquivos e diretórios presentes em um caminho especificado.
- `criarArquivoTxt`: Função que cria um arquivo `.txt` com um nome especificado pelo usuário em um caminho fixo.
- `main`: Função principal que gerencia o fluxo do programa.

## Como Compilar e Executar

1. **Compilar o Código**:
   ```sh
   g++ -o AP main.cpp auth.cpp dir.cpp process.cpp

2. **Rodar Código**:
   ```sh
   .\AP