import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.patches import *
import seaborn as sns
n = [5, 5000, 8000, 12000, 20000, 30000, 40000, 50000, int(0.25e7), int(0.5e7), int(1e7), int(1.5e7), int(2.0e7), int(2.5e7), int(3e7)]
label = ['Bubblesort', 'Insertionsort', 'Selectionsort', 'Mergesort', 'Quicksort_extra', 'Quicksort_inplace']
def myplot(Range, N, Out, Label, Title, name):
    plt.figure(figsize=(10,6))
    for i in Range:
        time = [0]*len(N)
        for k in range(5):
            with open(Out.format(i,k), 'r') as f:
                data = f.read()
                tmp = data.split('\n')
                time = time + map(eval, tmp[:-1]) //eliminate the ending ' '
        time = [t/5.0 for i in time];
        plt.plot(N, time)
    plt.legend(Label, loc = 'upper left')
    plt.xlabel('Input size')
    plt.ylabel('Execution time (s)')
    plt.title(Title)
    plt.savefig(name)
    plt.show()

def __name__ = "__main__":
    myplot(range(3), n[:8], '{}{}.out', label[:3], '$O(n^2)$ sort algorithms', '012.jpg')
    myplot(range(3,6), n[8:], '{}{}.out', label[3:6], '$O(n\log n)$ sort algorithms', '345.jpg')
    myplot(range(3), n[:8], 'reverse{}{}.out', label[:3], '$O(n^2)$ Sort algorithms for a descending array', 'reverse012.jpg')
    myplot(range(3,6), n[8:], 'reverse{}{}.out', label[3:6], '$O(n\log n)$ Sort algorithms for a descending array', 'reverse345.jpg')
    myplot(range(6), n[:8], 'same{}{}.out', label, 'Sort algorithms for an array of 1', 'same.jpg')
    