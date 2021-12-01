#pip install pyserial
from pyArduino import *

#pip install matplotlib
import matplotlib.pyplot as plt

#pip install pandas
import pandas as pd

#pip install numpy
import numpy as np

ts = 0.1
tf = 10
t = np.arange(0,tf+ts,ts)
N = len(t)

port = 'COM4'
baudRate = 9600
sizeData = 2

y = np.zeros((sizeData,N))

arduino = serialArduino(port,baudRate,sizeData)

arduino.readSerialStart()

for k in range(N) :
	
	start_time = time.time()

	for n in range(sizeData):
		y[n,k] = arduino.rawData[n]

	print(f"Valor 1: {y[0,k]}")
	print(f"Valor 2: {y[1,k]}")

	elapsed_time = time.time() - start_time

	while elapsed_time<ts:
		elapsed_time = time.time() - start_time
arduino.close()
