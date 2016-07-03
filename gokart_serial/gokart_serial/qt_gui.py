#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function

__author__ = 'Rodrigo Muñoz'

import sys
from PyQt4.QtCore import *
from PyQt4.QtGui import *

class GoKartGUI(QWidget):
   def __init__(self, parent = None):
      super(GoKartGUI, self).__init__(parent)
      layout = QVBoxLayout()
      
      # Steering wheel label
      self.l_stwheel = QLabel('Steering wheel')
      self.l_stwheel.setAlignment(Qt.AlignCenter)
      layout.addWidget(self.l_stwheel)
      # Steering wheel slider
      self.sl_stwheel = QSlider(Qt.Horizontal)
      self.sl_stwheel.setMinimum(-128)
      self.sl_stwheel.setMaximum(127)
      self.sl_stwheel.setValue(0)
      self.sl_stwheel.setTickPosition(QSlider.TicksBelow)
      self.sl_stwheel.setTickInterval(1)
      self.sl_stwheel.valueChanged.connect(self.set_stwheel)
      layout.addWidget(self.sl_stwheel)

      # Brake label
      self.l_brake = QLabel('Brake')
      self.l_brake.setAlignment(Qt.AlignCenter)
      layout.addWidget(self.l_brake)
      # Brake slider
      self.sl_brake = QSlider(Qt.Horizontal)
      self.sl_brake.setMinimum(0)
      self.sl_brake.setMaximum(255)
      self.sl_brake.setValue(0)
      self.sl_brake.setTickPosition(QSlider.TicksBelow)
      self.sl_brake.setTickInterval(1)
      self.sl_brake.valueChanged.connect(self.set_brake)
      layout.addWidget(self.sl_brake)

      # Throttle label
      self.l_throttle = QLabel('Throttle')
      self.l_throttle.setAlignment(Qt.AlignCenter)
      layout.addWidget(self.l_throttle)
      # Throttle slider
      self.sl_throttle = QSlider(Qt.Horizontal)
      self.sl_throttle.setMinimum(0)
      self.sl_throttle.setMaximum(255)
      self.sl_throttle.setValue(0)
      self.sl_throttle.setTickPosition(QSlider.TicksBelow)
      self.sl_throttle.setTickInterval(1)
      self.sl_throttle.valueChanged.connect(self.set_throttle)
      layout.addWidget(self.sl_throttle)
      # Set layout and tittle
      self.setLayout(layout)
      self.setWindowTitle('GoKartGUI')

   def set_stwheel(self):
      value = self.sl_stwheel.value()
      print('Steering wheel: {}'.format(value))


   def set_brake(self):
      value = self.sl_brake.value()
      print('Brake: {}'.format(value))


   def set_throttle(self):
      value = self.sl_throttle.value()
      print('Throttle: {}'.format(value))

   @staticmethod
   def run():
      app = QApplication(sys.argv)
      ex = GoKartGUI()
      ex.show()
      sys.exit(app.exec_())
      
