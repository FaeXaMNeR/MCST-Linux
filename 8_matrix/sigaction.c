#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#define SIZE 1000

// Реализация через sigaction()

int i = 0;
int j = 0;

void handler(int sig) {
    printf("\nТекущая итератор строки: %d, текущий итератор столбца: %d\n", i, j);
    signal(SIGINT, SIG_DFL);
}

int main() {
    int **matrix1 = malloc(SIZE * sizeof(int *));
    int **matrix2 = malloc(SIZE * sizeof(int *));
    int **res = malloc(SIZE * sizeof(int *));

    for (int a = 0; a < SIZE; a++) {
        matrix1[a] = malloc(SIZE * sizeof(int));
        matrix2[a] = malloc(SIZE * sizeof(int));
        res[a] = malloc(SIZE * sizeof(int));
    }

    // заполнение массивов единичками
    for (int a = 0; a < SIZE; a++) {
        for (int b = 0; b < SIZE; b++) {
            matrix1[a][b] = 1;
            matrix2[a][b] = 1;
        }
    }

    // изменение реакции SIGINT
    signal(SIGINT, handler);

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            res[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                res[i][j] += matrix1[i][k] * matrix2[k][j];
            }
            sleep(1);
        }
    }

    for (int a = 0; a < SIZE; a++) {
        free(matrix1[a]);
        free(matrix2[a]);
        free(res[a]);
    }
    free(matrix1);
    free(matrix2);
    free(res);

    return 0;
}