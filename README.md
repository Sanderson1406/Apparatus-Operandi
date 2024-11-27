### Atualização do README

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

## Comandos Disponíveis

### Comando: `criar user`

- **Descrição**: Cria um novo usuário.
- **Exemplo**:
```sh
   >>>> criar user
   >>>> Digite o nome de usuario: sanderson
   >>>> Digite a senha: 
```

### Comando: `login`

- **Descrição**: Realiza login com um usuário existente.
- **Exemplo**:
```sh
   >>>> login
   >>>> Digite o nome de usuario: sanderson
   >>>> Digite a senha:
```

### Comando: `listar dir1`

- **Descrição**: Lista os arquivos e diretórios presentes no diretório do usuário.
- **Exemplo**:
```sh
   >>>> listar dir1
   arquivo1.txt
   pasta1/
```

### Comando: `criar arquivo dir1`

- **Descrição**: Cria um arquivo `.txt` no diretório do usuário.
- **Exemplo**:
```sh
   >>>> criar arquivo dir1
   >>>> Digite o nome do arquivo: novo_arquivo
```

### Comando: `criar arquivo`

- **Descrição**: Cria um arquivo `.txt` no diretório `directories`.
- **Exemplo**:
```sh
   >>>> criar arquivo
   >>>> Digite o nome do arquivo: arquivo_global
```

### Comando: `apagar arquivo dir1`

- **Descrição**: Remove um arquivo no diretório do usuário.
- **Exemplo**:
```sh
   >>>> apagar arquivo dir1
   >>>> Digite o nome do arquivo: arquivo1.txt
```

### Comando: `apagar arquivo`

- **Descrição**: Remove um arquivo no diretório `directories`.
- **Exemplo**:
```sh
   >>>> apagar arquivo
   >>>> Digite o nome do arquivo: arquivo_global.txt
```

### Comando: `criar diretorio dir1`

- **Descrição**: Cria um novo diretório no diretório do usuário.
- **Exemplo**:
```sh
   >>>> criar diretorio dir1
   >>>> Digite o nome do diretório: nova_pasta
```

### Comando: `apagar diretorio dir1`

- **Descrição**: Remove um diretório no diretório do usuário.
- **Exemplo**:
```sh
   >>>> apagar diretorio dir1
   >>>> Digite o nome do diretório: pasta1
```

### Comando: `apagar diretorio dir1 --force`

- **Descrição**: Remove um diretório e seu conteúdo no diretório do usuário.
- **Exemplo**:
```sh
   >>>> apagar diretorio dir1 --force
   >>>> Digite o nome do diretório: pasta1
```

### Comando: `limpar`

- **Descrição**: Limpa o terminal.
- **Exemplo**:
```sh
   >>>> limpar
```

## Configuração do Ambiente no Fedora

1. **Atualizar o Sistema**:

```sh
sudo dnf update
```

1. **Instalar Dependências**:

```sh
sudo dnf install gcc-c++ openssl-devel
```

1. **Clonar o Repositório**:

```sh
git clone <https://github.com/Sanderson1406/Apparatus-Operandi/tree/Fedora-Vesion>
cd Apparatus-Operandi
```

1. **Compilar o Código**:

```sh
rm *.o
g++ -std=c++17 -c main.cpp auth.cpp dir.cpp process.cpp
g++ -o AP main.o auth.o dir.o process.o -lssl -lcrypto
```

1. **Executar o Programa**:

```sh
./AP
```