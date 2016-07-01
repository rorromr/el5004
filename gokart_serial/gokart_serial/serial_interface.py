#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function, division

__author__ = 'Rodrigo Muñoz'

import serial

class GoKartSerial(object):
    """GoKart main class"""
    def __init__(self, port='/dev/ttyUSB0', baud=115200):
        self.port = port
        self.baud = baud

    def send_command(self, cmd):
        """Send command"""
        pass

    def set_brake(self, val=0):
        """Set brake, range 0-255"""
        pass

    def set_stwheel(self, val=0):
        """Set steering wheel, range -128-127"""
        pass

    def set_throttle(self, val=0):
        """Set throtle, range 0-255"""
        pass

def main():
    """Basic test"""
    print('test')

if __name__ == '__main__':
    main()
