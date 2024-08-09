#include "SortingAlgorithms.h"

void quickSort(PagedArray& array, int low, int high) {
    if (low < high) {
        int pivot = array[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (array[j] < pivot) {
                ++i;
                std::swap(array[i], array[j]);
            }
        }
        std::swap(array[i + 1], array[high]);
        int pi = i + 1;
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

void insertionSort(PagedArray& array, int low, int high) {
    for (int i = low + 1; i <= high; ++i) {
        int key = array[i];
        int j = i - 1;
        while (j >= low && array[j] > key) {
            array[j + 1] = array[j];
            --j;
        }
        array[j + 1] = key;
    }
}

void bubbleSort(PagedArray& array, int low, int high) {
    bool swapped;
    for (int i = low; i < high; ++i) {
        swapped = false;
        for (int j = low; j < high - i; ++j) {
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}
