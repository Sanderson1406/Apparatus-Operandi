#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>
#include "utils.h"

void criarProcesso(const std::string& comando) {
    pid_t pid = fork(); 

    if (pid < 0) {
        std::cerr << "Falha ao criar o processo." << std::endl;
        return;
    }

    if (pid == 0) {
        // Código do processo filho
        char* args[] = {(char*)"/bin/bash", (char*)"-c", (char*)comando.c_str(), nullptr};
        if (execvp(args[0], args) < 0) {
            std::cerr << "Falha ao executar o comando." << std::endl;
            exit(EXIT_FAILURE);
        }
    } else {
        // Código do processo pai
        std::cout << ">> Processo criado com PID: " << pid << std::endl;

        // Aguarda o processo filho terminar
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            std::cout << ">> Processo terminou com código: " << WEXITSTATUS(status) << std::endl;
        } else {
            std::cerr << ">> Processo não terminou normalmente." << std::endl;
        }
    }
}