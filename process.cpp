#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void criarProcesso() {
    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Falha ao criar o processo." << std::endl;
        return;
    }

    if (pid > 0) {
        std::cout << ">> Processo pai (PID: " << getpid() << ") criou o processo filho com PID: " << pid << std::endl;

        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            std::cout << ">> Finalizando processos!" << std::endl;
            std::cout << ">> Processo filho terminou com codigo: " << WEXITSTATUS(status) << std::endl;
        } else {
            std::cerr << ">> Processo filho nao terminou normalmente." << std::endl;
        }
    }
}