#!/usr/bin/env python
# -*- coding: utf-8 -*-

__author__ = 'Rodrigo Muñoz'

from pyqtgraph.Qt import QtGui, QtCore
import pyqtgraph as pg

import collections
import random
import time
import math
import numpy as np

class DynamicPlotter():

    def __init__(self, app, update_fcn, sampleinterval=0.1, timewindow=10., size=(600,350), title='plot'):
        # Data stuff
        self._interval = int(sampleinterval*1000)
        self._bufsize = int(timewindow/sampleinterval)
        self.databuffer = collections.deque([0.0]*self._bufsize, self._bufsize)
        self.x = np.linspace(-timewindow, 0.0, self._bufsize)
        self.y = np.zeros(self._bufsize, dtype=np.float)
        # PyQtGraph stuff
        self.app = app
        self.plt = pg.plot(title=title)
        self.plt.resize(*size)
        self.plt.showGrid(x=True, y=True)
        self.plt.addLegend()
        self.curve = self.plt.plot(self.x, self.y, pen=(255,0,0), name=title)
        # QTimer
        self.update_fcn = update_fcn
        self.timer = QtCore.QTimer()
        self.timer.timeout.connect(self.updateplot)
        self.timer.start(self._interval)

    def xlabel(self, label='x', units=''):
        self.plt.setLabel('bottom', label, units)

    def ylabel(self, label='y', units=''):
        self.plt.setLabel('left', label, units)

    def updateplot(self):
        self.databuffer.append( self.update_fcn() )
        self.y[:] = self.databuffer
        self.curve.setData(self.x, self.y)
        self.app.processEvents()

def getdata():
    frequency = 0.5
    noise = random.normalvariate(0., 1.)
    new = 10.*math.sin(time.time()*frequency*2*math.pi) + noise
    return new

if __name__ == '__main__':
    app = QtGui.QApplication([])
    m = DynamicPlotter(app, getdata, sampleinterval=0.05, timewindow=10.)
    m.xlabel('time','s')
    m.ylabel('Torque','%')
    app.exec_()

