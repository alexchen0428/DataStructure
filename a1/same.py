#!/usr/bin/python

import sys
reload(sys)
sys.setdefaultencoding('utf-8')

import random
import os
import commands
import time

if __name__ == "__main__":
    n = 20000000
    with open('input_', 'w') as w:
        w.write(str(n)+'\n')
        for i in range(n):
            w.write('1\n')