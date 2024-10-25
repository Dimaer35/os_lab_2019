#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <seed> <array_size>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1) {
        // Ошибка при форке
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Дочерний процесс
        printf("Child process: executing sequential_min_max with seed = %s and array_size = %s...\n", argv[1], argv[2]);
        char *args[] = {"./sequential_min_max", argv[1], argv[2], NULL};  // Передаем аргументы seed и array_size
        execv(args[0], args);
        
        // Если execv завершился неудачей
        perror("execv failed");
        exit(EXIT_FAILURE);
    } else {
        // Родительский процесс
        int status;
        waitpid(pid, &status, 0);  // Ожидаем завершения дочернего процесса
        printf("Parent process: sequential_min_max has finished.\n");
    }

    return 0;
}
