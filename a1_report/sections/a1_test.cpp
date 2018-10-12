#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

typedef struct node_t {
    int key;
    struct node_t *next;
    node_t(int v) {key = v; next = NULL;}
} node_t;

void add(node_t *prev, int key) {
    node_t *tmp = new node_t(key);
    tmp->next = prev->next;
    prev->next = tmp;
}

void swap(int &a, int &b) {
    int t = a; a = b; b = t;
}

void bubblesort(int *d, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = n - 1; j > i; --j)
            if (d[j] < d[j-1])
                swap(d[j], d[j-1]);
}

void insertionsort_array(int *d, int n) {
    for (int i = 1; i < n; ++i) {
        int key = d[i], j;
        for (j = 0; j < i && d[j] <= key; ++j);
        for (int k = i; k > j; --k) d[k] = d[k-1];
        d[j] = key;
    }
}

void insertionsort_list(int *d, int n) {
    node_t *head = new node_t(0);
    for (int i = 0; i < n; ++i) {
        node_t *tmp = head;
        while (tmp->next && tmp->next->key < d[i]) tmp = tmp->next;
        add(tmp, d[i]);
    }
    node_t *tmp = head->next, *ptr;
    while (tmp) {
        cout << tmp->key;
        ptr = tmp;
        tmp = tmp->next;
        delete ptr;
    }
    delete head;
}

void selectionsort(int *d, int n) {
    for (int i = 0; i < n - 1; ++i) {
        int flag = i;
        for (int j = i + 1; j < n; ++j)
            if (d[j] < d[flag])
                flag = j;
        swap(d[flag], d[i]);
    }
}

void merge(int *d, int l, int m, int r) {
    int i = l, j = m + 1, k = 0;
    int *tmp = new int[r-l+1];
    while (i <= m && j <= r) {
        if (d[i] <= d[j]) tmp[k++] = d[i++];
        else tmp[k++] = d[j++];
    }
    while (i <= m) tmp[k++] = d[i++];
    while (j <= r) tmp[k++] = d[j++];
    for (i = l; i <= r; ++i) d[i] = tmp[i-l];
    delete[] tmp;
}

void mergesort(int *d, int l, int r) { //close interval
    if (l >= r) return;
    int m = ((l + r) >> 1);
    mergesort(d, l, m);
    mergesort(d, m + 1, r);
    merge(d, l, m, r);
}

void quicksort_extra(int *d, int l, int r) {
    if (l >= r) return;
    int p = rand()%(r-l+1)+l;
    swap(d[l], d[p]);
    int key = d[l];
    int i = 0, j = r - l;
    int *b = new int[r-l+1];
    for (int k = l + 1; k <= r ; ++k) {
        if (d[k] < key) b[i++] = d[k];
        else b[j--] = d[k];
    }
    b[i] = key;
    for (int k = 0; k <= r - l; ++k) d[k + l] = b[k];
    delete[] b;
    quicksort_extra(d, l, l + i - 1);
    quicksort_extra(d, l + i + 1, r);
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

void rd(int *d, int n){
    for (int i = 0; i < n; ++i)
        cin >> d[i];
}

void prt(int *d, int n) {
    for (int i = 0; i < n; ++i)
        cout << d[i] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    srand(time(NULL));
    int cmd, n;
    cin >> cmd >> n;
    int *d = new int[n];
    rd(d, n);
    int start = clock();
    switch(cmd) {
        case 0: bubblesort(d, n); break;
        case 1: insertionsort_array(d, n); break;
        case 2: selectionsort(d, n); break;
        case 3: mergesort(d, 0, n-1); break;
        case 4: quicksort_extra(d, 0, n-1); break;
        case 5: quicksort_inplace(d, 0, n-1); break;
        default: return 0;
    }
    //prt(d, n);
    cout << (clock() - start)*1.0/CLOCKS_PER_SEC << "\n";
    delete[] d;
    return 0;
}