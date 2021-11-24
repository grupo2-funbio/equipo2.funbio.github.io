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
	6000 5800 5800 5800
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
Wire Wire Line
	6800 3850 6800 3800
Wire Wire Line
	6800 3800 7600 3800
Wire Wire Line
	7600 3800 7600 6000
Wire Wire Line
	7600 6000 6000 6000
Wire Wire Line
	6000 6000 6000 5800
Connection ~ 6000 5800
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
Wire Wire Line
	5800 3000 6250 3000
Connection ~ 6250 3000
Wire Wire Line
	6250 3000 6300 3000
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
$Comp
L Device:R R5
U 1 1 6182FB36
P 6950 3000
F 0 "R5" V 6743 3000 50  0000 C CNN
F 1 "10 KΩ" V 6834 3000 50  0000 C CNN
F 2 "" V 6880 3000 50  0001 C CNN
F 3 "~" H 6950 3000 50  0001 C CNN
	1    6950 3000
	0    1    1    0   
$EndComp
$Comp
L Device:R R4
U 1 1 618302E3
P 6950 3400
F 0 "R4" V 6743 3400 50  0000 C CNN
F 1 "10 KΩ" V 6834 3400 50  0000 C CNN
F 2 "" V 6880 3400 50  0001 C CNN
F 3 "~" H 6950 3400 50  0001 C CNN
	1    6950 3400
	0    1    1    0   
$EndComp
Wire Wire Line
	6650 3000 6800 3000
Wire Wire Line
	6650 3400 6800 3400
Wire Wire Line
	7100 3000 7200 3000
Wire Wire Line
	7300 3000 7300 3200
Wire Wire Line
	7100 3400 7200 3400
Wire Wire Line
	7200 3400 7200 3000
Connection ~ 7200 3000
Wire Wire Line
	7200 3000 7300 3000
$Comp
L Device:Rotary_Encoder_Switch encoder_rotatorio
U 1 1 617FBFFF
P 5900 1100
F 0 "encoder_rotatorio" H 5900 1467 50  0000 C CNN
F 1 "KY-040" H 5900 1376 50  0000 C CNN
F 2 "" H 5750 1260 50  0001 C CNN
F 3 "~" H 5900 1360 50  0001 C CNN
	1    5900 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 4200 5750 4200
Wire Wire Line
	5750 4200 5750 2650
Wire Wire Line
	5750 2650 6300 2650
Wire Wire Line
	5600 1100 5500 1100
Wire Wire Line
	5500 1100 5500 1500
Wire Wire Line
	5500 1500 6900 1500
Wire Wire Line
	6900 1500 6900 1350
Wire Wire Line
	6900 1200 6200 1200
Wire Wire Line
	5550 1200 5600 1200
Wire Wire Line
	7900 1650 7900 6250
Wire Wire Line
	7900 6250 5800 6250
Wire Wire Line
	5800 6250 5800 5800
Connection ~ 5800 5800
Wire Wire Line
	5800 5800 5500 5800
$Comp
L power:GND #PWR?
U 1 1 6185E567
P 7150 1400
F 0 "#PWR?" H 7150 1150 50  0001 C CNN
F 1 "GND" H 7155 1227 50  0000 C CNN
F 2 "" H 7150 1400 50  0001 C CNN
F 3 "" H 7150 1400 50  0001 C CNN
	1    7150 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 1350 7150 1350
Wire Wire Line
	7150 1350 7150 1400
Connection ~ 6900 1350
Wire Wire Line
	6900 1350 6900 1200
Wire Wire Line
	7900 1650 7350 1650
Wire Wire Line
	7350 1650 7350 1950
Wire Wire Line
	7350 1950 7000 1950
Wire Wire Line
	5550 1200 5550 1950
Wire Wire Line
	5600 1000 5300 1000
Wire Wire Line
	5300 1000 5300 2200
Wire Wire Line
	5300 2200 5650 2200
Wire Wire Line
	7350 2200 7350 1950
Connection ~ 7350 1950
Wire Wire Line
	5700 1950 5700 4000
Wire Wire Line
	5700 4000 5550 4000
Connection ~ 5700 1950
Wire Wire Line
	5700 1950 5550 1950
Wire Wire Line
	5550 3900 5650 3900
Wire Wire Line
	5650 3900 5650 2200
Connection ~ 5650 2200
Wire Wire Line
	5650 2200 6700 2200
$Comp
L Device:R R8
U 1 1 618909D5
P 6850 1950
F 0 "R8" V 6643 1950 50  0000 C CNN
F 1 "10 KΩ" V 6734 1950 50  0000 C CNN
F 2 "" V 6780 1950 50  0001 C CNN
F 3 "~" H 6850 1950 50  0001 C CNN
	1    6850 1950
	0    1    1    0   
$EndComp
Wire Wire Line
	6700 1950 5700 1950
Wire Wire Line
	7000 2200 7350 2200
$Comp
L Device:R R7
U 1 1 6189120D
P 6850 2200
F 0 "R7" V 7050 2200 50  0000 C CNN
F 1 "10 KΩ" V 6950 2200 50  0000 C CNN
F 2 "" V 6780 2200 50  0001 C CNN
F 3 "~" H 6850 2200 50  0001 C CNN
	1    6850 2200
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push buttonok
U 1 1 61893181
P 6500 2650
F 0 "buttonok" H 6500 2935 50  0000 C CNN
F 1 "SW_Push" H 6500 2844 50  0000 C CNN
F 2 "" H 6500 2850 50  0001 C CNN
F 3 "~" H 6500 2850 50  0001 C CNN
	1    6500 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 2650 7200 3000
Wire Wire Line
	6700 2650 6850 2650
$Comp
L Device:R R6
U 1 1 61898DA4
P 7000 2650
F 0 "R6" V 6793 2650 50  0000 C CNN
F 1 "10 KΩ" V 6884 2650 50  0000 C CNN
F 2 "" V 6930 2650 50  0001 C CNN
F 3 "~" H 7000 2650 50  0001 C CNN
	1    7000 2650
	0    1    1    0   
$EndComp
Wire Wire Line
	7150 2650 7200 2650
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
	2250 2800 2150 2800
Wire Wire Line
	2150 2800 2150 4050
Wire Wire Line
	2150 4050 3050 4050
Wire Wire Line
	3050 4050 3050 4350
Wire Wire Line
	2150 4050 1600 4050
Wire Wire Line
	1600 4050 1600 7500
Wire Wire Line
	1600 7500 5500 7500
Wire Wire Line
	5500 7500 5500 5800
Connection ~ 2150 4050
Connection ~ 5500 5800
Wire Wire Line
	5500 5800 4850 5800
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
P 2100 6700
F 0 "Batería" H 2218 6796 50  0000 L CNN
F 1 "3.7 V" H 2218 6705 50  0000 L CNN
F 2 "" V 2100 6760 50  0001 C CNN
F 3 "~" V 2100 6760 50  0001 C CNN
	1    2100 6700
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Switching:MT3608 Step-up
U 1 1 618CECEB
P 4050 6700
F 0 "Step-up" H 4050 7067 50  0000 C CNN
F 1 "MT3608" H 4050 6976 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 4100 6450 50  0001 L CIN
F 3 "https://www.olimex.com/Products/Breadboarding/BB-PWR-3608/resources/MT3608.pdf" H 3800 7150 50  0001 C CNN
	1    4050 6700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 618E0638
P 2100 6800
F 0 "#PWR?" H 2100 6550 50  0001 C CNN
F 1 "GND" H 2105 6627 50  0000 C CNN
F 2 "" H 2100 6800 50  0001 C CNN
F 3 "" H 2100 6800 50  0001 C CNN
	1    2100 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 6500 2100 6450
Wire Wire Line
	2100 6450 2800 6450
Wire Wire Line
	2800 6450 2800 6700
Wire Wire Line
	2800 6450 2800 6200
Wire Wire Line
	2800 6200 3500 6200
Wire Wire Line
	4450 6200 4450 6600
Wire Wire Line
	4450 6600 4350 6600
Connection ~ 2800 6450
Wire Wire Line
	3750 6600 3500 6600
Wire Wire Line
	3500 6600 3500 6200
Connection ~ 3500 6200
Wire Wire Line
	3500 6200 3700 6200
Wire Wire Line
	4450 6200 4800 6200
Wire Wire Line
	4800 6200 4800 6350
Wire Wire Line
	4800 6800 4350 6800
Connection ~ 4450 6200
Wire Wire Line
	4800 6200 5000 6200
Wire Wire Line
	5000 5900 4850 5900
Wire Wire Line
	4850 5900 4850 5800
Wire Wire Line
	5000 5900 5000 6200
Connection ~ 4800 6200
Connection ~ 5000 6200
Wire Wire Line
	5000 6200 5000 6500
Connection ~ 4850 5800
Wire Wire Line
	4800 6800 4800 6850
Connection ~ 4800 6800
Wire Wire Line
	4050 7000 4050 7100
$Comp
L power:GND #PWR?
U 1 1 619196EE
P 4800 7200
F 0 "#PWR?" H 4800 6950 50  0001 C CNN
F 1 "GND" H 4805 7027 50  0000 C CNN
F 2 "" H 4800 7200 50  0001 C CNN
F 3 "" H 4800 7200 50  0001 C CNN
	1    4800 7200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61919D28
P 5000 7200
F 0 "#PWR?" H 5000 6950 50  0001 C CNN
F 1 "GND" H 5005 7027 50  0000 C CNN
F 2 "" H 5000 7200 50  0001 C CNN
F 3 "" H 5000 7200 50  0001 C CNN
	1    5000 7200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6191A41E
P 4050 7100
F 0 "#PWR?" H 4050 6850 50  0001 C CNN
F 1 "GND" H 4055 6927 50  0000 C CNN
F 2 "" H 4050 7100 50  0001 C CNN
F 3 "" H 4050 7100 50  0001 C CNN
	1    4050 7100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6191AA43
P 2800 7200
F 0 "#PWR?" H 2800 6950 50  0001 C CNN
F 1 "GND" H 2805 7027 50  0000 C CNN
F 2 "" H 2800 7200 50  0001 C CNN
F 3 "" H 2800 7200 50  0001 C CNN
	1    2800 7200
	1    0    0    -1  
$EndComp
$Comp
L Device:C Cin
U 1 1 6191B5EE
P 2800 6850
F 0 "Cin" H 2915 6896 50  0000 L CNN
F 1 "22μF" H 2915 6805 50  0000 L CNN
F 2 "" H 2838 6700 50  0001 C CNN
F 3 "~" H 2800 6850 50  0001 C CNN
	1    2800 6850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 7000 2800 7200
$Comp
L Device:C Cout
U 1 1 6191BC8E
P 5000 6650
F 0 "Cout" H 5115 6696 50  0000 L CNN
F 1 "22μF" H 5115 6605 50  0000 L CNN
F 2 "" H 5038 6500 50  0001 C CNN
F 3 "~" H 5000 6650 50  0001 C CNN
	1    5000 6650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 6800 5000 7200
$Comp
L Device:R R1
U 1 1 6191D1C2
P 4800 6500
F 0 "R1" H 4600 6550 50  0000 L CNN
F 1 "110 K Ω" H 4500 6450 50  0000 L CNN
F 2 "" V 4730 6500 50  0001 C CNN
F 3 "~" H 4800 6500 50  0001 C CNN
	1    4800 6500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 6650 4800 6800
$Comp
L Device:R R2
U 1 1 6191D771
P 4800 7000
F 0 "R2" H 4650 7050 50  0000 L CNN
F 1 "15K Ω" H 4600 6950 50  0000 L CNN
F 2 "" V 4730 7000 50  0001 C CNN
F 3 "~" H 4800 7000 50  0001 C CNN
	1    4800 7000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 7150 4800 7200
$Comp
L pspice:INDUCTOR L
U 1 1 61920202
P 3950 6200
F 0 "L" H 3950 6415 50  0000 C CNN
F 1 "4.7 μHz" H 3950 6324 50  0000 C CNN
F 2 "" H 3950 6200 50  0001 C CNN
F 3 "~" H 3950 6200 50  0001 C CNN
	1    3950 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 6200 4450 6200
Text Label 8250 7650 0    50   ~ 0
01-11-21
$EndSCHEMATC
