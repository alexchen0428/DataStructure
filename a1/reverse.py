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
        with open('input{}'.format(cases), 'w') as w:
            n = size[cases]
            w.write(str(n) + '\n')
            for i in range(n):
                w.write(str(INT_MAX-1-i) + '\n')
        print("Testcase{}".format(cases))
    os.system('./reverse.sh')