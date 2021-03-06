#!/usr/bin/python

import sys
reload(sys)
sys.setdefaultencoding('utf-8')

import random
import os
import commands
import time

MAX = 15
INT_MAX = 2**31;
size = [5, 5000, 8000, 12000, 20000, 30000, 40000, 50000, int(0.25e7), int(0.5e7), int(1e7), int(1.5e7), int(2.0e7), int(2.5e7), int(3e7)]
if __name__ == "__main__":
    for cases in range(MAX):
        for k in range(5):
            with open('input{}{}'.format(cases,k), 'w') as w:
                n = size[cases]
                w.write(str(n) + '\n')
                for i in range(n):
                    w.write(str(random.randint(-INT_MAX, INT_MAX-1)) + '\n')
        print("Testcase{}".format(cases))