#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
inline void swap(int &a, int &b) {
    int t = a; a = b; b = t;
}

int partition(int d[], int n, int p) {
    swap(d[0], d[p]);
    int key = d[0];
    int i = 0, j = n - 1;
    while (i < j) {
        while(d[j] >= key && i < j) --j;
        while(d[i] <= key && i < j) ++i;
        if (i < j) swap(d[i], d[j]);
    }
    d[0] = d[i];
    d[i] = key;
    return i;
}

void insertionsort(int d[], int n) {
    for (int i = 1; i < n; ++i) {
        int key = d[i], j;
        for (j = 0; j < i && d[j] <= key; ++j);
        for (int k = i; k > j; --k) d[k] = d[k-1];
        d[j] = key;
    }
}

void medians(int d[], int n) {
    int cnt = 0;
    for (int i = 0; i + 5 < n; i += 5) {
        insertionsort(d+i, 5);
        swap(d[cnt++], d[i+2]);
    }
}

int Rselect(int d[], int n, int k) {
    if (n == 1) return d[0];
    int p = rand() % n;
    int j = partition(d, n, p);
    if (j == k) return d[j];
    if (j > k) return Rselect(d, j, k);
    else return Rselect(d+j+1, n-j-1, k-j-1);
}

int Dselect(int d[], int n, int k) {
    if (n == 1) return d[0];
    if (n <= 5) {
        insertionsort(d, n);
        return d[k];
    }
    medians(d, n);
    Dselect(d, n/5, n/10);
    int p = n/10;
    int j = partition(d, n, p);
    if (j == k) return d[j];
    if (j > k) return Dselect(d, j, k);
    else return Dselect(d+j+1, n-j-1, k-j-1);
}

void quicksort_inplace(int *d, int l, int r) {
    if (l >= r) return;
    int p = rand()%(r-l+1)+l;
    swap(d[l], d[p]);
    int key = d[l];
    int i = l, j = r;
    while (i < j) {
        while(d[j] >= key && i < j) --j; // make sure finally i == j and d[j]=d[i] < key so that you could put it on the left
        while(d[i] <= key && i < j) ++i;
        if (i < j) swap(d[i], d[j]);
    }
    d[l] = d[i];
    d[i] = key;
    quicksort_inplace(d, l, i - 1);
    quicksort_inplace(d, i + 1, r);
}


int main() {
    ios::sync_with_stdio(false);
    srand(time(NULL));
    int n, k, flag;
    cin >> flag >> k >> n;
    int *d = new int[n];
    for (int i = 0; i < n; ++i) cin >> d[i];
    int start = clock();
    if (flag == 0) Rselect(d, n, k);
    else if (flag == 1) Dselect(d, n, k);
    else quicksort_inplace(d, 0, n-1);
    cout << (clock() - start)*1.0/CLOCKS_PER_SEC << "\n";
    delete[] d;
    return 0;
}