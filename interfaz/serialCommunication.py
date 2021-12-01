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

for k in range(N):
     
     start_time = time.time()
     
     for n in range(sizeData):
          y[n,k] = arduino.rawData[n]

     print(f"Flexion {y[0,k]}")
     print(f"Dolor_flexion {y[1,k]}")
     print(f"Extension {y[2,k]}")
     print (f"Dolor_extension {y[3,k]}")
          
     elapsed_time = time.time() - start_time
     time.sleep(ts-elapsed_time)
     
arduino.close()
