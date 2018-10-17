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

int main() {
    ios::sync_with_stdio(false);
    srand(time(NULL));
    int n, k, flag, ans;
    cin >> flag >> n >> k;
    int *d = new int[n];
    for (int i = 0; i < n; ++i) cin >> d[i];
    ans = (flag == 0) ? Rselect(d, n, k):Dselect(d, n, k);
    delete[] d;
    cout << "The order-" << k << " item is " << ans << "\n";
    return 0;
}