#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Использование: %s <имя_файла>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Open error");
        exit(EXIT_FAILURE);
    }

    // Создание процесса
    pid_t pid = fork();
    if (pid == -1) {
        perror("Fork error");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Дочерний процесс
    if (pid == 0) {                                               // -rw-r--r--
        int child_fd = open("child.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (child_fd == -1) {
            perror("Open child error");
            close(fd);
            exit(EXIT_FAILURE);
        }

        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;

        while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
            if (write(child_fd, buffer, bytes_read) != bytes_read) {
                perror("Write child error");
                close(fd);
                close(child_fd);
                exit(EXIT_FAILURE);
            }
        }

        close(child_fd);
        close(fd);

        // Вывод файла
        child_fd = open("child.txt", O_RDONLY);
        if (child_fd == -1) {
            perror("Open child (out) error");
            exit(EXIT_FAILURE);
        }

        printf("Содержимое файла дочернего процесса:\n");
        while ((bytes_read = read(child_fd, buffer, BUFFER_SIZE)) > 0) {
            write(STDOUT_FILENO, buffer, bytes_read);
        }
        printf("\n");

        close(child_fd);
        exit(EXIT_SUCCESS);
        
    // Родительский процесс
    } else {                                                        // -rw-r--r--
        int parent_fd = open("parent.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (parent_fd == -1) {
            perror("Open parent error");
            close(fd);
            exit(EXIT_FAILURE);
        }

        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;

        while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
            if (write(parent_fd, buffer, bytes_read) != bytes_read) {
                perror("Write parent error");
                close(fd);
                close(parent_fd);
                exit(EXIT_FAILURE);
            }
        }

        close(parent_fd);
        close(fd);

        wait(NULL);

        parent_fd = open("parent.txt", O_RDONLY);
        if (parent_fd == -1) {
            perror("Open parent error");
            exit(EXIT_FAILURE);
        }

        printf("Содержимое:\n");
        while ((bytes_read = read(parent_fd, buffer, BUFFER_SIZE)) > 0) {
            write(STDOUT_FILENO, buffer, bytes_read);
        }
        printf("\n");

        close(parent_fd);
    }

    return 0;
}
