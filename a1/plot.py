import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.patches import *
import seaborn as sns
n = [5, 5000, 8000, 12000, 20000, 30000, 40000, 50000, int(0.25e7), int(0.5e7), int(1e7), int(1.5e7), int(2.0e7), int(2.5e7), int(3e7)]
label = ['Bubblesort', 'Insertionsort', 'Selectionsort', 'Mergesort', 'Quicksort_extra', 'Quicksort_inplace']
plt.figure(figsize=(10,6))
for i in range(3):
    with open('{}.out'.format(i), 'r') as f:
        data = f.read();
        time = data.split('\n')
        plt.plot(n[:8], time[:-1])
plt.legend(label[:3], loc = 'upper left')
plt.xlabel('Input size')
plt.ylabel('Execution time (s)')
plt.title('$O(n^2)$ sort algorithms')
plt.savefig('012.jpg')
plt.show()

plt.figure(figsize=(10,6))
for i in range(3,6):
    with open('{}.out'.format(i), 'r') as f:
        data = f.read();
        time = data.split('\n')
        nn = n[8:]
        ttime = time[:-1]
        nn.insert(0,0)
        ttime.insert(0,'0.0')
        plt.plot(nn, ttime)
plt.legend(label[3:6], loc='upper left')
plt.xlabel('Input size')
plt.ylabel('Execution time (s)')
plt.title('$O(n\log n)$ sort algorithms')
plt.savefig('345.jpg')
plt.show()

plt.figure(figsize=(10,6))
for i in range(3):
    with open('reverse{}.out'.format(i), 'r') as f:
        data = f.read();
        time = data.split('\n')
        plt.plot(n[:8], time[:-1])
plt.legend(label[:3], loc = 'upper left')
plt.xlabel('Input size')
plt.ylabel('Execution time (s)')
plt.title('$O(n^2)$ Sort algorithms for a descending array')
plt.savefig('reverse012.jpg')
plt.show()
plt.figure(figsize=(10,6))
for i in range(3,6):
    with open('reverse{}.out'.format(i), 'r') as f:
        data = f.read();
        time = data.split('\n')
        nn = n[8:]
        ttime = time[:-1]
        nn.insert(0,0)
        ttime.insert(0,'0.0')
        plt.plot(nn, ttime)
plt.legend(label[3:6], loc='upper left')
plt.xlabel('Input size')
plt.ylabel('Execution time (s)')
plt.title('$O(n\log n)$ sort algorithms')
plt.savefig('reverse345.jpg')
plt.show()

plt.figure(figsize=(10,6))
for i in range(6):
    with open('same{}.out'.format(i), 'r') as f:
        data = f.read();
        time = data.split('\n')
        plt.plot(n[:8], time[:-1])
plt.legend(label, loc = 'upper left')
plt.xlabel('Input size')
plt.ylabel('Execution time (s)')
plt.title('Sort algorithms for an array of 1')
plt.savefig('same.jpg')
plt.show()