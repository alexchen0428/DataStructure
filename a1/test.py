#!/usr/bin/python

import sys
reload(sys)
sys.setdefaultencoding('utf-8')

import random
import os
import commands
import time

MAX = 15
INT_MAX = 2**30;
if __name__ == "__main__":
    for cases in range(MAX):
        with open('input{}'.format(cases), 'w') as w:
            n = int(cases**5*50+5)
            w.write(str(n) + '\n')
            for i in range(n):
                w.write(str(random.randint(-INT_MAX, INT_MAX)) + '\n')
        print("Testcase{}".format(cases))

    #os.system("./test.sh")