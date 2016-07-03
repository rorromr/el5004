#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function, division

__author__ = 'Rodrigo Muñoz'

from gokart_serial import GoKartSerial
import logging
import time

class Color:
    HEADER = '\033[95m'
    BLUE = '\033[94m'
    GREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

def main():
    gokart = GoKartSerial()
    while True:

        data = gokart.read(readline=True)
        print(Color.GREEN + data + Color.ENDC,end='')
        gokart.set_stwheel(25)
        gokart.set_brake(25)
        time.sleep(0.1)

if __name__ == '__main__':
    main()
