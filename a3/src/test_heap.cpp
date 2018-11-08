#include <iostream>
#include "priority_queue.h"
#include "binary_heap.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

#define MAXN 10010
int a[MAXN];
// The following example defines a functor. It is defined using struct keyword.
// Recall that struct keyword can also be used to define a class, so it can
// have member functions, as the example shown below. The difference of using
// struct is that by default all the members are public instead of private. For
// the following functor, it has no data member, but just a function member
// which is an overloaded operator (). 
//
// To use it, you can write
//      compare_t comp; // This defines an object comp of compare_t type.
//      comp(3, 5); // This calls the overloaded operator() of object comp.
//                  // In this example, it will return 3>5;
//
// In this project you will need to define and use functor similar to the
// following example. The functor you define takes two argument of TYPE and
// will return true if and only if the first argument is strictly smaller
// than the second argument. The functor type will be passed as the COMP
// template parameter to the priority queue template. See priority_queue.h,
// binary_heap.h, and binary_array.h.
struct compare_t
{
    bool operator()(int a, int b) const
    {
        return a > b;
    }
};

int main(int argc, char* argv[])
{
    srand(time(NULL));
    for (int j = 0; j < MAXN; ++j) a[j] = rand()%1000000-500000;

    int i;
    int size = sizeof(a)/sizeof(int);
    /*
    cout << "Input: ";
    for(i = 0; i < size; i++)
        cout << a[i] << " " << flush;
    cout << endl;
*/
    // We define a priority queue on int with the comparison functor as
    // compare_t defined above. For this queue, the larger the int value is,
    // the less prior it is.
    priority_queue<int, compare_t> *pql = new binary_heap<int, compare_t>;
    for(i = 0; i < size; i++)
        pql->enqueue(a[i]);

    cout << "Sort in descending order: " << flush;
    int prev = 0;
    for(i = 0; i < size; i++)
    {
        int val = pql->dequeue_min();
        if (val > prev && i > 0) return -1;
        prev = val;
    }
    cout << endl;
    delete pql;

    // For some built-in types or library types, they may define a default less
    // than operator. In this case, when you declare a priority queue, you can
    // omit the second template parameter COMP and it will still work. See
    // priority_queue.h, binary_heap.h, and binary_heap.h, from which you
    // will notice that by default COMP =  std::less<TYPE>.
    //
    // For the following example, we omit the second template parameter, so the
    // priority queue uses the default less than operator defined on int. In
    // this queue, the smaller the int value is, the less prior it is.
    priority_queue<int> *pqs = new binary_heap<int>;
    for(i = 0; i < size; i++)
        pqs->enqueue(a[i]);

    cout << "Sort in ascending order: " << flush;
    for(i = 0; i < size; i++)
    {
        int val = pqs->dequeue_min();
        if (val < prev && i > 0) return -1;
        prev = val;
    }
    cout << endl;

    delete pqs;
    return 0;
}
