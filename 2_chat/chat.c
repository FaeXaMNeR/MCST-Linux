#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/select.h>
#include <errno.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Использование: %s 1 или 2\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int role = atoi(argv[1]);
    if (role != 1 && role != 2) {
        fprintf(stderr, "Второй аргумент должен быть 1 или 2\n");
        exit(EXIT_FAILURE);
    }

    const char *fifo1 = "/tmp/chat1";
    const char *fifo2 = "/tmp/chat2";

    // Создание FIFO
    if (mkfifo(fifo1, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo fifo1");
        exit(EXIT_FAILURE);
    }
    if (mkfifo(fifo2, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo fifo2");
        exit(EXIT_FAILURE);
    }

    int write_fd, read_fd;

    if (role == 1) {
        if ((write_fd = open(fifo1, O_WRONLY)) == -1) {
            perror("Open fifo1 for writing");
            exit(EXIT_FAILURE);
        }
        if ((read_fd = open(fifo2, O_RDONLY)) == -1) {
            perror("Open fifo2 for reading");
            exit(EXIT_FAILURE);
        }
    } else {
        if ((read_fd = open(fifo1, O_RDONLY)) == -1) {
            perror("Open fifo1 for reading");
            exit(EXIT_FAILURE);
        }
        if ((write_fd = open(fifo2, O_WRONLY)) == -1) {
            perror("Open fifo2 for writing");
            exit(EXIT_FAILURE);
        }
    }

    printf("Собеседники подключены, общение началось (exit для завершения)\n");

    char buf[BUF_SIZE];
    fd_set readfds;

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);  // Ввод с клавиатуры
        FD_SET(read_fd, &readfds);      

        int max_fd = (STDIN_FILENO > read_fd) ? STDIN_FILENO : read_fd;
        if (select(max_fd + 1, &readfds, NULL, NULL, NULL) == -1) {
            perror("Select");
            exit(EXIT_FAILURE);
        }

        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            ssize_t bytes = read(STDIN_FILENO, buf, BUF_SIZE);
            if (bytes > 0) {
                if (write(write_fd, buf, bytes) == -1) {
                    perror("Pipe write");
                    exit(EXIT_FAILURE);
                }
                if (strncmp(buf, "exit\n", 5) == 0) {
                    printf("Чат завершен\n");
                    break;
                }
            }
        }

        // Обработка данных из канала
        if (FD_ISSET(read_fd, &readfds)) {
            ssize_t bytes = read(read_fd, buf, BUF_SIZE);
            if (bytes > 0) {
                printf("Получено сообщение:\n%.*s", (int)bytes, buf);
                if (strncmp(buf, "exit\n", 5) == 0) {
                    printf("Собеседник вышел, чат завершен\n");
                    break;
                }
            } else if (bytes == 0) {
                printf("Собеседник вышел, чат завершен\n");
                break;
            } else {
                perror("read from pipe");
                exit(EXIT_FAILURE);
            }
        }
    }

    close(write_fd);
    close(read_fd);

    unlink(fifo1);
    unlink(fifo2);

    return 0;
}