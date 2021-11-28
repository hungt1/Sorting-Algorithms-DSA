#include "Sort.h"
using namespace std;

// Selection Sort
void selectionSort(int a[], int n){
    for (int i = 0; i < n; i++){
        int idx = i;
        for (int j = i + 1; j < n; j++){
            if (a[j] < a[idx]){
                idx = j;
            }
        }
        swap(a[i], a[idx]);
    }
}
// -----------------------------------------------


// Insertion Sort
void insertionSort(int a[], int n){
    for (int i = 1; i < n; i++){
        int cur = a[i];
        int j = i; 
        for (; j > 0 && cur < a[j - 1]; j--){
            a[j] = a[j - 1];
        }
        a[j] = cur;
    }
}
// -----------------------------------------------


// Bubble Sort
void bubbleSort(int a[], int n){
    for (int i = 0; i < n - 1; i++){
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++){
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}
// -----------------------------------------------


// Shell Sort
// reference: https://www.geeksforgeeks.org/cpp-program-for-shellsort/
void shellSort(int a[], int n){
    for (int gap = n / 2; gap > 0; gap /= 2){
        for (int i = gap; i < n; i++){
            int cur = a[i];
            int j = i; 
            for (; j >= gap && cur < a[j - gap]; j -= gap){
                a[j] = a[j - gap];
            }
            a[j] = cur;
        }
    }
}
// -----------------------------------------------


// Shaker Sort
void shakerSort(int a[], int n){
    int left = 0, right = n - 1;
    for (int i = 0; i < n - 1; i++){
        bool swapped = false;
        if (i % 2 == 0){
            for (int j = left; j < right; j++){
                if (a[j] > a[j + 1]){
                    swap(a[j], a[j + 1]);
                    swapped = true;
                }
            }
            right--;
        }
        else {
            for (int j = right; j > left; j--){
                if (a[j] < a[j - 1]){
                    swap(a[j], a[j - 1]);
                    swapped = true;
                }
            }
            left++;
        }
        if (!swapped) break;
    }
}
// -----------------------------------------------

// Heap Sort
// reference: https://www.geeksforgeeks.org/cpp-program-for-heap-sort/
void heapify(int a[], int n, int i){
    int largest = i;
    int l = 2 * i + 1, r = 2 * i + 2;
    
    if (l < n && a[l] > a[largest]) largest = l;

    if (r < n && a[r] > a[largest]) largest = r;

    if (largest != i){
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void buildHeap(int a[], int n){
    for (int i = n / 2 - 1; i >= 0; i--){
        heapify(a, n, i);
    }
}

void heapSort(int a[], int n){
    buildHeap(a, n);
    for (int i = n - 1; i > 0; i--){
        swap(a[i], a[0]);
        heapify(a, i, 0);
    }
}
// -----------------------------------------------


// Merge Sort
void merge(int left[], int n1, int right[], int n2, int dest[], int n){
    int ptr1 = 0, ptr2 = 0;
    int cur = 0;
    int* tmp = new int[n];
    while (ptr1 < n1 && ptr2 < n2){
        if (left[ptr1] < right[ptr2]){
            tmp[cur++] = left[ptr1++];
        }
        else {
            tmp[cur++] = right[ptr2++];
        }
    }
    while (ptr1 < n1) tmp[cur++] = left[ptr1++];
    while (ptr2 < n2) tmp[cur++] = right[ptr2++];
    memcpy(dest, tmp, n * sizeof(int)); 
    delete[] tmp;
}

void mergeSort(int a[], int n){
    if (n > 1){
        int m = (n + 1) / 2;
        mergeSort(a, m); mergeSort(a + m, n - m);
        merge(a, m, a + m, n - m, a, n);
    }
}
// -----------------------------------------------


// Quick Sort
int partition(int a[], int n){
    swap(a[n - 1], a[rand() % n]);
    int pivot = a[n - 1];
    int i = 0;
    for (int j = 0; j < n; j++){
        if (a[j] <= pivot){
            swap(a[i++], a[j]);
        }
    }
    return i;
}

void quickSort(int a[], int n){
    if (n > 1){
        int m = partition(a, n);
        quickSort(a, m - 1); 
        quickSort(a + m, n - m);
    }
}
// -----------------------------------------------


// Counting Sort
// magic: https://stackoverflow.com/questions/2204176/how-to-initialise-memory-with-new-operator-in-c
void countingSort(int a[], int n){
    int mn = a[0];
    int mx = a[0];
    for (int i = 0; i < n; i++){
        if (a[i] < mn) mn = a[i];
        if (a[i] > mx) mx = a[i];
    }

    int* cnt = new int[mx - mn + 1]();
    for (int i = 0; i < n; i++){
        cnt[a[i] - mn]++;
    }

    for (int i = 1; i <= mx - mn; i++){
        cnt[i] += cnt[i - 1];
    }
    
    int* tmp = new int[n];
    for (int i = 0; i < n; i++){
        tmp[--cnt[a[i] - mn]] = a[i];
    }
    memcpy(a, tmp, sizeof(int) * n);
    delete[] tmp; delete[] cnt;
}
// -----------------------------------------------


// Radix Sort
void radixSort(int a[], int n){
    int mx = a[0];
    for (int i = 0; i < n; i++){
        if (a[i] > mx) mx = a[i];
    }

    int cnt[10] = {0};
    int* tmp = new int[n];
    for (int exp = 1; mx / exp > 0; exp *= 10){
        for (int i = 0; i < n; i++){
            cnt[(a[i] / exp) % 10]++;
        }
        for (int i = 1; i < 10; i++) cnt[i] += cnt[i - 1];

        for (int i = n - 1; i >= 0; i--){
            tmp[--cnt[(a[i] / exp) % 10]] = a[i];
        }
        memcpy(a, tmp, sizeof(int) * n);
        memset(cnt, 0, 40);
    }
    delete[] tmp; 
}
// -----------------------------------------------


// Flash Sort
// Idea: Mr. Phuong
void flashSort(int a[], int n){
    int mn = a[0], mx = a[0];
    for (int i = 0; i < n; i++){
        if (a[i] < mn) mn = a[i];
        if (a[i] > mx) mx = a[i];
    }
    if (mn == mx) return;

    int m = 0.43 * n;
    if (m < 2) m = 2;
    int* layer = new int[m]();
    for (int i = 0; i < n; i++){
        int k = 1ll * (m - 1) * (a[i] - mn) / (mx - mn);
        layer[k]++;
    }

    for (int i = 1; i < m; i++){
        layer[i] += layer[i - 1];
    }

    for (int i = 0; i < n; i++){
        int idx = i, val = a[i];
        int k = 1ll * (m - 1) * (val - mn) / (mx - mn);
        while (i < layer[k]){
            int nxt = --layer[k], nxtVal = a[nxt];
            a[nxt] = val;
            idx = nxt;  val = nxtVal;
            k = 1ll * (m - 1) * (val - mn) / (mx - mn);
            if (idx == i) break;
        }
    }
    
    for (int i = 0; i < m - 1; i++){
        insertionSort(a + layer[i], layer[i + 1] - layer[i]);
    }
    delete[] layer; 
}
// -----------------------------------------------