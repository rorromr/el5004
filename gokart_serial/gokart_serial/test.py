#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function, division

__author__ = 'Rodrigo Muñoz'

from gokart_serial import GoKartSerial
import logging
import time

def main():
    gokart = GoKartSerial()
    gokart.set_brake(125)

if __name__ == '__main__':
    main()
