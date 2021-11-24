EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Module:Arduino_Nano_Every Microcontrolador
U 1 1 617F2D30
P 5050 4500
F 0 "Microcontrolador" H 5050 3319 50  0000 C CNN
F 1 "Arduino_Nano" H 5050 3410 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 5050 4500 50  0001 C CIN
F 3 "https://content.arduino.cc/assets/NANOEveryV3.0_sch.pdf" H 5050 4500 50  0001 C CNN
	1    5050 4500
	-1   0    0    1   
$EndComp
$Comp
L Sensor_Motion:MPU-6050 IMU2
U 1 1 617F5660
P 2950 2900
F 0 "IMU2" H 2950 2111 50  0000 C CNN
F 1 "MPU-6050" H 2950 2020 50  0000 C CNN
F 2 "Sensor_Motion:InvenSense_QFN-24_4x4mm_P0.5mm" H 2950 2100 50  0001 C CNN
F 3 "https://store.invensense.com/datasheets/invensense/MPU-6050_DataSheet_V3%204.pdf" H 2950 2750 50  0001 C CNN
	1    2950 2900
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Motion:MPU-6050 IMU1
U 1 1 617F74E6
P 2950 5050
F 0 "IMU1" H 2950 4261 50  0000 C CNN
F 1 "MPU-6050" H 2950 4170 50  0000 C CNN
F 2 "Sensor_Motion:InvenSense_QFN-24_4x4mm_P0.5mm" H 2950 4250 50  0001 C CNN
F 3 "https://store.invensense.com/datasheets/invensense/MPU-6050_DataSheet_V3%204.pdf" H 2950 4900 50  0001 C CNN
	1    2950 5050
	1    0    0    -1  
$EndComp
$Comp
L Display_Character:RC1602A Display
U 1 1 617F9734
P 6800 4550
F 0 "Display" H 6800 5431 50  0000 C CNN
F 1 "RC1602A" H 6800 5340 50  0000 C CNN
F 2 "Display:RC1602A" H 6900 3750 50  0001 C CNN
F 3 "http://www.raystar-optronics.com/down.php?ProID=18" H 6900 4450 50  0001 C CNN
	1    6800 4550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 618037D8
P 6800 5250
F 0 "#PWR?" H 6800 5000 50  0001 C CNN
F 1 "GND" H 6805 5077 50  0000 C CNN
F 2 "" H 6800 5250 50  0001 C CNN
F 3 "" H 6800 5250 50  0001 C CNN
	1    6800 5250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6180D940
P 5500 3450
F 0 "#PWR?" H 5500 3200 50  0001 C CNN
F 1 "GND" H 5505 3277 50  0000 C CNN
F 2 "" H 5500 3450 50  0001 C CNN
F 3 "" H 5500 3450 50  0001 C CNN
	1    5500 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 3500 5050 3450
Wire Wire Line
	5050 3450 5500 3450
Wire Wire Line
	4850 5800 4850 5500
$Comp
L Device:R R3
U 1 1 618144E0
P 6150 5800
F 0 "R3" V 5943 5800 50  0000 C CNN
F 1 "220 Ω" V 6034 5800 50  0000 C CNN
F 2 "" V 6080 5800 50  0001 C CNN
F 3 "~" H 6150 5800 50  0001 C CNN
F 4 "R" H 6150 5800 50  0001 C CNN "Spice_Primitive"
F 5 "220" H 6150 5800 50  0001 C CNN "Spice_Model"
F 6 "Y" H 6150 5800 50  0001 C CNN "Spice_Netlist_Enabled"
	1    6150 5800
	0    1    1    0   
$EndComp
Wire Wire Line
	6050 5000 6050 5050
Wire Wire Line
	5550 5000 6050 5000
Wire Wire Line
	6050 5050 6400 5050
Wire Wire Line
	5550 4900 6050 4900
Wire Wire Line
	6050 4900 6050 4950
Wire Wire Line
	6050 4950 6400 4950
Wire Wire Line
	5550 4800 6050 4800
Wire Wire Line
	6050 4800 6050 4850
Wire Wire Line
	6050 4850 6400 4850
Wire Wire Line
	5550 4700 6050 4700
Wire Wire Line
	6050 4700 6050 4750
Wire Wire Line
	6050 4750 6400 4750
Wire Wire Line
	5550 4600 6050 4600
Wire Wire Line
	6050 4600 6050 4250
Wire Wire Line
	6050 4250 6400 4250
Wire Wire Line
	5550 4500 6000 4500
Wire Wire Line
	6000 4500 6000 4050
Wire Wire Line
	6000 4050 6400 4050
$Comp
L power:GND #PWR?
U 1 1 61819932
P 6250 4100
F 0 "#PWR?" H 6250 3850 50  0001 C CNN
F 1 "GND" H 6255 3927 50  0000 C CNN
F 2 "" H 6250 4100 50  0001 C CNN
F 3 "" H 6250 4100 50  0001 C CNN
	1    6250 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 4150 6400 4100
Wire Wire Line
	6400 4100 6250 4100
Wire Wire Line
	6300 5800 7500 5800
Wire Wire Line
	7500 5800 7500 4750
Wire Wire Line
	7500 4750 7200 4750
$Comp
L power:GND #PWR?
U 1 1 6181C8E4
P 7300 4950
F 0 "#PWR?" H 7300 4700 50  0001 C CNN
F 1 "GND" H 7305 4777 50  0000 C CNN
F 2 "" H 7300 4950 50  0001 C CNN
F 3 "" H 7300 4950 50  0001 C CNN
	1    7300 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 4850 7300 4850
Wire Wire Line
	7300 4850 7300 4950
$Comp
L power:GND #PWR?
U 1 1 6181DBBC
P 7300 4400
F 0 "#PWR?" H 7300 4150 50  0001 C CNN
F 1 "GND" H 7305 4227 50  0000 C CNN
F 2 "" H 7300 4400 50  0001 C CNN
F 3 "" H 7300 4400 50  0001 C CNN
	1    7300 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 4350 7300 4350
Wire Wire Line
	7300 4350 7300 4400
$Comp
L Switch:SW_Push button+
U 1 1 61822DB1
P 6450 3400
F 0 "button+" H 6450 3685 50  0000 C CNN
F 1 "SW_Push" H 6450 3594 50  0000 C CNN
F 2 "" H 6450 3600 50  0001 C CNN
F 3 "~" H 6450 3600 50  0001 C CNN
	1    6450 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 4400 5950 4400
Wire Wire Line
	5950 4400 5950 3400
Wire Wire Line
	5950 3400 6250 3400
Wire Wire Line
	5550 4300 5800 4300
Wire Wire Line
	5800 4300 5800 3000
$Comp
L power:GND #PWR?
U 1 1 6182F496
P 7300 3200
F 0 "#PWR?" H 7300 2950 50  0001 C CNN
F 1 "GND" H 7305 3027 50  0000 C CNN
F 2 "" H 7300 3200 50  0001 C CNN
F 3 "" H 7300 3200 50  0001 C CNN
	1    7300 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 3000 7300 3200
Wire Wire Line
	7200 3400 7200 3000
Connection ~ 7200 3000
Wire Wire Line
	7200 3000 7300 3000
Wire Wire Line
	2950 3600 2950 3650
Wire Wire Line
	2950 3650 3800 3650
Wire Wire Line
	3800 3650 3800 4650
Wire Wire Line
	3800 5800 2950 5800
Wire Wire Line
	2950 5800 2950 5750
Wire Wire Line
	3950 4650 3950 4800
Wire Wire Line
	3800 4650 3950 4650
Connection ~ 3800 4650
Wire Wire Line
	3800 4650 3800 5800
$Comp
L power:GND #PWR?
U 1 1 618A2BF5
P 3950 4800
F 0 "#PWR?" H 3950 4550 50  0001 C CNN
F 1 "GND" H 3955 4627 50  0000 C CNN
F 2 "" H 3950 4800 50  0001 C CNN
F 3 "" H 3950 4800 50  0001 C CNN
	1    3950 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 4850 1850 4850
Wire Wire Line
	1850 4850 1850 2700
Wire Wire Line
	1850 2700 2250 2700
Wire Wire Line
	2250 4750 2050 4750
Wire Wire Line
	2050 4750 2050 2600
Wire Wire Line
	2050 2600 2250 2600
Wire Wire Line
	2050 2600 2050 2000
Wire Wire Line
	2050 2000 4350 2000
Wire Wire Line
	4350 2000 4350 4100
Wire Wire Line
	4350 4100 4550 4100
Connection ~ 2050 2600
Wire Wire Line
	1850 2700 1850 1750
Wire Wire Line
	1850 1750 4450 1750
Wire Wire Line
	4450 1750 4450 4000
Wire Wire Line
	4450 4000 4550 4000
Connection ~ 1850 2700
$Comp
L Device:Battery_Cell Batería
U 1 1 618CD8CE
P 5050 6500
F 0 "Batería" H 5168 6596 50  0000 L CNN
F 1 "3.7 V" H 5168 6505 50  0000 L CNN
F 2 "" V 5050 6560 50  0001 C CNN
F 3 "~" V 5050 6560 50  0001 C CNN
	1    5050 6500
	1    0    0    -1  
$EndComp
Connection ~ 4850 5800
Text Label 8250 7650 0    50   ~ 0
01-11-21
$Comp
L Step~up~MT3608:MT3608 Step_up
U 1 1 61966294
P 4100 6450
F 0 "Step_up" H 4050 6765 50  0000 C CNN
F 1 "MT3608" H 4050 6674 50  0000 C CNN
F 2 "" H 4100 6450 50  0001 C CNN
F 3 "" H 4100 6450 50  0001 C CNN
	1    4100 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 6300 4550 6300
Wire Wire Line
	4550 6300 4550 6400
Wire Wire Line
	5050 6600 4550 6600
Wire Wire Line
	4550 6600 4550 6500
Wire Wire Line
	3550 6400 3500 6400
Wire Wire Line
	3500 6400 3500 5900
Wire Wire Line
	3500 5900 4650 5900
Wire Wire Line
	4650 5900 4650 5800
Wire Wire Line
	4650 5800 4850 5800
Wire Wire Line
	3550 6500 3400 6500
Wire Wire Line
	3400 6500 3400 6600
$Comp
L power:GND #PWR?
U 1 1 6198A49F
P 3400 6600
F 0 "#PWR?" H 3400 6350 50  0001 C CNN
F 1 "GND" H 3405 6427 50  0000 C CNN
F 2 "" H 3400 6600 50  0001 C CNN
F 3 "" H 3400 6600 50  0001 C CNN
	1    3400 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 3850 6800 3800
Wire Wire Line
	6800 3800 7500 3800
Text Label 7300 3800 0    50   ~ 0
+5V
Wire Wire Line
	4850 5800 6000 5800
Wire Wire Line
	3050 2200 3500 2200
Wire Wire Line
	3050 4350 3400 4350
Text Label 3250 2200 0    50   ~ 0
+5V
Text Label 3200 4350 0    50   ~ 0
+5V
$Comp
L KV-040:encoder_rotacional KV-040
U 1 1 61965336
P 6900 1350
F 0 "KV-040" H 6958 1915 50  0000 C CNN
F 1 "encoder_rotacional" H 6958 1824 50  0000 C CNN
F 2 "" H 6850 1350 50  0001 C CNN
F 3 "" H 6850 1350 50  0001 C CNN
	1    6900 1350
	-1   0    0    -1  
$EndComp
$Comp
L Switch:SW_Push button-
U 1 1 61821C08
P 6450 3000
F 0 "button-" H 6450 3285 50  0000 C CNN
F 1 "SW_Push" H 6450 3194 50  0000 C CNN
F 2 "" H 6450 3200 50  0001 C CNN
F 3 "~" H 6450 3200 50  0001 C CNN
	1    6450 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 3000 6300 3000
Wire Wire Line
	5550 4200 5750 4200
Wire Wire Line
	5750 4200 5750 1250
Wire Wire Line
	5750 1250 6400 1250
Wire Wire Line
	5550 4000 5700 4000
Wire Wire Line
	5700 4000 5700 1150
Wire Wire Line
	5700 1150 6400 1150
Wire Wire Line
	5550 3900 5650 3900
Wire Wire Line
	5650 1050 6400 1050
Wire Wire Line
	5650 1050 5650 3900
Wire Wire Line
	6400 1450 6250 1450
Wire Wire Line
	6250 1450 6250 1700
$Comp
L power:GND #PWR?
U 1 1 61A25374
P 6250 1700
F 0 "#PWR?" H 6250 1450 50  0001 C CNN
F 1 "GND" H 6255 1527 50  0000 C CNN
F 2 "" H 6250 1700 50  0001 C CNN
F 3 "" H 6250 1700 50  0001 C CNN
	1    6250 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 1350 5900 1350
Wire Wire Line
	5900 1350 5900 2100
Wire Wire Line
	5900 2100 6550 2100
Text Label 6400 2100 0    50   ~ 0
+5V
Wire Wire Line
	6650 3000 7200 3000
Wire Wire Line
	6650 3400 7200 3400
$EndSCHEMATC
