#include <iostream>
#include <vector>

std::vector<int> max_elem(std::vector<int> &array) {
    if (array.size() == 0) return {};

    int current_max = 1;
    int max = 1;

    int index_start = 0;

    for (int i = 0; i < array.size(); i++) {
        if (array[i + 1] > array[i]) {
            current_max++;
        }
        else {
            current_max = 1;
        }

        if (current_max > max) {
            max = current_max;
            index_start = i - max + 2;
        }
    }

    std::vector<int> res;

    for(int i = index_start, j = 0; j < max; i++, j++) {
        res.push_back(array[i]);
    }

    return res;
}

// алгоритм Кадана
std::vector<int> max_sum(std::vector<int> &array) {
    if (array.size() == 0) return {};

    int current_max = array[0];
    int max = array[0];

    int current_len = 1;
    int len = 1;

    int index_start = 0;

    for (int i = 0; i < array.size(); i++) {
        if (array[i + 1] > array[i]) {
            current_max += array[i + 1];
            current_len++;
        }
        else {
            current_max = array[i];
            current_len = 1;
        }

        if (current_max > max) {
            max = current_max;
            len = current_len;
            index_start = i - len + 2;
        }
    }

    std::vector<int> res;

    for(int i = index_start, j = 0; j < len; i++, j++) {
        res.push_back(array[i]);
    }

    return res;
}

int sum(std::vector<int> &array) {
    int sum = 0;

    for(int i : array) {
        sum += i;
    }

    return sum;
}

/*int main() {                 // 0  1  2  3  4  5  6  7  8
    std::vector<int> numbers = {-2, -1, 0, -3, 1, 2, -1};

    std::vector<int> res1 = max_elem(numbers);
    for(int i : res1)  std::cout << i << " ";
    std::cout << "\n\n";

    std::vector<int> res2 = max_sum(numbers);
    for(int i : res2) std::cout << i << " ";
    std::cout << std::endl;
    std::cout << sum(res2) << std::endl;
}*/