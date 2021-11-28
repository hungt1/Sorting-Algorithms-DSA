#include "SortComp.h"
using namespace std;

bool lt(const int& i, const int &j){ // less than
    Counter::numOfComparisons++;
    return (i < j);
}

bool le(const int& i, const int& j){ // less or equal
    Counter::numOfComparisons++;
    return (i <= j);
}

bool gt(const int& i, const int& j){ // greater than
    Counter::numOfComparisons++;
    return (i > j);
}

bool ge(const int& i, const int& j){ // greater or equal
    Counter::numOfComparisons++;
    return (i >= j);
}

bool eq(const int& i, const int &j){ // equal
    Counter::numOfComparisons++;
    return (i == j);
}

// Selection Sort
void selectionSortComp(int a[], int n){
    for (int i = 0; lt(i, n); i++){
        int idx = i;
        for (int j = i + 1; lt(j, n); j++){
            if (lt(a[j], a[idx])){
                idx = j;
            }
        }
        swap(a[i], a[idx]);
    }
}
// -----------------------------------------------


// Insertion Sort
void insertionSortComp(int a[], int n){
    for (int i = 1; lt(i, n); i++){
        int cur = a[i];
        int j = i; 
        for (; gt(j, 0) && lt(cur, a[j - 1]); j--){
            a[j] = a[j - 1];
        }
        a[j] = cur;
    }
}
// -----------------------------------------------


// Bubble Sort
void bubbleSortComp(int a[], int n){
    for (int i = 0; lt(i, n - 1); i++){
        bool swapped = false;
        for (int j = 0; lt(j, n - i - 1); j++){
            if (gt(a[j], a[j + 1])) {
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
void shellSortComp(int a[], int n){
    for (int gap = n / 2; gt(gap, 0); gap /= 2){
        for (int i = gap; lt(i, n); i++){
            int cur = a[i];
            int j = i; 
            for (; ge(j, gap) && lt(cur, a[j - gap]); j -= gap){
                a[j] = a[j - gap];
            }
            a[j] = cur;
        }
    }
}
// -----------------------------------------------


// Shaker Sort
void shakerSortComp(int a[], int n){
    int left = 0, right = n - 1;
    for (int i = 0; lt(i, n - 1); i++){
        bool swapped = false;
        if (eq(i % 2, 0)){
            for (int j = left; lt(j, right); j++){
                if (gt(a[j], a[j + 1])){
                    swap(a[j], a[j + 1]);
                    swapped = true;
                }
            }
            right--;
        }
        else {
            for (int j = right; gt(j, left); j--){
                if (lt(a[j], a[j - 1])){
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
void heapifyComp(int a[], int n, int i){
    int largest = i;
    int l = 2 * i + 1, r = 2 * i + 2;
    
    if (lt(l, n) && gt(a[l], a[largest])) largest = l;

    if (lt(r, n) && gt(a[r], a[largest])) largest = r;

    if (largest != i){
        swap(a[i], a[largest]);
        heapifyComp(a, n, largest);
    }
}

void buildHeapComp(int a[], int n){
    for (int i = n / 2 - 1; ge(i, 0); i--){
        heapifyComp(a, n, i);
    }
}

void heapSortComp(int a[], int n){
    buildHeapComp(a, n);
    for (int i = n - 1; gt(i, 0); i--){
        swap(a[i], a[0]);
        heapifyComp(a, i, 0);
    }
}
// -----------------------------------------------


// Merge Sort
void mergeComp(int left[], int n1, int right[], int n2, int dest[], int n){
    int ptr1 = 0, ptr2 = 0;
    int cur = 0;
    int* tmp = new int[n];
    while (lt(ptr1, n1) && lt(ptr2, n2)){
        if (lt(left[ptr1], right[ptr2])){
            tmp[cur++] = left[ptr1++];
        }
        else {
            tmp[cur++] = right[ptr2++];
        }
    }
    while (lt(ptr1, n1)) tmp[cur++] = left[ptr1++];
    while (lt(ptr2, n2)) tmp[cur++] = right[ptr2++];
    memcpy(dest, tmp, n * sizeof(int)); 
    delete[] tmp;
}

void mergeSortComp(int a[], int n){
    if (gt(n, 1)){
        int m = (n + 1) / 2;
        mergeSortComp(a, m); mergeSortComp(a + m, n - m);
        mergeComp(a, m, a + m, n - m, a, n);
    }
}
// -----------------------------------------------


// Quick Sort
int partitionComp(int a[], int n){
    swap(a[n - 1], a[rand() % n]);
    int pivot = a[n - 1];
    int i = 0;
    for (int j = 0; lt(j, n); j++){
        if (le(a[j], pivot)){
            swap(a[i++], a[j]);
        }
    }
    return i;
}

void quickSortComp(int a[], int n){
    if (gt(n, 1)){
        int m = partitionComp(a, n);
        quickSortComp(a, m - 1); 
        quickSortComp(a + m, n - m);
    }
}
// -----------------------------------------------


// Counting Sort
// magic: https://stackoverflow.com/questions/2204176/how-to-initialise-memory-with-new-operator-in-c
void countingSortComp(int a[], int n){
    int mn = a[0];
    int mx = a[0];
    for (int i = 0; lt(i, n); i++){
        if (lt(a[i], mn)) mn = a[i];
        if (gt(a[i], mx)) mx = a[i];
    }

    int* cnt = new int[mx - mn + 1]();
    for (int i = 0; lt(i, n); i++){
        cnt[a[i] - mn]++;
    }

    for (int i = 1; le(i, mx - mn); i++){
        cnt[i] += cnt[i - 1];
    }
    
    int* tmp = new int[n];
    for (int i = 0; lt(i, n); i++){
        tmp[--cnt[a[i] - mn]] = a[i];
    }
    memcpy(a, tmp, sizeof(int) * n);
    delete[] tmp; delete[] cnt;
}
// -----------------------------------------------


// Radix Sort
void radixSortComp(int a[], int n){
    int mx = a[0];
    for (int i = 0; lt(i, n); i++){
        if (gt(a[i], mx)) mx = a[i];
    }

    int cnt[10] = {0};
    int* tmp = new int[n];
    for (int exp = 1; gt(mx / exp, 0); exp *= 10){
        for (int i = 0; lt(i, n); i++){
            cnt[(a[i] / exp) % 10]++;
        }
        for (int i = 1; lt(i, 10); i++) cnt[i] += cnt[i - 1];

        for (int i = n - 1; ge(i, 0); i--){
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
void flashSortComp(int a[], int n){
    int mn = a[0], mx = a[0];
    for (int i = 0; lt(i, n); i++){
        if (lt(a[i], mn)) mn = a[i];
        if (gt(a[i], mx)) mx = a[i];
    }
    if (eq(mn, mx)) return;

    int m = 0.43 * n;
    if (lt(m, 2)) m = 2;
    int* layer = new int[m]();
    for (int i = 0; lt(i, n); i++){
        int k = 1ll * (m - 1) * (a[i] - mn) / (mx - mn);
        layer[k]++;
    }

    for (int i = 1; lt(i, m); i++){
        layer[i] += layer[i - 1];
    }

    for (int i = 0; lt(i, n); i++){
        int idx = i, val = a[i];
        int k = 1ll * (m - 1) * (val - mn) / (mx - mn);
        while (lt(i, layer[k])){
            int nxt = --layer[k], nxtVal = a[nxt];
            a[nxt] = val;
            idx = nxt;  val = nxtVal;
            k = 1ll * (m - 1) * (val - mn) / (mx - mn);
            if (eq(idx, i)) break;
        }
    }
    
    for (int i = 0; lt(i, m - 1); i++){
        insertionSortComp(a + layer[i], layer[i + 1] - layer[i]);
    }
    delete[] layer; 
}
// -----------------------------------------------