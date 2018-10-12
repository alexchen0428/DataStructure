#!/usr/bin/python

import sys

import random
import os
import time

MAX = 10
INT_MAX = 2**31;
size = [1, 5, 5000, 8000, 12000, 20000, 30000, 40000, 50000, 60000]
if __name__ == "__main__":
    for cases in range(MAX):
        filename = '../inputs/{}.in'.format(cases)
        dirname = os.path.dirname(filename)
        if not os.path.exists(dirname):
            os.makedirs(dirname)
        with open(filename, 'w') as w:
            n = size[cases]
            w.write(str(n) + '\n')
            for i in range(n):
                w.write(str(random.randint(-INT_MAX, INT_MAX-1)) + '\n')
        print("Cases{}".format(cases))