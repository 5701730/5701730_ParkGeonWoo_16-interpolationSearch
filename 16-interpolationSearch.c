#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000 

int compareCount = 0; 


void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 10000; // 0~9999 사이의 랜덤 숫자
    }
}

// 퀵 정렬
void quickSort(int* array, int left, int right) {
    if (left >= right) return;

    int pivot = array[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        compareCount++;
        if (array[j] <= pivot) {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }

    int temp = array[i + 1];
    array[i + 1] = array[right];
    array[right] = temp;

    quickSort(array, left, i);
    quickSort(array, i + 2, right);
}

// 이진 탐색
int binarySearch(int* array, int target) {
    int left = 0, right = SIZE - 1;
    int localCompareCount = 0;

    while (left <= right) {
        localCompareCount++;
        int mid = left + (right - left) / 2;

        if (array[mid] == target) {
            compareCount += localCompareCount;
            return mid;
        }
        if (array[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    compareCount += localCompareCount;
    return -1;
}

// 보간 탐색
int interpolationSearch(int* array, int target) {
    int left = 0, right = SIZE - 1;
    int localCompareCount = 0;

    while (left <= right && target >= array[left] && target <= array[right]) {
        if (left == right) {
            if (array[left] == target) {
                compareCount += (++localCompareCount);
                return left;
            }
            break;
        }

        // 보간 공식
        int pos = left + ((target - array[left]) * (right - left) / (array[right] - array[left]));
        localCompareCount++;

        if (array[pos] == target) {
            compareCount += localCompareCount;
            return pos;
        }

        if (array[pos] < target)
            left = pos + 1;
        else
            right = pos - 1;
    }

    compareCount += localCompareCount;
    return -1;
}

// 평균 비교 횟수 계산
float getAverageBinarySearchCompareCount(int* array) {
    compareCount = 0;
    for (int i = 0; i < 1000; i++) {
        int target = array[rand() % SIZE]; // 배열에서 항상 존재하는 값 선택
        binarySearch(array, target);
    }
    return compareCount / 1000.0;
}

float getAverageInterpolationSearchCompareCount(int* array) {
    compareCount = 0;
    for (int i = 0; i < 1000; i++) {
        int target = array[rand() % SIZE]; // 배열에서 항상 존재하는 값 선택
        interpolationSearch(array, target);
    }
    return compareCount / 1000.0;
}

// 배열 출력
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++) {
        printf("%4d ", array[i]);
    }
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++) {
        printf("%4d ", array[i]);
    }
    printf("\n\n");
}

int main(int argc, char* argv[]) {
    srand(time(NULL)); // 랜덤 시드 초기화

    for (int i = 0; i < 3; i++) { // 3번 연속 실행
        int array[SIZE];
        generateRandomArray(array);

        quickSort(array, 0, SIZE - 1);
        printArray(array);

        printf("Average Compare Count of Binary Search: %.2f\n", getAverageBinarySearchCompareCount(array));
        printf("Average Compare Count of Interpolation Search: %.2f\n", getAverageInterpolationSearchCompareCount(array));

        printf("\n");
    }

    return 0;
}
