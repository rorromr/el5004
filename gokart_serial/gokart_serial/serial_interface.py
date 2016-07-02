#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function, division

__author__ = 'Rodrigo Muñoz'

import serial
import StringIO
from array import array
from threading import Lock
from .message import GoKartCommand, to_hex

class GoKartSerial(object):
    """GoKart main class"""
    def __init__(self, port='/dev/ttyUSB0', baud=115200):
        self.serial_mutex = Lock()
        self.port = port
        self.baud = baud
        self.cmd = GoKartCommand()

    def __write_serial(self, data):
        print(self.cmd)
        print("Hex: {}".format(to_hex(data)))

    def __send_command(self):
        """Send command"""
        buff = StringIO.StringIO()
        try:
            self.cmd.serialize(buff)
        except Exception, e:
            print(e.message)
            return
        base_cmd_int = bytearray(buff.getvalue())
        checksum = 255 - ( sum(base_cmd_int) % 256 )
        # Packet: FF  FF  BASE_CMD  CHECKSUM
        packet = bytearray([0xFF, 0xFF]) + base_cmd_int + bytearray([checksum])
        packet_str = array('B', packet).tostring()
        with self.serial_mutex:
            self.__write_serial(packet_str)
        
    def set_brake(self, val=0):
        """Set brake, range 0-255"""
        self.cmd.brake = val
        self.__send_command()

    def set_stwheel(self, val=0):
        """Set steering wheel, range -128-127"""
        self.cmd.stwheel = val
        self.__send_command()

    def set_throttle(self, val=0):
        """Set throtle, range 0-255"""
        self.cmd.throttle = val
        self.__send_command()

    def set_emergency(self, state = True):
        """Set emergency state"""
        self.cmd.emergency = int(state)
        self.__send_command()


