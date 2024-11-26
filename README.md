# Apparatus-Operandi

## Funcionalidades

- **Criação de Usuário**: No primeiro acesso, se não houver usuários cadastrados, o sistema solicitará a criação de um novo usuário e senha.
- **Autenticação de Usuário**: Se houver usuários cadastrados, o sistema solicitará o nome de usuário e a senha para login.
- **Armazenamento Seguro**: As senhas são armazenadas em formato hash para maior segurança.
- **Persistência de Dados**: Os dados dos usuários são salvos em um arquivo (`users.txt`) para persistência entre execuções.
- **Listagem de Pastas**: O sistema pode listar os arquivos e diretórios presentes em um caminho especificado.
- **Criação de Arquivo `.txt`**: O sistema permite a criação de arquivos `.txt` com um nome variável especificado pelo usuário, em um caminho fixo.
- **Criação de Diretório**: O sistema permite a criação de novos diretórios em um caminho especificado.
- **Remoção de Diretório**: O sistema permite a remoção de diretórios vazios em um caminho especificado.
- **Remoção de Arquivo**: O sistema permite a remoção de arquivos em um caminho especificado.

## Estrutura do Código

- `hashPassword`: Função que gera um hash simples da senha.
- `createUser`: Função que cria um novo usuário e salva suas informações.
- `authenticateUser`: Função que autentica um usuário existente.
- `listarPastas`: Função que lista os arquivos e diretórios presentes em um caminho especificado.
- `criarArquivoTxt`: Função que cria um arquivo `.txt` com um nome especificado pelo usuário em um caminho fixo.
- `criarDiretorio`: Função que cria um novo diretório em um caminho especificado.
- `apagarDiretorio`: Função que remove um diretório vazio em um caminho especificado.
- `apagarArquivo`: Função que remove um arquivo em um caminho especificado.
- `main`: Função principal que gerencia o fluxo do programa.

## Como Compilar e Executar

1. **Limpar Resquiscios**:
   ```sh
   rm *.o

2. **Compilando**:
   ```sh
   g++ -std=c++17 -c main.cpp auth.cpp dir.cpp process.cpp
   g++ -o AP main.o auth.o dir.o process.o -lssl -lcrypto

3. **Rodar Código**:
   ```sh
   ./AP