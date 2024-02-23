#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <PID>" << std::endl;
        return 1;
    }

    int pid = std::atoi(argv[1]);

    std::ofstream logfile("audit.log", std::ios::out | std::ios::app);
    if (!logfile.is_open()) {
        std::cerr << "Failed to open logfile." << std::endl;
        return 1;
    }

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        return 1;

        close(pipefd[1]);

        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            perror("dup2");
            return 1;
        }

        execlp("strace", "strace", "-p", argv[1], "-f", "-e", "trace=all", NULL);
        perror("execlp");
        return 1;
    } else {

        close(pipefd[0]);

        int status;
        waitpid(child_pid, &status, 0);

        char buffer[4096];
        ssize_t nread;
        while ((nread = read(pipefd[1], buffer, sizeof(buffer))) > 0) {
            std::cout.write(buffer, nread);
            logfile.write(buffer, nread);
        }

        if (WIFEXITED(status)) {
            logfile << "Child process exited with status: " << WEXITSTATUS(status) << std::endl;
            return WEXITSTATUS(status);
        } else {
            logfile << "Child process exited abnormally." << std::endl;
            return 1;
        }
    }

    return 0;
}
