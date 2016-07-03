#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function, division

__author__ = 'Rodrigo Muñoz'

from serial import Serial, SerialException
import StringIO
from array import array
from threading import Lock, Thread
import time
import sys
from .message import GoKartCommand, to_hex

class GoKartSerial(object):
    """GoKart main class"""
    def __init__(self, port='/dev/ttyUSB0', baudrate=9600):
        self.port_name = port
        self.baudrate = baudrate
        self.cmd = GoKartCommand()
        self.serial_mutex = Lock()
        self.ser = None
        try:
            self.ser = Serial(port)
            self.ser.setTimeout(None)
        except SerialException:
           raise SerialOpenError(port, baudrate)

    def __del__(self):
        """
        Destructor calls GoKartSerial.close
        """
        self.close()

    def close(self):
        """
        Close the serial port.
        """
        if self.ser:
            self.ser.flushInput()
            self.ser.flushOutput()
            self.ser.close()

    def __write_serial(self, data):
        """
        Write in the serial port.
        """
        #print(self.cmd)
        #print("Hex: {}".format(to_hex(data)))
        self.ser.flushInput()
        self.ser.flushOutput()
        self.ser.write(data)

    def read(self, length=1, readline=False):
        try: 
            if readline:
                return self.ser.readline()
            else:
                return self.ser.read(length)
        except SerialException:
           print('Error reading')
           return ''



    def __send_command(self):
        """
        Serialize and send command
        """
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
        """
        Set brake, range 0-255
        """
        self.cmd.brake = val
        self.__send_command()

    def set_stwheel(self, val=0):
        """
        Set steering wheel, range -128-127
        """
        self.cmd.stwheel = val
        self.__send_command()

    def set_throttle(self, val=0):
        """
        Set throtle, range 0-255
        """
        self.cmd.throttle = val
        self.__send_command()

    def set_emergency(self, state = True):
        """
        Set emergency state
        """
        self.cmd.emergency = int(state)
        self.__send_command()

class SerialOpenError(Exception):
    def __init__(self, port, baud):
        Exception.__init__(self)
        self.message = "Cannot open port '%s' at %d bps" % (port, baud)
        self.port = port
        self.baud = baud
    
    def __str__(self):
        return self.message

class GoKartSerialConsole(GoKartSerial):
    """GoKartSerialConsole"""
    def __init__(self, port='/dev/ttyUSB0', baudrate=9600, rate = 10):
        super(GoKartSerialConsole, self).__init__(port, baudrate)
        self.rate = rate
        self.running = True
        Thread(target=self.run).start()

    def stop(self):
        self.running = False

    def run(self):
        while self.running:
            data = self.read(readline=True)
            print(data, end='')
            time.sleep(1.0/self.rate)
        

