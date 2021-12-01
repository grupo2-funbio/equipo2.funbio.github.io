import sys
from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QDialog, QApplication
from PyQt5.uic import loadUi
#pip install pyserial
from pyArduino import *

#pip install matplotlib
import matplotlib.pyplot as plt

#pip install pandas
#pip install openpyxl
import pandas as pd

#pip install numpy
import numpy as np

ts = 0.1
tf = 30
t = np.arange(0,tf+ts,ts)
N = len(t)

port = 'COM4' 
baudRate = 9600 
sizeData = 4

y  = np.zeros((sizeData,N))

arduino = serialArduino(port,baudRate,sizeData)

arduino.readSerialStart()


class Login(QDialog):
    def __init__(self):
        super(Login,self).__init__()
        loadUi("login.ui",self)
        self.botonlogin.clicked.connect(self.loginfunction)
        self.createaccbutton.clicked.connect(self.gotocreate)

    def loginfunction(self):
        registro=CreateAcb()
        widget.addWidget(registro)
        widget.setCurrentIndex(widget.currentIndex()+1)

    def gotocreate(self):
        createacc=CreateAcc()
        widget.addWidget(createacc)
        widget.setCurrentIndex(widget.currentIndex()+1)
        

class CreateAcc(QDialog):
    def __init__(self):
        super(CreateAcc,self).__init__()
        loadUi("createacc.ui",self)
        self.signupbutton.clicked.connect(self.gotomenu)
    def gotomenu(self):
        menu=CreateAdd()
        widget.addWidget(menu)
        widget.setCurrentIndex(widget.currentIndex()+1)

class CreateAcb(QDialog):
    def __init__(self):
        super(CreateAcb,self).__init__()
        loadUi("registro.ui",self)
        self.importboton.clicked.connect(self.gotodatos)
    def gotodatos(self):
        datos=CreateAbb()
        widget.addWidget(datos)
        widget.setCurrentIndex(widget.currentIndex()+1)

class CreateAbb(QDialog):
    def __init__(self):
        super(CreateAbb,self).__init__()
        loadUi("datos.ui",self)
        self.botonimp.clicked.connect(self.on_click)
        self.botonretorn.clicked.connect(self.reinicio)

    def on_click(self):
        for k in range(N):
     
         start_time = time.time()
     
         for n in range(sizeData):
              y[n,k] = arduino.rawData[n]

         self.cuadro1.setText(str(f"{y[0,k]}"))
         self.cuadro2.setText(str(f"{y[1,k]}"))
         self.cuadro3.setText(str(f"{y[2,k]}"))
         self.cuadro4.setText(str(f"{y[3,k]}"))
         #elapsed_time = time.time() - start_time
         #time.sleep(ts-elapsed_time)
     
        # arduino.close()
         

    def reinicio(self):
        y=0
        self.cuadro1.setText(str(y))
        self.cuadro2.setText(str(y))
        self.cuadro3.setText(str(y))
        self.cuadro4.setText(str(y))

class CreateAdd(QDialog):
    def __init__(self):
        super(CreateAdd,self).__init__()
        loadUi("login.ui",self)
        self.botonlogin.clicked.connect(self.loginfunction)
        self.createaccbutton.clicked.connect(self.gotocreate)
        
    def loginfunction(self):
        registro=CreateAcb()
        widget.addWidget(registro)
        widget.setCurrentIndex(widget.currentIndex()+1)

    def gotocreate(self):
        createacc=CreateAcc()
        widget.addWidget(createacc)
        widget.setCurrentIndex(widget.currentIndex()+1)


        

app=QApplication(sys.argv)
mainwindow=Login()
widget=QtWidgets.QStackedWidget()
widget.addWidget(mainwindow)
widget.setFixedWidth(480)
widget.setFixedHeight(620)
widget.show()
app.exec_()