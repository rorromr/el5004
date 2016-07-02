#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function, division

__author__ = 'Rodrigo Muñoz'

import struct

class Message(object):
    """Base class for messages"""
    def serialize(self, buff):
        pass
    
    def deserialize(self, buff):
    	pass

    def __str__(self):
        return ''

class MessageException(Exception):
    """Base exception type for errors"""
    pass

class DeserializationError(MessageException):
    """Message deserialization error"""
    pass

class SerializationError(MessageException):
    """Message serialization error"""
    pass

class GoKartCommand(Message):
    # Struct type
    # Little endian
    # GoKartCommand [int8_t, uint8_t, uint8_t, uint8_t] 
    _struct = struct.Struct('<bBBB')

    def __init__(self):
        self.stwheel = 0
        self.brake = 0
        self.throttle = 0
        self.emergency = 0

    def serialize(self, buff):
        try:
            buff.write(GoKartCommand._struct.pack(self.stwheel, self.brake, self.throttle, self.emergency))
        except struct.error as se:
            raise SerializationError('Error in serialization %s' % (self.__str__))
        
    def deserialize(self, buff):
        pass

    def __str__(self):
        return 'stwheel: {:d}\nbrake: {:d}\nthrottle: {:d}\nemergency: {}'.format(self.stwheel, self.brake, self.throttle, bool(self.emergency))

def to_hex(data):
    return ":".join("{:02x}".format(ord(c)) for c in data)

def test():
    """Basic test"""
    import StringIO
    buff = StringIO.StringIO()
    cmd = GoKartCommand()
    cmd.stwheel = -10
    cmd.brake = 8
    cmd.throttle = 6
    cmd.emergency = 0
    cmd.serialize(buff)
    print(to_hex(buff.getvalue()))
    print(cmd)
    

if __name__ == '__main__':
    test()
