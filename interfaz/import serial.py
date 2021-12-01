import serial
from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QDialog, QApplication
from PyQt5.uic import loadUi

ser = serial.Serial ('COM4', baudrate = 9600, timeout = 1)

while 1:
    
    arduinoData = ser.readline()
    angulo=arduinoData.split(b',')
    angulo1=angulo[0]
    print(angulo1)
   