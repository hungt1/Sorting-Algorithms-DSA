bool isSorted(int a[], int c[], int n){
    for (int i = 0; i < n; i++){
        if (a[i] != c[i]){
            return false;
        }
    }
    return true;
}