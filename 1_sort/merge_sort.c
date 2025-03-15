#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// будет использоваться сортировка слиянием

// структура для передачи данных в поток
typedef struct thread_data {
    int *array;
    int left;
    int right;
} thread_data_t;

void merge(int *arr, int left, int mid, int right) {
    int size1 = mid - left + 1;
    int size2 = right - mid;

    int left_array[size1];
    int right_array[size2];

    for (int i = 0; i < size1; i++) left_array[i] = arr[left + i];
    for (int i = 0; i < size2; i++) right_array[i] = arr[mid + 1 + i];

    int i = 0, j = 0;
    int k = left;

    // слияние
    while (i < size1 && j < size2) {
        if (left_array[i] <= right_array[j]) {
            arr[k] = left_array[i];
            i++;
        } else {
            arr[k] = right_array[j];
            j++;
        }
        k++;
    }

    // заполнение остатков
    while (i < size1) {
        arr[k] = left_array[i];
        i++;
        k++;
    }

    while (j < size2) {
        arr[k] = right_array[j];
        j++;
        k++;
    }
}

// функция, которая будет работать в несколько потоков
void *merge_sort(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    int left = data->left;
    int right = data->right;

    if (left < right) {
        int mid = (right + left) / 2;

        // новые потоки будут создаваться для сортировки правой и левой части
        pthread_t thread1, thread2;
        thread_data_t data1 = {data->array, left, mid};
        thread_data_t data2 = {data->array, mid + 1, right};

        pthread_create(&thread1, NULL, merge_sort, &data1);
        pthread_create(&thread2, NULL, merge_sort, &data2);

        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);

        merge(data->array, left, mid, right);
    }

    pthread_exit(NULL);   
}

void print(int *arr, int n) {
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7, 1, 8, 9, 2, 10, 3, 4}; // 13
    int len = sizeof(arr) / sizeof(arr[0]);

    pthread_t thread;
    thread_data_t data = {arr, 0, len - 1};

    pthread_create(&thread, NULL, merge_sort, &data);
    pthread_join(thread, NULL);

    print(arr, len);

    return 0;    
}
