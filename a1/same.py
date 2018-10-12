#!/usr/bin/python

import sys
reload(sys)
sys.setdefaultencoding('utf-8')

import random
import os
import commands
import time

MAX = 8
INT_MAX = 2**31;
size = [5, 5000, 8000, 12000, 20000, 30000, 40000, 50000]
if __name__ == "__main__":
    for cases in range(MAX):
        with open('input{}'.format(cases), 'w') as w:
            n = size[cases]
            w.write(str(n) + '\n')
            for i in range(n):
                w.write('1\n')
        print("Testcase{}".format(cases))
    os.system('./same.sh')