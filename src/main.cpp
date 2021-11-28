#include "support/DataGenerator.cpp"
#include "support/Checker.h"
#include "Sort.h"
#include "SortComp.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <algorithm>
using namespace std;

#define TESTING 0

#define RANDOM 0
#define NEARLY_SORTED 1
#define SORTED 2
#define REVERSE_SORTED 3

typedef void (*sort_pointer)(int*, int);

const sort_pointer SORT_TYPE[11] = {selectionSort, insertionSort, bubbleSort, shellSort, 
    shakerSort, heapSort, mergeSort, quickSort, countingSort, radixSort, flashSort};

const sort_pointer SORT_COMP_TYPE[11] = {selectionSortComp, insertionSortComp, bubbleSortComp, shellSortComp, 
    shakerSortComp, heapSortComp, mergeSortComp, quickSortComp, countingSortComp, radixSortComp, flashSortComp};

const string SORT_NAME[11] = {"selection-sort", "insertion-sort", "bubble-sort", "shell-sort", 
    "shaker-sort", "heap-sort", "merge-sort", "quick-sort", "counting-sort", "radix-sort", "flash-sort"};

const string SORT_NAME_V2[11] = {"Selection Sort", "Insertion Sort", "Bubble Sort", "Shell Sort", 
    "Shaker Sort", "Heap Sort", "Merge Sort", "Quick Sort", "Counting Sort", "Radix Sort", "Flash Sort"};

const int DATA_SIZE[6] = {10000, 30000, 50000, 100000, 300000, 500000};

string getDataOrder(int i){
    if (i == RANDOM) return "Randomized";
    if (i == SORTED) return "Sorted";
    if (i == REVERSE_SORTED) return "Reverse Sorted";
    if (i == NEARLY_SORTED) return "Nearly Sorted";
    return "none";
}

int getTypeDataOrder(string cur){
    if (cur == "-rand") return 0;
    if (cur == "-nsorted") return 1;
    if (cur == "-sorted") return 2;
    if (cur == "-rev") return 3;
    return -1;
}

int toNumber(string cur){
    for (char c : cur){
        if (c < '0' || c > '9') return -1;
    }
    if (cur.length() > 7) return -2;
    int ans = stoi(cur);
    return (ans <= 1000000 ? ans : -2);
}

int getSortNameIndex(string cur){
    for (int i = 0; i < 11; i++){
        if (SORT_NAME[i] == cur) return i;
    }
    return -1;
}


void readDataFile(ifstream& f, int* &a, int &n){
    f >> n;
    a = new int[n];
    for (int i = 0; i < n; i++){
        f >> a[i];
    }
}

void runAlgo(int idx, string t, int* a, int n){
    int* b = new int[n];
    memcpy(b, a, sizeof(int) * n);
    if (t == "-time" || t == "-both"){
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        SORT_TYPE[idx](a, n);
        auto end = chrono::high_resolution_clock::now();
        double time_in_ms = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_in_ms *= 1e-6;
        cout << "Running time: " << time_in_ms << "ms\n";
    }
    if (t == "-comp" || t == "-both"){
        Counter::numOfComparisons = 0;
        SORT_COMP_TYPE[idx](b, n);
        cout << "Comparisons: " << Counter::numOfComparisons << '\n';
    }
    delete[] b;
}

void runCompAlgo(int idx1, int idx2, int* a, int n){
    int* b = new int[n];
    double t1, t2; long long c1, c2;

    memcpy(b, a, sizeof(int) * n);
    auto start = chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    SORT_TYPE[idx1](b, n);
    auto end = chrono::high_resolution_clock::now();
    t1 = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    t1 *= 1e-6;

    memcpy(b, a, sizeof(int) * n);
    start = chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    SORT_TYPE[idx2](b, n);
    end = chrono::high_resolution_clock::now();
    t2 = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    t2 *= 1e-6;

    memcpy(b, a, sizeof(int) * n);
    Counter::numOfComparisons = 0;
    SORT_COMP_TYPE[idx1](b, n);
    c1 = Counter::numOfComparisons;

    Counter::numOfComparisons = 0;
    SORT_COMP_TYPE[idx2](a, n);
    c2 = Counter::numOfComparisons;

    cout << "Running time: " << t1 << "ms | " << t2 << "ms\n";
    cout << "Comparisons: " << c1 << " | " << c2 << '\n';

    delete[] b;
}

const string NAME_OF_FILE[4] = {"input_1.txt", "input_2.txt", "input_3.txt", "input_4.txt"};

void process(vector<string>& cmd, int op){
    if (op == -1){
        cout << "Invalid data size !!!\n";
        return;
    }
    if (op == 0){
        cout << "Invalid command !!!\n";
        return;
    }
    if (op == 1){
        ifstream f; f.open(cmd[2], ios::in);
        if (!f){
            cout << "File not found !!!\n";
            return;
        }
        int idx = getSortNameIndex(cmd[1]);
        int n; int* a;
        readDataFile(f, a, n);
        f.close();
        cout << "ALGORITHM MODE\n";
        cout << "Algorithm: " << SORT_NAME_V2[idx] << '\n';
        cout << "Input file: " << cmd[2] << '\n';
        cout << "Input size: " << n << '\n';
        cout << "----------------------------------\n";
        runAlgo(idx, cmd[3], a, n);
        ofstream g; g.open("output.txt", ios::out | ios::binary);
        g << n << '\n';
        for (int i = 0; i < n; i++){
            if (i) g << ' ';
            g << a[i];
        }
        g.close();
        delete[] a;
        return;
    }
    if (op == 2){
        int n = toNumber(cmd[2]);
        int o = getTypeDataOrder(cmd[3]);
        int idx = getSortNameIndex(cmd[1]);
        cout << "ALGORITHM MODE\n";
        cout << "Algorithm: " << SORT_NAME_V2[idx] << '\n';
        cout << "Input size: " << n << '\n';
        cout << "Input oder: " << getDataOrder(o) << '\n';
        cout << "----------------------------------\n";
        int* a = new int[n];
        GenerateData(a, n, o);
        ofstream g; g.open("input.txt", ios::out | ios::binary);
        g << n << '\n';
        for (int i = 0; i < n; i++){
            if (i) g << ' ';
            g << a[i];
        }
        g.close();
        runAlgo(idx, cmd[4], a, n);
        g.open("output.txt", ios::out | ios::binary);
        g << n << '\n';
        for (int i = 0; i < n; i++){
            if (i) g << ' ';
            g << a[i];
        }
        g.close();
        delete[] a;
        return;
    }
    if (op == 3){
        int n = toNumber(cmd[2]);
        int idx = getSortNameIndex(cmd[1]);
        cout << "ALGORITHM MODE\n";
        cout << "Algorithm: " << SORT_NAME_V2[idx] << '\n';
        cout << "Input size: " << n << "\n";
        for (int o = 0; o < 4; o++){
            int* a = new int[n];
            GenerateData(a, n, o);
            ofstream g; g.open(NAME_OF_FILE[o], ios::out | ios::binary);
            g << n << '\n';
            for (int i = 0; i < n; i++){
                if (i) g << ' ';
                g << a[i];
            }
            g.close();
            cout << "\n----------------------------------\n";
            cout << "Input order: " << getDataOrder(o) << '\n';
            runAlgo(idx, cmd[3], a, n);
            delete[] a;
        }
        return;
    }
    if (op == 4){
        int idx1 = getSortNameIndex(cmd[1]);
        int idx2 = getSortNameIndex(cmd[2]);
        ifstream f; f.open(cmd[3], ios::in);
        if (!f){
            cout << "File not found !!!\n";
            return;
        }
        int n; int* a;
        readDataFile(f, a, n);
        f.close();
        cout << "COMPARE MODE\n";
        cout << "Algorithm: " << SORT_NAME_V2[idx1] << " | " << SORT_NAME_V2[idx2] << '\n';
        cout << "Input file: " << cmd[3] << '\n';
        cout << "Input size: " << n << '\n';
        cout << "----------------------------------\n";
        runCompAlgo(idx1, idx2, a, n);
        delete[] a;
        return;
    }
    if (op == 5){
        int idx1 = getSortNameIndex(cmd[1]);
        int idx2 = getSortNameIndex(cmd[2]);
        int n = toNumber(cmd[3]);
        int o = getTypeDataOrder(cmd[4]);
        cout << "COMPARE MODE\n";
        cout << "Algorithm: " << SORT_NAME_V2[idx1] << " | " << SORT_NAME_V2[idx2] << '\n';
        cout << "Input size: " << n << '\n';
        cout << "Input order: " << getDataOrder(o) << '\n';
        cout << "----------------------------------\n";
        int* a = new int[n];
        GenerateData(a, n, o);
        ofstream g; g.open("input.txt", ios::out | ios::binary);
        g << n << '\n';
        for (int i = 0; i < n; i++){
            if (i) g << ' ';
            g << a[i];
        }
        g.close();
        runCompAlgo(idx1, idx2, a, n);

    }
}

int getTypeOfCommand(vector<string> cmd){
    if (cmd.size() < 4 || cmd.size() > 5) return 0;
    if (cmd[0] != "-a" && cmd[0] != "-c") return 0;
    if (cmd[0] == "-a"){
        if (cmd.back() != "-both" && cmd.back() != "-time" && cmd.back() != "-comp") return 0;
        if (getSortNameIndex(cmd[1]) == -1) return 0;
        int n = toNumber(cmd[2]);
        if (cmd.size() == 4){
            if (n == -2) return -1;
            else if (n != -1) return 3;
            else return 1;
        }
        else {
            if (n == -2) return -1;
            else if (n == -1) return 0;
            else {
                if (getTypeDataOrder(cmd[3]) == -1) return 0;
                else return 2;
            }
        }
    }
    else {
        int idx1 = getSortNameIndex(cmd[1]);
        int idx2 = getSortNameIndex(cmd[2]);
        if (idx1 == -1 || idx2 == -1) return 0;
        int n = toNumber(cmd[3]);
        if (cmd.size() == 4){
            return 4;
        }
        else {
            if (n >= 0 && getTypeDataOrder(cmd[4]) != -1) return 5;
            else if (n == -2) return -1;
        }
    }
    return 0;
}

long long Counter::numOfComparisons = 0;

// compile: g++ main.cpp Sort.cpp SortComp.cpp -std=c++14 -o main
int main(int argc, char** argv)
{   
    srand(time(nullptr));
    if (TESTING){
        freopen("data.csv", "w", stdout);
        cout << "Sort name, Data order, Data size, Execution time (in milisecond), Comparisons\n";
        for (int o = 0; o < 4; o++){
            for (int s = 0; s < 6; s++){
                for (int i = 0; i < 11; i++){
                    int n = DATA_SIZE[s];
                    int* a = new int[n];
                    int* b = new int[n];
                    int* c = new int[n];
                    GenerateData(a, n, o);
                    memcpy(b, a, sizeof(int) * n);
                    memcpy(c, a, sizeof(int) * n);
                    sort(c, c + n);

                    auto start = chrono::high_resolution_clock::now();
                    ios_base::sync_with_stdio(false);
                    SORT_TYPE[i](a, n);
                    auto end = chrono::high_resolution_clock::now();
                    double time_in_ms = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                    time_in_ms *= 1e-6;

                    if (!isSorted(a, c, n)){
                        cerr << o << ' ' << s << ' ' << n << ' ' << "Stupid Sort in time !!!\n";
                        return 1;
                    }
                    
                    Counter::numOfComparisons = 0;
                    SORT_COMP_TYPE[i](b, n);
                    if (!isSorted(b, c, n)){
                        cerr << o << ' ' << s << ' ' << n << ' ' << "Stupid Sort in count comparisons !!!\n";
                        return 1;
                    }
                    cerr << SORT_NAME[i] << " - " << getDataOrder(o) << " - " << n << " - ";
                    cerr << fixed << setprecision(6) << time_in_ms << "ms - " << Counter::numOfComparisons << '\n';;
                    
                    cout << SORT_NAME[i] << ", " << getDataOrder(o) << ", " << n << ", ";
                    cout << fixed << setprecision(6) << time_in_ms << ", " << Counter::numOfComparisons << '\n';
                    delete[] a; delete[] b;
                }
            }
        }
    }
    else {
        vector<string> cmd;
        for (int i = 1; i < argc; i++){
            cmd.push_back(string(argv[i]));
        }
        int op = getTypeOfCommand(cmd);
        process(cmd, op);
    }
    return 0;
}


/*
Example:
Command 1: main -a flash-sort input.txt -both
Command 2: main -a flash-sort 100000 -rand -time
Command 3: main -a flash-sort 100000 -comp

Command 4: main -c flash-sort heap-sort input.txt
COmmand 5: main -c flash-sort heap-sort 1000000 -nsorted
*/