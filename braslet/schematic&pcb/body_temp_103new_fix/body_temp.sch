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
L Sensor_Temperature:Si7051-A20 U4
U 1 1 5EF8C469
P 10075 1125
F 0 "U4" H 10125 1475 50  0000 L CNN
F 1 "Si7051-A20" H 10125 1375 50  0000 L CNN
F 2 "body_temp:DFN-6-1EP_3x3mm_P1mm_EP1.5x2.4mm" H 10075 725 50  0001 C CNN
F 3 "https://www.silabs.com/documents/public/data-sheets/Si7050-1-3-4-5-A20.pdf" H 9875 1425 50  0001 C CNN
F 4 "https://www.chipdip.ru/product1/8001949570" H 10075 1125 50  0001 C CNN "Ссылка"
F 5 "400" H 10075 1125 50  0001 C CNN "Цена"
	1    10075 1125
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LP5907MFX-3.3 U2
U 1 1 5EF8DA04
P 4300 2000
F 0 "U2" H 4450 1725 50  0000 C CNN
F 1 "LP5907MFX-3.3" H 4300 2276 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5" H 4300 2350 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lp5907.pdf" H 4300 2500 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/lp5907mfx-3.3-nopb" H 4300 2000 50  0001 C CNN "Ссылка"
F 5 "29" H 4300 2000 50  0001 C CNN "Цена"
	1    4300 2000
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J2
U 1 1 5EF91F2E
P 2600 2250
F 0 "J2" V 2600 2325 50  0000 L CNN
F 1 "Аккумулятор  на плату" V 2725 2100 50  0001 L CNN
F 2 "body_temp:ZH_Conn_02x01" H 2600 2250 50  0001 C CNN
F 3 "~" H 2600 2250 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/b2b-zr-lf-sn-2" H 2600 2250 50  0001 C CNN "Ссылка"
F 5 "9" H 2600 2250 50  0001 C CNN "Цена"
	1    2600 2250
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR013
U 1 1 5EF9A714
P 4700 1600
F 0 "#PWR013" H 4700 1450 50  0001 C CNN
F 1 "+3.3V" H 4715 1773 50  0000 C CNN
F 2 "" H 4700 1600 50  0001 C CNN
F 3 "" H 4700 1600 50  0001 C CNN
	1    4700 1600
	1    0    0    -1  
$EndComp
$Comp
L body_temp-rescue:MAX1555-body_temp D2
U 1 1 5EFC28B9
P 1925 1825
F 0 "D2" H 1900 1350 50  0000 C CNN
F 1 "MAX1555" H 1912 1899 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5" H 1925 2000 50  0001 C CNN
F 3 "" H 1925 2000 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/max1555ezk-t" H 1925 1825 50  0001 C CNN "Ссылка"
F 5 "88" H 1925 1825 50  0001 C CNN "Цена"
	1    1925 1825
	1    0    0    -1  
$EndComp
$Comp
L Device:LED_ALT D1
U 1 1 5EFC551B
P 1000 1900
F 0 "D1" V 1050 1725 50  0000 R CNN
F 1 "Зарядка" V 975 1825 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 1000 1900 50  0001 C CNN
F 3 "~" H 1000 1900 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/to-1608bc-bf" H 1000 1900 50  0001 C CNN "Ссылка"
F 5 "7" H 1000 1900 50  0001 C CNN "Цена"
	1    1000 1900
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR05
U 1 1 5EFC706A
P 1500 1350
F 0 "#PWR05" H 1500 1200 50  0001 C CNN
F 1 "+5V" H 1600 1400 50  0000 C CNN
F 2 "" H 1500 1350 50  0001 C CNN
F 3 "" H 1500 1350 50  0001 C CNN
	1    1500 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 1900 1575 1900
$Comp
L power:GND #PWR06
U 1 1 5EFC81EF
P 1500 2375
F 0 "#PWR06" H 1500 2125 50  0001 C CNN
F 1 "GND" H 1505 2202 50  0000 C CNN
F 2 "" H 1500 2375 50  0001 C CNN
F 3 "" H 1500 2375 50  0001 C CNN
	1    1500 2375
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 2375 1500 2025
Wire Wire Line
	1500 2025 1575 2025
Wire Wire Line
	1425 2150 1575 2150
$Comp
L power:+5V #PWR03
U 1 1 5EFCDA1E
P 1000 1350
F 0 "#PWR03" H 1000 1200 50  0001 C CNN
F 1 "+5V" H 1100 1400 50  0000 C CNN
F 2 "" H 1000 1350 50  0001 C CNN
F 3 "" H 1000 1350 50  0001 C CNN
	1    1000 1350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5EFCF548
P 2300 2400
F 0 "#PWR09" H 2300 2150 50  0001 C CNN
F 1 "GND" H 2150 2300 50  0000 C CNN
F 2 "" H 2300 2400 50  0001 C CNN
F 3 "" H 2300 2400 50  0001 C CNN
	1    2300 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR012
U 1 1 5EFD44BF
P 4300 2700
F 0 "#PWR012" H 4300 2450 50  0001 C CNN
F 1 "GND" H 4305 2527 50  0000 C CNN
F 2 "" H 4300 2700 50  0001 C CNN
F 3 "" H 4300 2700 50  0001 C CNN
	1    4300 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5EFE4019
P 3900 2200
F 0 "C2" H 3750 2300 50  0000 L CNN
F 1 "1uF" H 3700 2100 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3938 2050 50  0001 C CNN
F 3 "~" H 3900 2200 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/grm188r61e105k" H 3900 2200 50  0001 C CNN "Ссылка"
F 5 "7" H 3900 2200 50  0001 C CNN "Цена"
	1    3900 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 1900 4700 1900
$Comp
L power:+3.3V #PWR015
U 1 1 5F00F8FA
P 2000 3825
F 0 "#PWR015" H 2000 3675 50  0001 C CNN
F 1 "+3.3V" H 2200 3875 50  0000 C CNN
F 2 "" H 2000 3825 50  0001 C CNN
F 3 "" H 2000 3825 50  0001 C CNN
	1    2000 3825
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR023
U 1 1 5F01776B
P 2000 7825
F 0 "#PWR023" H 2000 7575 50  0001 C CNN
F 1 "GND" H 2150 7775 50  0000 C CNN
F 2 "" H 2000 7825 50  0001 C CNN
F 3 "" H 2000 7825 50  0001 C CNN
	1    2000 7825
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR027
U 1 1 5F01A304
P 10075 1525
F 0 "#PWR027" H 10075 1275 50  0001 C CNN
F 1 "GND" H 10080 1352 50  0000 C CNN
F 2 "" H 10075 1525 50  0001 C CNN
F 3 "" H 10075 1525 50  0001 C CNN
	1    10075 1525
	1    0    0    -1  
$EndComp
Wire Wire Line
	10075 1525 10075 1425
Text Label 9400 1025 2    50   ~ 0
SCL_temp
Text Label 9400 1125 2    50   ~ 0
SDA_temp
Text Label 3000 4525 0    50   ~ 0
Rx_wifi
Text Label 3000 4425 0    50   ~ 0
Tx_wifi
Text Label 10975 2925 0    50   ~ 0
Tx_wifi
Wire Wire Line
	10900 2725 10975 2725
Text Label 10975 2725 0    50   ~ 0
Rx_wifi
Wire Wire Line
	10975 2925 10900 2925
Text Label 9625 2625 2    50   ~ 0
Rst_wifi
Wire Wire Line
	9625 2625 9700 2625
Text Label 3000 4225 0    50   ~ 0
Rst_wifi
Text Label 8400 2675 2    50   ~ 0
En_wifi
Text Label 3000 4325 0    50   ~ 0
En_wifi
$Comp
L power:GND #PWR020
U 1 1 5F056636
P 10300 3975
F 0 "#PWR020" H 10300 3725 50  0001 C CNN
F 1 "GND" H 10300 3800 50  0000 C CNN
F 2 "" H 10300 3975 50  0001 C CNN
F 3 "" H 10300 3975 50  0001 C CNN
	1    10300 3975
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 5F0670B9
P 5650 4825
F 0 "R6" V 5550 4800 50  0000 R CNN
F 1 "10k" V 5550 5000 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5580 4825 50  0001 C CNN
F 3 "~" H 5650 4825 50  0001 C CNN
F 4 "https://www.chipdip.ru/product0/9000079736" H 5650 4825 50  0001 C CNN "Ссылка"
F 5 "2" H 5650 4825 50  0001 C CNN "Цена"
	1    5650 4825
	0    1    1    0   
$EndComp
$Comp
L RF_Module:ESP-12F U5
U 1 1 5EFB9D06
P 10300 3225
F 0 "U5" H 10500 4075 50  0000 C CNN
F 1 "ESP-12F" H 10625 3975 50  0000 C CNN
F 2 "body_temp:ESP-12E" H 10300 3225 50  0001 C CNN
F 3 "http://wiki.ai-thinker.com/_media/esp8266/esp8266_series_modules_user_manual_v1.1.pdf" H 9950 3325 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/esp-12e" H 10300 3225 50  0001 C CNN "Ссылка"
F 5 "610" H 10300 3225 50  0001 C CNN "Цена"
	1    10300 3225
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5EFCAB3D
P 10975 3975
F 0 "#PWR0101" H 10975 3725 50  0001 C CNN
F 1 "GND" H 10975 3800 50  0000 C CNN
F 2 "" H 10975 3975 50  0001 C CNN
F 3 "" H 10975 3975 50  0001 C CNN
	1    10975 3975
	1    0    0    -1  
$EndComp
Wire Wire Line
	10300 3975 10300 3925
Wire Wire Line
	10975 3975 10975 3525
Wire Wire Line
	10975 3525 10900 3525
$Comp
L power:GND #PWR0102
U 1 1 5EFF0AA2
P 3500 5925
F 0 "#PWR0102" H 3500 5675 50  0001 C CNN
F 1 "GND" H 3650 5825 50  0000 C CNN
F 2 "" H 3500 5925 50  0001 C CNN
F 3 "" H 3500 5925 50  0001 C CNN
	1    3500 5925
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0103
U 1 1 5EFF360A
P 3500 5325
F 0 "#PWR0103" H 3500 5175 50  0001 C CNN
F 1 "+3.3V" H 3515 5498 50  0000 C CNN
F 2 "" H 3500 5325 50  0001 C CNN
F 3 "" H 3500 5325 50  0001 C CNN
	1    3500 5325
	1    0    0    -1  
$EndComp
Text Label 3500 5625 2    50   ~ 0
DIO
Text Label 3000 5525 0    50   ~ 0
DIO
Text Label 3000 5625 0    50   ~ 0
CLK
Text Label 3500 5525 2    50   ~ 0
CLK
Wire Wire Line
	4700 1600 4700 1900
Wire Wire Line
	9675 1125 9525 1125
Wire Wire Line
	9675 1025 9625 1025
Wire Wire Line
	2400 7625 2400 7725
Wire Wire Line
	2400 7725 2300 7725
Wire Wire Line
	2000 7725 2000 7625
Wire Wire Line
	2100 7625 2100 7725
Connection ~ 2100 7725
Wire Wire Line
	2100 7725 2000 7725
Wire Wire Line
	2200 7625 2200 7725
Connection ~ 2200 7725
Wire Wire Line
	2200 7725 2100 7725
Wire Wire Line
	2300 7625 2300 7725
Connection ~ 2300 7725
Wire Wire Line
	2300 7725 2200 7725
Wire Wire Line
	2000 7725 2000 7825
Connection ~ 2000 7725
Wire Wire Line
	2500 4025 2500 3925
Wire Wire Line
	2500 3925 2400 3925
Connection ~ 2100 3925
Wire Wire Line
	2100 3925 2000 3925
Connection ~ 2200 3925
Wire Wire Line
	2200 3925 2100 3925
Wire Wire Line
	2300 4025 2300 3925
Connection ~ 2300 3925
Wire Wire Line
	2300 3925 2200 3925
Wire Wire Line
	2400 4025 2400 3925
Connection ~ 2400 3925
Wire Wire Line
	2400 3925 2300 3925
Wire Wire Line
	2000 3825 2000 3925
Connection ~ 2000 3925
$Comp
L Device:R R3
U 1 1 5F41401A
P 3600 6325
F 0 "R3" H 3530 6279 50  0000 R CNN
F 1 "10k" H 3530 6370 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3530 6325 50  0001 C CNN
F 3 "~" H 3600 6325 50  0001 C CNN
F 4 "https://www.chipdip.ru/product0/9000079736" H 3600 6325 50  0001 C CNN "Ссылка"
F 5 "2" H 3600 6325 50  0001 C CNN "Цена"
	1    3600 6325
	-1   0    0    1   
$EndComp
Wire Wire Line
	2900 6125 3600 6125
Wire Wire Line
	3600 6125 3600 6175
$Comp
L power:GND #PWR011
U 1 1 5F419B87
P 3600 6575
F 0 "#PWR011" H 3600 6325 50  0001 C CNN
F 1 "GND" H 3605 6402 50  0000 C CNN
F 2 "" H 3600 6575 50  0001 C CNN
F 3 "" H 3600 6575 50  0001 C CNN
	1    3600 6575
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 6575 3600 6475
$Comp
L Sensor:MAX30102 IC1
U 1 1 5F41ECE3
P 7300 1700
F 0 "IC1" H 7500 2300 50  0000 R CNN
F 1 "MAX30102" H 7750 2200 50  0000 R CNN
F 2 "body_temp:Maxim_OLGA-14_3.3x5.6mm_P0.8mm" H 7150 2600 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX30102.pdf" H 6950 1950 50  0001 C CNN
F 4 "250" H 7300 1700 50  0001 C CNN "Цена"
	1    7300 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 4425 3000 4425
Wire Wire Line
	2900 4525 3000 4525
Wire Wire Line
	2900 4225 3000 4225
Wire Wire Line
	2900 4325 3000 4325
Text Label 3000 6225 0    50   ~ 0
SWO
Wire Wire Line
	2900 6225 3000 6225
Wire Wire Line
	2900 5525 3000 5525
Wire Wire Line
	2900 5625 3000 5625
$Comp
L Connector_Generic:Conn_01x05 J4
U 1 1 5F475500
P 3800 5625
F 0 "J4" H 3750 6075 50  0000 L CNN
F 1 "ST-Link" H 3650 5975 50  0000 L CNN
F 2 "body_temp:ds1066-05m_2.0mm" H 3800 5625 50  0001 C CNN
F 3 "https://www.chipdip.ru/product/t-ds1066-sc600?from=rec_product" H 3800 5625 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/ds1066-05m-mw-5m" H 3800 5625 50  0001 C CNN "Ссылка"
F 5 "https://www.chipdip.ru/product/ds1066-05f-mu-5f" H 3800 5625 50  0001 C CNN "Ссылка2"
F 6 "57" H 3800 5625 50  0001 C CNN "Цена"
	1    3800 5625
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 5925 3500 5825
Wire Wire Line
	3500 5825 3600 5825
Wire Wire Line
	3600 5425 3500 5425
Wire Wire Line
	3500 5425 3500 5325
Wire Wire Line
	3500 5525 3600 5525
Wire Wire Line
	3500 5625 3600 5625
Text Label 3500 5725 2    50   ~ 0
SWO
Wire Wire Line
	3500 5725 3600 5725
Text Label 1450 4225 2    50   ~ 0
res
Text Label 3000 6525 0    50   ~ 0
SCL_temp
Text Label 3000 6625 0    50   ~ 0
SDA_temp
Wire Wire Line
	2900 6525 3000 6525
Wire Wire Line
	2900 6625 3000 6625
Text Label 6350 1600 2    50   ~ 0
SCL_puls
Text Label 6350 1700 2    50   ~ 0
SDA_puls
Wire Wire Line
	6350 1600 6550 1600
Wire Wire Line
	6350 1700 6450 1700
$Comp
L Device:R R5
U 1 1 5F4F398F
P 9625 800
F 0 "R5" H 9555 754 50  0000 R CNN
F 1 "10k" H 9555 845 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9555 800 50  0001 C CNN
F 3 "~" H 9625 800 50  0001 C CNN
F 4 "https://www.chipdip.ru/product0/9000079736" H 9625 800 50  0001 C CNN "Ссылка"
F 5 "2" H 9625 800 50  0001 C CNN "Цена"
	1    9625 800 
	-1   0    0    1   
$EndComp
$Comp
L Device:R R2
U 1 1 5F4FCDDA
P 9525 800
F 0 "R2" H 9675 750 50  0000 R CNN
F 1 "10k" H 9725 850 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9455 800 50  0001 C CNN
F 3 "~" H 9525 800 50  0001 C CNN
F 4 "https://www.chipdip.ru/product0/9000079736" H 9525 800 50  0001 C CNN "Ссылка"
F 5 "2" H 9525 800 50  0001 C CNN "Цена"
	1    9525 800 
	-1   0    0    1   
$EndComp
Wire Wire Line
	9625 950  9625 1025
Connection ~ 9625 1025
Wire Wire Line
	9625 1025 9400 1025
Wire Wire Line
	9525 950  9525 1125
Connection ~ 9525 1125
Wire Wire Line
	9525 1125 9400 1125
$Comp
L power:+3.3V #PWR08
U 1 1 5F50D178
P 9525 450
F 0 "#PWR08" H 9525 300 50  0001 C CNN
F 1 "+3.3V" H 9540 623 50  0000 C CNN
F 2 "" H 9525 450 50  0001 C CNN
F 3 "" H 9525 450 50  0001 C CNN
	1    9525 450 
	1    0    0    -1  
$EndComp
Wire Wire Line
	9525 450  9525 500 
Wire Wire Line
	9625 650  9625 500 
Wire Wire Line
	9625 500  9525 500 
Connection ~ 9525 500 
Wire Wire Line
	9525 500  9525 650 
$Comp
L Device:R R8
U 1 1 5F529E8D
P 6550 1350
F 0 "R8" H 6480 1304 50  0000 R CNN
F 1 "10k" H 6480 1395 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6480 1350 50  0001 C CNN
F 3 "~" H 6550 1350 50  0001 C CNN
F 4 "https://www.chipdip.ru/product0/9000079736" H 6550 1350 50  0001 C CNN "Ссылка"
F 5 "2" H 6550 1350 50  0001 C CNN "Цена"
	1    6550 1350
	-1   0    0    1   
$EndComp
$Comp
L Device:R R7
U 1 1 5F529E95
P 6450 1350
F 0 "R7" H 6600 1300 50  0000 R CNN
F 1 "10k" H 6650 1400 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6380 1350 50  0001 C CNN
F 3 "~" H 6450 1350 50  0001 C CNN
F 4 "https://www.chipdip.ru/product0/9000079736" H 6450 1350 50  0001 C CNN "Ссылка"
F 5 "2" H 6450 1350 50  0001 C CNN "Цена"
	1    6450 1350
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR019
U 1 1 5F529E9B
P 6450 900
F 0 "#PWR019" H 6450 750 50  0001 C CNN
F 1 "+3.3V" H 6465 1073 50  0000 C CNN
F 2 "" H 6450 900 50  0001 C CNN
F 3 "" H 6450 900 50  0001 C CNN
	1    6450 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 1200 6550 1050
Wire Wire Line
	6550 1050 6450 1050
Wire Wire Line
	6450 1050 6450 1200
Wire Wire Line
	6550 1500 6550 1600
Connection ~ 6550 1600
Wire Wire Line
	6550 1600 6700 1600
Wire Wire Line
	6450 1500 6450 1700
Connection ~ 6450 1700
Wire Wire Line
	6450 1700 6700 1700
$Comp
L Regulator_Linear:MCP1700-1202E_SOT23 U6
U 1 1 5F5E0113
P 8450 1050
F 0 "U6" H 8450 1292 50  0000 C CNN
F 1 "MCP1700-1202E_SOT23" H 8350 1200 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 8450 1275 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20001826D.pdf" H 8450 1050 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/mcp1700t-1802e-tt-4" H 8450 1050 50  0001 C CNN "Ссылка"
F 5 "53" H 8450 1050 50  0001 C CNN "Цена"
	1    8450 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 1200 7200 1050
Wire Wire Line
	7200 1050 6550 1050
Connection ~ 6550 1050
Wire Wire Line
	7300 1200 7300 1050
Wire Wire Line
	7300 1050 7200 1050
Connection ~ 7200 1050
Wire Wire Line
	7300 1050 8150 1050
Connection ~ 7300 1050
$Comp
L power:GND #PWR024
U 1 1 5F5F5496
P 8450 1400
F 0 "#PWR024" H 8450 1150 50  0001 C CNN
F 1 "GND" H 8455 1227 50  0000 C CNN
F 2 "" H 8450 1400 50  0001 C CNN
F 3 "" H 8450 1400 50  0001 C CNN
	1    8450 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8450 1400 8450 1350
Wire Wire Line
	8750 1050 8850 1050
Wire Wire Line
	8850 1050 8850 850 
Wire Wire Line
	8850 850  7000 850 
Wire Wire Line
	7000 850  7000 1200
$Comp
L power:GND #PWR021
U 1 1 5F6020FE
P 7200 2250
F 0 "#PWR021" H 7200 2000 50  0001 C CNN
F 1 "GND" H 7205 2077 50  0000 C CNN
F 2 "" H 7200 2250 50  0001 C CNN
F 3 "" H 7200 2250 50  0001 C CNN
	1    7200 2250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR022
U 1 1 5F602465
P 7400 2250
F 0 "#PWR022" H 7400 2000 50  0001 C CNN
F 1 "GND" H 7405 2077 50  0000 C CNN
F 2 "" H 7400 2250 50  0001 C CNN
F 3 "" H 7400 2250 50  0001 C CNN
	1    7400 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 2250 7400 2200
Wire Wire Line
	7200 2250 7200 2200
$Comp
L Device:CP_Small C5
U 1 1 5F3CA854
P 8350 4750
F 0 "C5" V 8450 4500 50  0000 C CNN
F 1 "0.47uF" V 8450 4700 50  0000 C CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3216-18_Kemet-A" H 8350 4750 50  0001 C CNN
F 3 "~" H 8350 4750 50  0001 C CNN
F 4 "https://www.chipdip.ru/product0/176529410" H 8350 4750 50  0001 C CNN "Ссылка"
F 5 "19" H 8350 4750 50  0001 C CNN "Цена"
	1    8350 4750
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C6
U 1 1 5F3CC786
P 10450 5000
F 0 "C6" H 10542 5046 50  0000 L CNN
F 1 "5pF" H 10542 4955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 10450 5000 50  0001 C CNN
F 3 "~" H 10450 5000 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/grm1885c1h5r1c" H 10450 5000 50  0001 C CNN "Ссылка"
F 5 "3" H 10450 5000 50  0001 C CNN "Цена"
	1    10450 5000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 5F3CE1ED
P 8650 4750
F 0 "R9" V 8550 4900 50  0000 R CNN
F 1 "10k" V 8550 4750 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8580 4750 50  0001 C CNN
F 3 "~" H 8650 4750 50  0001 C CNN
F 4 "https://www.chipdip.ru/product0/9000079736" H 8650 4750 50  0001 C CNN "Ссылка"
F 5 "2" H 8650 4750 50  0001 C CNN "Цена"
	1    8650 4750
	0    -1   -1   0   
$EndComp
$Comp
L body_temp-rescue:TPA301-body_temp U7
U 1 1 5F3D7DF2
P 9350 4300
F 0 "U7" H 9100 4300 50  0000 C CNN
F 1 "TPA301" H 9350 4300 50  0000 C CNN
F 2 "body_temp:MSOP-8-1EP_3x3mm_P0.65mm_EP1.95x2.15mm" H 9350 4300 50  0001 C CNN
F 3 "" H 9350 4300 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/tpa301d" H 9350 4300 50  0001 C CNN "Ссылка"
F 5 "51" H 9350 4300 50  0001 C CNN "Цена"
	1    9350 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	8450 4750 8500 4750
Wire Wire Line
	8900 4650 8850 4650
Wire Wire Line
	8850 4650 8850 4550
Wire Wire Line
	8850 4550 8900 4550
$Comp
L Device:CP_Small C7
U 1 1 5F3F0555
P 8700 4550
F 0 "C7" V 8600 4300 50  0000 C CNN
F 1 "2.2uF" V 8600 4500 50  0000 C CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3216-18_Kemet-A" H 8700 4550 50  0001 C CNN
F 3 "~" H 8700 4550 50  0001 C CNN
F 4 "https://www.chipdip.ru/product0/12712" H 8700 4550 50  0001 C CNN "Ссылка"
F 5 "19" H 8700 4550 50  0001 C CNN "Цена"
	1    8700 4550
	0    1    1    0   
$EndComp
Wire Wire Line
	8800 4550 8850 4550
Connection ~ 8850 4550
$Comp
L power:GND #PWR025
U 1 1 5F3F8322
P 8550 4600
F 0 "#PWR025" H 8550 4350 50  0001 C CNN
F 1 "GND" H 8400 4600 50  0000 C CNN
F 2 "" H 8550 4600 50  0001 C CNN
F 3 "" H 8550 4600 50  0001 C CNN
	1    8550 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 4600 8550 4550
Wire Wire Line
	8550 4550 8600 4550
$Comp
L Device:CP_Small C8
U 1 1 5F40027C
P 9900 4950
F 0 "C8" H 9750 5000 50  0000 C CNN
F 1 "1uF" H 9750 4900 50  0000 C CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3216-18_Kemet-A" H 9900 4950 50  0001 C CNN
F 3 "~" H 9900 4950 50  0001 C CNN
F 4 "https://www.chipdip.ru/product0/19661" H 9900 4950 50  0001 C CNN "Ссылка"
F 5 "19" H 9900 4950 50  0001 C CNN "Цена"
	1    9900 4950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR028
U 1 1 5F409B46
P 9900 5300
F 0 "#PWR028" H 9900 5050 50  0001 C CNN
F 1 "GND" H 9900 5150 50  0000 C CNN
F 2 "" H 9900 5300 50  0001 C CNN
F 3 "" H 9900 5300 50  0001 C CNN
	1    9900 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9900 5300 9900 5050
$Comp
L power:GND #PWR029
U 1 1 5F411168
P 10050 5300
F 0 "#PWR029" H 10050 5050 50  0001 C CNN
F 1 "GND" H 10050 5150 50  0000 C CNN
F 2 "" H 10050 5300 50  0001 C CNN
F 3 "" H 10050 5300 50  0001 C CNN
	1    10050 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	10050 5300 10050 4550
Wire Wire Line
	10050 4550 9800 4550
$Comp
L Device:Speaker LS1
U 1 1 5F41A095
P 11000 4550
F 0 "LS1" H 11170 4546 50  0000 L CNN
F 1 "Speaker" H 11170 4455 50  0000 L CNN
F 2 "" H 11000 4350 50  0001 C CNN
F 3 "~" H 10990 4500 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/kp1530sp1-7021-8" H 11000 4550 50  0001 C CNN "Ссылка"
F 5 "78" H 11000 4550 50  0001 C CNN "Цена"
	1    11000 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9900 4850 9900 4650
Wire Wire Line
	9900 4650 9800 4650
Wire Wire Line
	10250 4550 10200 4550
Wire Wire Line
	10200 4550 10200 4450
Wire Wire Line
	10200 4450 9800 4450
Wire Wire Line
	10250 4650 10200 4650
Wire Wire Line
	10200 4650 10200 4750
Wire Wire Line
	10200 4750 9800 4750
$Comp
L Device:R R10
U 1 1 5F47C02B
P 10200 5000
F 0 "R10" H 10400 5050 50  0000 R CNN
F 1 "50k" H 10400 4950 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 10130 5000 50  0001 C CNN
F 3 "~" H 10200 5000 50  0001 C CNN
F 4 "https://www.chipdip.ru/product0/9000079753" H 10200 5000 50  0001 C CNN "Ссылка"
F 5 "2" H 10200 5000 50  0001 C CNN "Цена"
	1    10200 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	10200 4850 10200 4750
Connection ~ 10200 4750
Wire Wire Line
	8800 4750 8850 4750
Wire Wire Line
	10200 5150 10200 5250
Wire Wire Line
	10200 5250 8850 5250
Wire Wire Line
	8850 5250 8850 4750
Connection ~ 8850 4750
Wire Wire Line
	8850 4750 8900 4750
Wire Wire Line
	10450 4900 10450 4750
Wire Wire Line
	10450 4750 10200 4750
Wire Wire Line
	10450 5100 10450 5250
Wire Wire Line
	10450 5250 10200 5250
Connection ~ 10200 5250
$Comp
L MCU_ST_STM32F1:STM32F103RCTx U1
U 1 1 5F4E1C52
P 2200 5825
F 0 "U1" H 2600 7675 50  0000 C CNN
F 1 "STM32F103RCTx" H 2850 7575 50  0000 C CNN
F 2 "Package_QFP:LQFP-64_10x10mm_P0.5mm" H 1600 4125 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00191185.pdf" H 2200 5825 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/stm32f103rct6-2" H 2200 5825 50  0001 C CNN "Ссылка"
F 5 "230" H 2200 5825 50  0001 C CNN "Цена"
	1    2200 5825
	1    0    0    -1  
$EndComp
Text Label 3000 4625 0    50   ~ 0
audio
Wire Wire Line
	2900 4625 3000 4625
Wire Wire Line
	2000 3925 2000 4025
Wire Wire Line
	2100 3925 2100 4025
Wire Wire Line
	2200 3925 2200 4025
Text Label 8200 4750 2    50   ~ 0
audio
Wire Wire Line
	8200 4750 8250 4750
Text Label 8850 4350 2    50   ~ 0
audio_on
Wire Wire Line
	8850 4350 8850 4450
Wire Wire Line
	8850 4450 8900 4450
Text Label 3000 4725 0    50   ~ 0
audio_on
Wire Wire Line
	3000 4725 2900 4725
$Comp
L Device:Battery_Cell BT1
U 1 1 5F5200A1
P 2500 2900
F 0 "BT1" V 2350 2950 50  0000 C CNN
F 1 "Аккумулятор 3.7В" V 2650 2950 50  0000 C CNN
F 2 "" V 2500 2960 50  0001 C CNN
F 3 "~" V 2500 2960 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/lp504368-robiton" H 2500 2900 50  0001 C CNN "Ссылка"
F 5 "410" H 2500 2900 50  0001 C CNN "Цена"
	1    2500 2900
	0    1    1    0   
$EndComp
Wire Wire Line
	2250 1900 2600 1900
Wire Wire Line
	2500 2050 2500 2000
Wire Wire Line
	2300 2400 2300 2000
Wire Wire Line
	2300 2000 2500 2000
Wire Wire Line
	2600 2050 2600 1900
$Comp
L Connector:Conn_01x02_Male J5
U 1 1 5F55E3BB
P 2600 2400
F 0 "J5" V 2662 2444 50  0000 L CNN
F 1 "Аккумулятор на кабель" V 3000 2600 50  0001 L CNN
F 2 "" H 2600 2400 50  0001 C CNN
F 3 "~" H 2600 2400 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/zhr-2" H 2600 2400 50  0001 C CNN "Ссылка"
F 5 "https://www.chipdip.ru/product/szh-002t-003t-p0.5?from=rec_product" H 2600 2400 50  0001 C CNN "Ссылка2"
F 6 "24" H 2600 2400 50  0001 C CNN "Цена"
	1    2600 2400
	0    1    1    0   
$EndComp
Wire Wire Line
	2400 2900 2350 2900
Wire Wire Line
	2350 2900 2350 2650
Wire Wire Line
	2350 2650 2500 2650
Wire Wire Line
	2500 2650 2500 2600
Wire Wire Line
	2700 2900 2750 2900
Wire Wire Line
	2750 2900 2750 2650
Wire Wire Line
	2750 2650 2600 2650
Wire Wire Line
	2600 2650 2600 2600
$Comp
L Connector_Generic:Conn_01x02 J3
U 1 1 5F5BD609
P 10450 4550
F 0 "J3" H 10400 4700 50  0000 L CNN
F 1 "Динамик на плату" V 10575 4400 50  0001 L CNN
F 2 "body_temp:ZH_Conn_02x01" H 10450 4550 50  0001 C CNN
F 3 "~" H 10450 4550 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/b2b-zr-lf-sn-2" H 10450 4550 50  0001 C CNN "Ссылка"
F 5 "9" H 10450 4550 50  0001 C CNN "Цена"
	1    10450 4550
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J6
U 1 1 5F5BE0A4
P 10550 4550
F 0 "J6" H 10600 4700 50  0000 L CNN
F 1 "Динамик на кабель" V 10950 4750 50  0001 L CNN
F 2 "" H 10550 4550 50  0001 C CNN
F 3 "~" H 10550 4550 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/zhr-2" H 10550 4550 50  0001 C CNN "Ссылка"
F 5 "https://www.chipdip.ru/product/szh-002t-003t-p0.5?from=rec_product" H 10550 4550 50  0001 C CNN "Ссылка2"
F 6 "24" H 10550 4550 50  0001 C CNN "Цена"
	1    10550 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	10750 4550 10800 4550
Wire Wire Line
	10750 4650 10800 4650
Text Label 3000 5125 0    50   ~ 0
Rx_debug
Text Label 3000 5225 0    50   ~ 0
Tx_debug
Wire Wire Line
	2900 5125 3000 5125
Wire Wire Line
	2900 5225 3000 5225
$Comp
L Device:Crystal Y1
U 1 1 5F676CB3
P 1150 7325
F 0 "Y1" H 1150 7593 50  0000 C CNN
F 1 "Crystal" H 1150 7502 50  0000 C CNN
F 2 "Crystal:Crystal_SMD_G8-2Pin_3.2x1.5mm" H 1150 7325 50  0001 C CNN
F 3 "~" H 1150 7325 50  0001 C CNN
F 4 "https://www.chipdip.ru/product0/9000372611" H 1150 7325 50  0001 C CNN "Ссылка"
F 5 "45" H 1150 7325 50  0001 C CNN "Цена"
	1    1150 7325
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 7325 1350 7325
Wire Wire Line
	1500 7425 1450 7425
Wire Wire Line
	1450 7425 1450 7525
Wire Wire Line
	1450 7525 950  7525
Wire Wire Line
	950  7525 950  7325
Wire Wire Line
	950  7325 1000 7325
$Comp
L Device:C_Small C9
U 1 1 5F71BD99
P 950 7675
F 0 "C9" H 1042 7721 50  0000 L CNN
F 1 "10pF" H 1042 7630 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 950 7675 50  0001 C CNN
F 3 "~" H 950 7675 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/grm1885c1h100j" H 950 7675 50  0001 C CNN "Ссылка"
F 5 "3" H 950 7675 50  0001 C CNN "Цена"
	1    950  7675
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C10
U 1 1 5F71C528
P 1350 7675
F 0 "C10" H 1442 7721 50  0000 L CNN
F 1 "10pF" H 1442 7630 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1350 7675 50  0001 C CNN
F 3 "~" H 1350 7675 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/grm1885c1h100j" H 1350 7675 50  0001 C CNN "Ссылка"
F 5 "3" H 1350 7675 50  0001 C CNN "Цена"
	1    1350 7675
	1    0    0    -1  
$EndComp
Wire Wire Line
	950  7525 950  7575
Connection ~ 950  7525
$Comp
L power:GND #PWR030
U 1 1 5F737B26
P 950 7825
F 0 "#PWR030" H 950 7575 50  0001 C CNN
F 1 "GND" H 950 7675 50  0000 C CNN
F 2 "" H 950 7825 50  0001 C CNN
F 3 "" H 950 7825 50  0001 C CNN
	1    950  7825
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR031
U 1 1 5F737B2C
P 1350 7825
F 0 "#PWR031" H 1350 7575 50  0001 C CNN
F 1 "GND" H 1350 7675 50  0000 C CNN
F 2 "" H 1350 7825 50  0001 C CNN
F 3 "" H 1350 7825 50  0001 C CNN
	1    1350 7825
	1    0    0    -1  
$EndComp
Wire Wire Line
	950  7775 950  7825
$Comp
L Transistor_FET:IRLML6402 Q1
U 1 1 5F8FD19C
P 3150 2000
F 0 "Q1" V 3050 1900 50  0000 C CNN
F 1 "IRLML6402" V 3401 2000 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 3350 1925 50  0001 L CIN
F 3 "https://www.infineon.com/dgdl/irlml6402pbf.pdf?fileId=5546d462533600a401535668d5c2263c" H 3150 2000 50  0001 L CNN
F 4 "https://www.chipdip.ru/product/irlml6402tr" H 3150 2000 50  0001 C CNN "Ссылка"
F 5 "12" H 3150 2000 50  0001 C CNN "Цена"
	1    3150 2000
	0    1    -1   0   
$EndComp
Wire Wire Line
	4000 2000 3900 2000
Wire Wire Line
	3900 2000 3900 1900
Wire Wire Line
	3900 1900 4000 1900
Wire Wire Line
	3150 2200 3150 2300
Wire Wire Line
	3150 2300 2900 2300
Wire Wire Line
	2900 1500 2900 2300
$Comp
L Device:R R11
U 1 1 5F9E9B0E
P 3150 2500
F 0 "R11" H 3350 2450 50  0000 R CNN
F 1 "10k" H 3350 2550 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3080 2500 50  0001 C CNN
F 3 "~" H 3150 2500 50  0001 C CNN
F 4 "https://www.chipdip.ru/product0/9000079736" H 3150 2500 50  0001 C CNN "Ссылка"
F 5 "2" H 3150 2500 50  0001 C CNN "Цена"
	1    3150 2500
	-1   0    0    1   
$EndComp
Wire Wire Line
	3150 2350 3150 2300
Connection ~ 3150 2300
$Comp
L power:GND #PWR010
U 1 1 5F9F8817
P 3150 2700
F 0 "#PWR010" H 3150 2450 50  0001 C CNN
F 1 "GND" H 3155 2527 50  0000 C CNN
F 2 "" H 3150 2700 50  0001 C CNN
F 3 "" H 3150 2700 50  0001 C CNN
	1    3150 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 2700 3150 2650
Wire Wire Line
	3600 2200 3600 2300
Wire Wire Line
	3600 2300 3150 2300
Wire Wire Line
	3350 1900 3400 1900
Wire Wire Line
	3800 1900 3900 1900
Connection ~ 3900 1900
$Comp
L Transistor_FET:IRLML6402 Q2
U 1 1 5FA1781C
P 3600 2000
F 0 "Q2" V 3500 2100 50  0000 C CNN
F 1 "IRLML6402" V 3851 2000 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 3800 1925 50  0001 L CIN
F 3 "https://www.infineon.com/dgdl/irlml6402pbf.pdf?fileId=5546d462533600a401535668d5c2263c" H 3600 2000 50  0001 L CNN
F 4 "https://www.chipdip.ru/product/irlml6402tr" H 3600 2000 50  0001 C CNN "Ссылка"
F 5 "12" H 3600 2000 50  0001 C CNN "Цена"
	1    3600 2000
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR032
U 1 1 5FAAEBF2
P 3900 2700
F 0 "#PWR032" H 3900 2450 50  0001 C CNN
F 1 "GND" H 3905 2527 50  0000 C CNN
F 2 "" H 3900 2700 50  0001 C CNN
F 3 "" H 3900 2700 50  0001 C CNN
	1    3900 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 2700 3900 2350
Wire Wire Line
	4300 2300 4300 2700
Wire Wire Line
	3900 2050 3900 2000
Connection ~ 3900 2000
Wire Wire Line
	1500 1350 1500 1500
Wire Wire Line
	2950 1900 2600 1900
Connection ~ 2600 1900
Wire Wire Line
	2900 1500 1500 1500
Connection ~ 1500 1500
Wire Wire Line
	1500 1500 1500 1900
Wire Wire Line
	7750 3100 7400 3100
Wire Wire Line
	7750 3000 7400 3000
Text Label 7750 3100 0    50   ~ 0
Tx_debug
Text Label 7750 3000 0    50   ~ 0
Rx_debug
Wire Wire Line
	7800 3300 7900 3300
Text Label 7900 3300 0    50   ~ 0
res
Wire Wire Line
	7400 3300 7500 3300
$Comp
L Device:C C4
U 1 1 5F4A2FC5
P 7650 3300
F 0 "C4" V 7500 3250 50  0000 L CNN
F 1 "1uF" V 7500 3400 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7688 3150 50  0001 C CNN
F 3 "~" H 7650 3300 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/grm188r61e105k" H 7650 3300 50  0001 C CNN "Ссылка"
F 5 "7" H 7650 3300 50  0001 C CNN "Цена"
	1    7650 3300
	0    1    1    0   
$EndComp
Wire Wire Line
	6900 5300 6900 5200
$Comp
L power:GND #PWR016
U 1 1 5F3C560D
P 6900 5300
F 0 "#PWR016" H 6900 5050 50  0001 C CNN
F 1 "GND" H 6905 5127 50  0000 C CNN
F 2 "" H 6900 5300 50  0001 C CNN
F 3 "" H 6900 5300 50  0001 C CNN
	1    6900 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 4000 6200 3900
$Comp
L power:GND #PWR014
U 1 1 5F3AFAF0
P 6200 4000
F 0 "#PWR014" H 6200 3750 50  0001 C CNN
F 1 "GND" H 6205 3827 50  0000 C CNN
F 2 "" H 6200 4000 50  0001 C CNN
F 3 "" H 6200 4000 50  0001 C CNN
	1    6200 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 3300 6400 3300
Connection ~ 6300 3300
Wire Wire Line
	6300 3500 6300 3300
Wire Wire Line
	6200 3400 6400 3400
Connection ~ 6200 3400
Wire Wire Line
	6200 3500 6200 3400
Connection ~ 6100 3200
Wire Wire Line
	6100 3500 6100 3200
$Comp
L Power_Protection:SP0503BAHT D4
U 1 1 5F3A61C0
P 6200 3700
F 0 "D4" H 5875 3750 50  0000 L CNN
F 1 "SP0503BAHT" H 5625 3550 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-143" H 6425 3650 50  0001 L CNN
F 3 "http://www.littelfuse.com/~/media/files/littelfuse/technical%20resources/documents/data%20sheets/sp05xxba.pdf" H 6325 3825 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/sp0503bahtg" H 6200 3700 50  0001 C CNN "Ссылка"
F 5 "58" H 6200 3700 50  0001 C CNN "Цена"
	1    6200 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 2450 6800 2450
Connection ~ 6250 2450
Wire Wire Line
	6250 2600 6250 2450
Wire Wire Line
	6100 3100 6100 2450
Connection ~ 6100 3100
Wire Wire Line
	5925 3100 6100 3100
Wire Wire Line
	5925 3400 6200 3400
Wire Wire Line
	5925 3300 6300 3300
$Comp
L body_temp-rescue:USB_B_Micro-Connector J1
U 1 1 5EF938C7
P 5625 3300
F 0 "J1" H 5682 3767 50  0000 C CNN
F 1 "USB_B_Micro" H 5682 3676 50  0000 C CNN
F 2 "Connector_USB:USB_Micro-B_Molex-105017-0001" H 5775 3250 50  0001 C CNN
F 3 "~" H 5775 3250 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/105017-0001-molex" H 5625 3300 50  0001 C CNN "Ссылка"
F 5 "50" H 5625 3300 50  0001 C CNN "Цена"
	1    5625 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 2450 6800 2600
Wire Wire Line
	6100 2450 6250 2450
Wire Wire Line
	6100 3200 6100 3100
Wire Wire Line
	6400 3200 6100 3200
Wire Wire Line
	6250 3000 6250 2900
Wire Wire Line
	6400 3000 6250 3000
$Comp
L Device:R R4
U 1 1 5F35D34A
P 6250 2750
F 0 "R4" H 6180 2704 50  0000 R CNN
F 1 "10k" H 6180 2795 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6180 2750 50  0001 C CNN
F 3 "~" H 6250 2750 50  0001 C CNN
F 4 "https://www.chipdip.ru/product0/9000079736" H 6250 2750 50  0001 C CNN "Ссылка"
F 5 "2" H 6250 2750 50  0001 C CNN "Цена"
	1    6250 2750
	-1   0    0    1   
$EndComp
$Comp
L Interface_USB:CP2102N-A01-GQFN28 U3
U 1 1 5F35845E
P 6900 3900
F 0 "U3" H 6750 2650 50  0000 C CNN
F 1 "CP2102N-A01-GQFN28" H 7400 2650 50  0000 C CNN
F 2 "Package_DFN_QFN:QFN-28-1EP_5x5mm_P0.5mm_EP3.35x3.35mm" H 7350 2700 50  0001 L CNN
F 3 "https://www.silabs.com/documents/public/data-sheets/cp2102n-datasheet.pdf" H 6950 3150 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/cp2102-gmr" H 6900 3900 50  0001 C CNN "Ссылка"
F 5 "140" H 6900 3900 50  0001 C CNN "Цена"
	1    6900 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7775 4350 7775 4150
$Comp
L power:GND #PWR02
U 1 1 5EFDF79E
P 7775 4350
F 0 "#PWR02" H 7775 4100 50  0001 C CNN
F 1 "GND" H 7780 4177 50  0000 C CNN
F 2 "" H 7775 4350 50  0001 C CNN
F 3 "" H 7775 4350 50  0001 C CNN
	1    7775 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7775 3675 7775 3850
$Comp
L power:+5V #PWR01
U 1 1 5EFDE46D
P 7775 3675
F 0 "#PWR01" H 7775 3525 50  0001 C CNN
F 1 "+5V" H 7790 3848 50  0000 C CNN
F 2 "" H 7775 3675 50  0001 C CNN
F 3 "" H 7775 3675 50  0001 C CNN
	1    7775 3675
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5EFDCA3F
P 7775 4000
F 0 "C1" H 7890 4046 50  0000 L CNN
F 1 "1uF" H 7890 3955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7813 3850 50  0001 C CNN
F 3 "~" H 7775 4000 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/grm188r61e105k" H 7775 4000 50  0001 C CNN "Ссылка"
F 5 "7" H 7775 4000 50  0001 C CNN "Цена"
	1    7775 4000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5EFAF710
P 5525 3850
F 0 "#PWR04" H 5525 3600 50  0001 C CNN
F 1 "GND" H 5425 3850 50  0000 C CNN
F 2 "" H 5525 3850 50  0001 C CNN
F 3 "" H 5525 3850 50  0001 C CNN
	1    5525 3850
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_3_Open JP1
U 1 1 5FCD7934
P 3400 1400
F 0 "JP1" V 3500 1250 50  0000 C CNN
F 1 "SolderJumper_3_Open" V 3500 850 50  0001 C CNN
F 2 "Jumper:SolderJumper-3_P1.3mm_Open_RoundedPad1.0x1.5mm" H 3400 1400 50  0001 C CNN
F 3 "~" H 3400 1400 50  0001 C CNN
	1    3400 1400
	0    -1   1    0   
$EndComp
Wire Wire Line
	3550 1400 3900 1400
Wire Wire Line
	3900 1400 3900 1900
Wire Wire Line
	3400 1150 2900 1150
Wire Wire Line
	2900 1150 2900 1500
Connection ~ 2900 1500
Wire Wire Line
	3400 1650 2600 1650
Wire Wire Line
	2600 1650 2600 1900
Text Notes 950  1150 0    50   ~ 0
JP1 для теста работы алгоритма!\n1-2 При включении зарядки от USB, питание схемы идёт от USB, аккумулятор только заряжается\n2-3 Питание схемы всегда от аккумулятора
Wire Wire Line
	1000 1350 1000 1750
Wire Wire Line
	1000 2150 1000 2050
$Comp
L Device:R R1
U 1 1 5EFCA2BF
P 1275 2150
F 0 "R1" V 1375 2150 50  0000 C CNN
F 1 "1k" V 1175 2150 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1205 2150 50  0001 C CNN
F 3 "~" H 1275 2150 50  0001 C CNN
F 4 "https://www.chipdip.ru/product0/9000079676" H 1275 2150 50  0001 C CNN "Ссылка"
F 5 "2" H 1275 2150 50  0001 C CNN "Цена"
	1    1275 2150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1000 2150 1125 2150
Wire Wire Line
	3400 1200 3400 1150
Wire Wire Line
	3400 1600 3400 1650
Wire Wire Line
	1350 7825 1350 7775
Wire Wire Line
	1350 7575 1350 7325
Connection ~ 1350 7325
Wire Wire Line
	1350 7325 1500 7325
$Comp
L power:+5V #PWR0107
U 1 1 5F4C8973
P 6100 2350
F 0 "#PWR0107" H 6100 2200 50  0001 C CNN
F 1 "+5V" H 6200 2400 50  0000 C CNN
F 2 "" H 6100 2350 50  0001 C CNN
F 3 "" H 6100 2350 50  0001 C CNN
	1    6100 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 2350 6100 2450
Connection ~ 6100 2450
$Comp
L power:GND #PWR035
U 1 1 5F47C76F
P 9450 3500
F 0 "#PWR035" H 9450 3250 50  0001 C CNN
F 1 "GND" H 9450 3350 50  0000 C CNN
F 2 "" H 9450 3500 50  0001 C CNN
F 3 "" H 9450 3500 50  0001 C CNN
	1    9450 3500
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR017
U 1 1 5F47CE01
P 9450 3200
F 0 "#PWR017" H 9450 3050 50  0001 C CNN
F 1 "+3.3V" H 9465 3373 50  0000 C CNN
F 2 "" H 9450 3200 50  0001 C CNN
F 3 "" H 9450 3200 50  0001 C CNN
	1    9450 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	9450 3500 9450 3450
Wire Wire Line
	9450 3200 9450 3250
$Comp
L Device:CP_Small C3
U 1 1 5F4C4BF0
P 9450 3350
F 0 "C3" H 9300 3400 50  0000 C CNN
F 1 "1uF" H 9300 3300 50  0000 C CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3216-18_Kemet-A" H 9450 3350 50  0001 C CNN
F 3 "~" H 9450 3350 50  0001 C CNN
F 4 "https://www.chipdip.ru/product0/19661" H 9450 3350 50  0001 C CNN "Ссылка"
F 5 "19" H 9450 3350 50  0001 C CNN "Цена"
	1    9450 3350
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR036
U 1 1 5F4D5839
P 9900 4250
F 0 "#PWR036" H 9900 4100 50  0001 C CNN
F 1 "+3.3V" H 9915 4423 50  0000 C CNN
F 2 "" H 9900 4250 50  0001 C CNN
F 3 "" H 9900 4250 50  0001 C CNN
	1    9900 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9900 4250 9900 4650
Connection ~ 9900 4650
$Comp
L 74xGxx:74LVC2G14 U8
U 2 1 5F45E21C
P 5025 4825
F 0 "U8" H 4875 4975 50  0000 C CNN
F 1 "74LVC2G14" H 5250 4925 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 5025 4825 50  0001 C CNN
F 3 "https://www.ti.com/lit/ds/symlink/sn74lvc2g14.pdf" H 5025 4825 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/sn74lvc2g14dbvr-2" H 5025 4825 50  0001 C CNN "Ссылка"
F 5 "12" H 5025 4825 50  0001 C CNN "Цена"
	2    5025 4825
	1    0    0    -1  
$EndComp
$Comp
L 74xGxx:74LVC2G14 U8
U 1 1 5F45FA52
P 5025 5375
F 0 "U8" H 4875 5525 50  0000 C CNN
F 1 "74LVC2G14" H 5275 5275 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 5025 5375 50  0001 C CNN
F 3 "https://www.ti.com/lit/ds/symlink/sn74lvc2g14.pdf" H 5025 5375 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/sn74lvc2g14dbvr-2" H 5025 5375 50  0001 C CNN "Ссылка"
F 5 "12" H 5025 5375 50  0001 C CNN "Цена"
	1    5025 5375
	1    0    0    -1  
$EndComp
$Comp
L Diode:BAS316 D6
U 1 1 5F47240F
P 4625 5175
F 0 "D6" V 4675 5525 50  0000 R CNN
F 1 "BAS316" V 4575 5525 50  0000 R CNN
F 2 "Diode_SMD:D_SOD-323" H 4625 5000 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/BAS16_SER.pdf" H 4625 5175 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/bas321.115" H 4625 5175 50  0001 C CNN "Ссылка"
F 5 "11" H 4625 5175 50  0001 C CNN "Цена"
	1    4625 5175
	0    -1   -1   0   
$EndComp
$Comp
L Device:CP_Small C11
U 1 1 5F474506
P 4625 5575
F 0 "C11" H 4775 5625 50  0000 C CNN
F 1 "10uF" H 4775 5475 50  0000 C CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3216-18_Kemet-A" H 4625 5575 50  0001 C CNN
F 3 "~" H 4625 5575 50  0001 C CNN
F 4 "https://www.chipdip.ru/product0/868717967" H 4625 5575 50  0001 C CNN "Ссылка"
F 5 "16" H 4625 5575 50  0001 C CNN "Цена"
	1    4625 5575
	1    0    0    -1  
$EndComp
Wire Wire Line
	4725 5375 4625 5375
Connection ~ 4625 5375
$Comp
L Device:R R14
U 1 1 5F4962F9
P 4325 5575
F 0 "R14" H 4525 5625 50  0000 R CNN
F 1 "50k" H 4525 5525 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4255 5575 50  0001 C CNN
F 3 "~" H 4325 5575 50  0001 C CNN
F 4 "https://www.chipdip.ru/product0/9000079753" H 4325 5575 50  0001 C CNN "Ссылка"
F 5 "2" H 4325 5575 50  0001 C CNN "Цена"
	1    4325 5575
	1    0    0    -1  
$EndComp
Wire Wire Line
	4325 5425 4325 5375
$Comp
L power:GND #PWR07
U 1 1 5F4A9D2C
P 4325 5775
F 0 "#PWR07" H 4325 5525 50  0001 C CNN
F 1 "GND" H 4475 5725 50  0000 C CNN
F 2 "" H 4325 5775 50  0001 C CNN
F 3 "" H 4325 5775 50  0001 C CNN
	1    4325 5775
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR038
U 1 1 5F4AA647
P 4625 5775
F 0 "#PWR038" H 4625 5525 50  0001 C CNN
F 1 "GND" H 4775 5725 50  0000 C CNN
F 2 "" H 4625 5775 50  0001 C CNN
F 3 "" H 4625 5775 50  0001 C CNN
	1    4625 5775
	1    0    0    -1  
$EndComp
Wire Wire Line
	4625 5775 4625 5675
Wire Wire Line
	4325 5725 4325 5775
Wire Wire Line
	4725 4825 4625 4825
$Comp
L power:GND #PWR041
U 1 1 5F4F381D
P 6100 5775
F 0 "#PWR041" H 6100 5525 50  0001 C CNN
F 1 "GND" H 6250 5725 50  0000 C CNN
F 2 "" H 6100 5775 50  0001 C CNN
F 3 "" H 6100 5775 50  0001 C CNN
	1    6100 5775
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 5775 6100 5625
$Comp
L power:+3.3V #PWR040
U 1 1 5F506231
P 6250 4600
F 0 "#PWR040" H 6250 4450 50  0001 C CNN
F 1 "+3.3V" H 6250 4775 50  0000 C CNN
F 2 "" H 6250 4600 50  0001 C CNN
F 3 "" H 6250 4600 50  0001 C CNN
	1    6250 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5025 5275 5025 5125
Wire Wire Line
	5025 5125 6100 5125
Connection ~ 6100 5125
Wire Wire Line
	6100 5125 6100 5275
Wire Wire Line
	5025 5475 5025 5625
Wire Wire Line
	5025 5625 6100 5625
Connection ~ 6100 5625
Wire Wire Line
	6100 5625 6100 5475
$Comp
L power:GND #PWR039
U 1 1 5F54E709
P 5025 4975
F 0 "#PWR039" H 5025 4725 50  0001 C CNN
F 1 "GND" H 4875 4925 50  0000 C CNN
F 2 "" H 5025 4975 50  0001 C CNN
F 3 "" H 5025 4975 50  0001 C CNN
	1    5025 4975
	1    0    0    -1  
$EndComp
Wire Wire Line
	5025 4975 5025 4925
Wire Wire Line
	5025 4725 5025 4675
$Comp
L Device:R R15
U 1 1 5F58833C
P 4025 5575
F 0 "R15" H 3975 5525 50  0000 R CNN
F 1 "10k" H 3975 5625 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3955 5575 50  0001 C CNN
F 3 "~" H 4025 5575 50  0001 C CNN
F 4 "https://www.chipdip.ru/product0/9000079736" H 4025 5575 50  0001 C CNN "Ссылка"
F 5 "2" H 4025 5575 50  0001 C CNN "Цена"
	1    4025 5575
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR037
U 1 1 5F66F00F
P 3475 4575
F 0 "#PWR037" H 3475 4425 50  0001 C CNN
F 1 "+3.3V" H 3625 4625 50  0000 C CNN
F 2 "" H 3475 4575 50  0001 C CNN
F 3 "" H 3475 4575 50  0001 C CNN
	1    3475 4575
	1    0    0    -1  
$EndComp
Connection ~ 6100 4675
Wire Wire Line
	6100 4675 6100 5125
Wire Wire Line
	4625 5375 4625 5475
Wire Wire Line
	4625 5325 4625 5375
Wire Wire Line
	4325 5375 4625 5375
Wire Wire Line
	4625 4825 4625 5025
$Comp
L power:GND #PWR042
U 1 1 5F778E52
P 4025 5775
F 0 "#PWR042" H 4025 5525 50  0001 C CNN
F 1 "GND" H 4175 5725 50  0000 C CNN
F 2 "" H 4025 5775 50  0001 C CNN
F 3 "" H 4025 5775 50  0001 C CNN
	1    4025 5775
	1    0    0    -1  
$EndComp
Wire Wire Line
	4025 5775 4025 5725
$Comp
L Switch:SW_Push SW2
U 1 1 5F79E074
P 3725 4825
F 0 "SW2" H 3875 4925 50  0000 C CNN
F 1 "Prog_button" H 3725 4725 50  0000 C CNN
F 2 "body_temp:SW_SPST_EVQP7C" H 3725 5025 50  0001 C CNN
F 3 "~" H 3725 5025 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/kls7-ts5401-1.35-250-t" H 3725 4825 50  0001 C CNN "Ссылка"
F 5 "15" H 3725 4825 50  0001 C CNN "Цена"
	1    3725 4825
	1    0    0    -1  
$EndComp
Connection ~ 4625 4825
Wire Wire Line
	3475 4575 3475 4825
Wire Wire Line
	3475 4825 3525 4825
Text Label 5400 5000 0    50   ~ 0
res
Text Label 6400 5375 0    50   ~ 0
boot0
Text Label 1250 4425 2    50   ~ 0
boot0
Wire Wire Line
	1250 4425 1375 4425
Wire Wire Line
	6350 5375 6400 5375
Wire Wire Line
	3925 4825 4025 4825
Wire Wire Line
	4025 4825 4025 5425
Connection ~ 4025 4825
Wire Wire Line
	4025 4825 4625 4825
Text Label 3000 6925 0    50   ~ 0
SCL_puls
Text Label 3000 7025 0    50   ~ 0
SDA_puls
Wire Wire Line
	2900 6925 3000 6925
Wire Wire Line
	2900 7025 3000 7025
Text Label 8000 1700 0    50   ~ 0
int_puls
Wire Wire Line
	7900 1700 8000 1700
Text Label 1350 6975 2    50   ~ 0
int_puls
Wire Wire Line
	1350 6975 1400 6975
Wire Wire Line
	1400 6975 1400 7225
Wire Wire Line
	1400 7225 1500 7225
$Comp
L power:+3.3V #PWR0105
U 1 1 5F71175A
P 11075 625
F 0 "#PWR0105" H 11075 475 50  0001 C CNN
F 1 "+3.3V" H 11090 798 50  0000 C CNN
F 2 "" H 11075 625 50  0001 C CNN
F 3 "" H 11075 625 50  0001 C CNN
	1    11075 625 
	-1   0    0    -1  
$EndComp
$Comp
L Transistor_FET:IRLML6402 Q4
U 1 1 5F711762
P 10800 775
F 0 "Q4" V 10700 675 50  0000 C CNN
F 1 "IRLML6402" V 11050 900 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 11000 700 50  0001 L CIN
F 3 "https://www.infineon.com/dgdl/irlml6402pbf.pdf?fileId=5546d462533600a401535668d5c2263c" H 10800 775 50  0001 L CNN
F 4 "https://www.chipdip.ru/product/irlml6402tr" H 10800 775 50  0001 C CNN "Ссылка"
F 5 "12" H 10800 775 50  0001 C CNN "Цена"
	1    10800 775 
	0    -1   -1   0   
$EndComp
Wire Wire Line
	11075 625  11075 675 
Wire Wire Line
	11075 675  11000 675 
$Comp
L Device:R R18
U 1 1 5F71176D
P 10800 1300
F 0 "R18" H 11000 1250 50  0000 R CNN
F 1 "10k" H 11000 1350 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 10730 1300 50  0001 C CNN
F 3 "~" H 10800 1300 50  0001 C CNN
F 4 "https://www.chipdip.ru/product0/9000079736" H 10800 1300 50  0001 C CNN "Ссылка"
F 5 "2" H 10800 1300 50  0001 C CNN "Цена"
	1    10800 1300
	1    0    0    1   
$EndComp
Wire Wire Line
	10800 1150 10800 1100
$Comp
L power:GND #PWR0106
U 1 1 5F711776
P 10800 1525
F 0 "#PWR0106" H 10800 1275 50  0001 C CNN
F 1 "GND" H 10805 1352 50  0000 C CNN
F 2 "" H 10800 1525 50  0001 C CNN
F 3 "" H 10800 1525 50  0001 C CNN
	1    10800 1525
	-1   0    0    -1  
$EndComp
Wire Wire Line
	10800 1525 10800 1450
$Comp
L Device:R R19
U 1 1 5F71177F
P 11075 1100
F 0 "R19" V 11250 1150 50  0000 R CNN
F 1 "100" V 11175 1175 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 11005 1100 50  0001 C CNN
F 3 "~" H 11075 1100 50  0001 C CNN
F 4 "https://www.chipdip.ru/product0/9000079616" H 11075 1100 50  0001 C CNN "Ссылка"
F 5 "2" H 11075 1100 50  0001 C CNN "Цена"
	1    11075 1100
	0    1    -1   0   
$EndComp
Connection ~ 10800 1100
Wire Wire Line
	10925 1100 10800 1100
Wire Wire Line
	10800 975  10800 1100
Wire Wire Line
	10075 675  10600 675 
Wire Wire Line
	10075 675  10075 825 
$Comp
L power:+3.3V #PWR0108
U 1 1 5F813565
P 8800 2275
F 0 "#PWR0108" H 8800 2125 50  0001 C CNN
F 1 "+3.3V" H 8815 2448 50  0000 C CNN
F 2 "" H 8800 2275 50  0001 C CNN
F 3 "" H 8800 2275 50  0001 C CNN
	1    8800 2275
	1    0    0    -1  
$EndComp
Wire Wire Line
	8800 2275 8800 2325
Wire Wire Line
	8800 2325 8875 2325
$Comp
L Device:R R17
U 1 1 5F813578
P 9075 2875
F 0 "R17" H 9275 2825 50  0000 R CNN
F 1 "10k" H 9275 2925 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9005 2875 50  0001 C CNN
F 3 "~" H 9075 2875 50  0001 C CNN
F 4 "https://www.chipdip.ru/product0/9000079736" H 9075 2875 50  0001 C CNN "Ссылка"
F 5 "2" H 9075 2875 50  0001 C CNN "Цена"
	1    9075 2875
	-1   0    0    1   
$EndComp
Wire Wire Line
	9075 2675 9075 2625
$Comp
L power:GND #PWR0109
U 1 1 5F813581
P 9075 3100
F 0 "#PWR0109" H 9075 2850 50  0001 C CNN
F 1 "GND" H 9080 2927 50  0000 C CNN
F 2 "" H 9075 3100 50  0001 C CNN
F 3 "" H 9075 3100 50  0001 C CNN
	1    9075 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9075 3100 9075 3025
$Comp
L Device:R R16
U 1 1 5F81358A
P 8600 2675
F 0 "R16" V 8775 2725 50  0000 R CNN
F 1 "100" V 8700 2750 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8530 2675 50  0001 C CNN
F 3 "~" H 8600 2675 50  0001 C CNN
F 4 "https://www.chipdip.ru/product0/9000079616" H 8600 2675 50  0001 C CNN "Ссылка"
F 5 "2" H 8600 2675 50  0001 C CNN "Цена"
	1    8600 2675
	0    -1   -1   0   
$EndComp
$Comp
L Transistor_FET:IRLML6402 Q3
U 1 1 5F81356D
P 9075 2425
F 0 "Q3" V 8975 2325 50  0000 C CNN
F 1 "IRLML6402" V 9325 2550 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 9275 2350 50  0001 L CIN
F 3 "https://www.infineon.com/dgdl/irlml6402pbf.pdf?fileId=5546d462533600a401535668d5c2263c" H 9075 2425 50  0001 L CNN
F 4 "https://www.chipdip.ru/product/irlml6402tr" H 9075 2425 50  0001 C CNN "Ссылка"
F 5 "12" H 9075 2425 50  0001 C CNN "Цена"
	1    9075 2425
	0    1    -1   0   
$EndComp
Wire Wire Line
	8750 2675 9075 2675
Wire Wire Line
	9075 2675 9075 2725
Connection ~ 9075 2675
Wire Wire Line
	10300 2325 10300 2425
Wire Wire Line
	9275 2325 9325 2325
Wire Wire Line
	6450 900  6450 1050
Connection ~ 6450 1050
Text Label 11350 1000 1    50   ~ 0
temp_on
Wire Wire Line
	11225 1100 11350 1100
Wire Wire Line
	11350 1100 11350 1000
Text Label 3000 5725 0    50   ~ 0
temp_on
Wire Wire Line
	3000 5725 2900 5725
$Comp
L Device:R R22
U 1 1 5F72F663
P 5475 5375
F 0 "R22" V 5575 5500 50  0000 R CNN
F 1 "10k" V 5575 5325 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5405 5375 50  0001 C CNN
F 3 "~" H 5475 5375 50  0001 C CNN
F 4 "https://www.chipdip.ru/product0/9000079736" H 5475 5375 50  0001 C CNN "Ссылка"
F 5 "2" H 5475 5375 50  0001 C CNN "Цена"
	1    5475 5375
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5275 5375 5325 5375
Wire Wire Line
	5625 5375 5725 5375
$Comp
L Device:R R20
U 1 1 5F789E1F
P 4950 4200
F 0 "R20" V 5050 4375 50  0000 R CNN
F 1 "50k" V 5050 4175 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4880 4200 50  0001 C CNN
F 3 "~" H 4950 4200 50  0001 C CNN
F 4 "https://www.chipdip.ru/product0/9000079753" H 4950 4200 50  0001 C CNN "Ссылка"
F 5 "2" H 4950 4200 50  0001 C CNN "Цена"
	1    4950 4200
	0    -1   -1   0   
$EndComp
$Comp
L Device:CP_Small C12
U 1 1 5F78AF83
P 5150 4350
F 0 "C12" H 4975 4400 50  0000 C CNN
F 1 "10uF" H 4975 4300 50  0000 C CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3216-18_Kemet-A" H 5150 4350 50  0001 C CNN
F 3 "~" H 5150 4350 50  0001 C CNN
F 4 "https://www.chipdip.ru/product0/868717967" H 5150 4350 50  0001 C CNN "Ссылка"
F 5 "16" H 5150 4350 50  0001 C CNN "Цена"
	1    5150 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 4200 4625 4200
Wire Wire Line
	4625 4200 4625 4825
Wire Wire Line
	5150 4250 5150 4200
Wire Wire Line
	5150 4200 5100 4200
$Comp
L power:GND #PWR018
U 1 1 5F7E56B2
P 5150 4550
F 0 "#PWR018" H 5150 4300 50  0001 C CNN
F 1 "GND" H 5000 4500 50  0000 C CNN
F 2 "" H 5150 4550 50  0001 C CNN
F 3 "" H 5150 4550 50  0001 C CNN
	1    5150 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 4550 5150 4450
Wire Wire Line
	5025 4675 6100 4675
$Comp
L Device:R R21
U 1 1 5F814066
P 5325 4375
F 0 "R21" H 5525 4425 50  0000 R CNN
F 1 "150k" H 5575 4325 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5255 4375 50  0001 C CNN
F 3 "~" H 5325 4375 50  0001 C CNN
F 4 "" H 5325 4375 50  0001 C CNN "Ссылка"
F 5 "2" H 5325 4375 50  0001 C CNN "Цена"
	1    5325 4375
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 4200 5325 4200
Wire Wire Line
	5325 4200 5325 4225
Connection ~ 5150 4200
$Comp
L power:GND #PWR026
U 1 1 5F8711F7
P 5325 4550
F 0 "#PWR026" H 5325 4300 50  0001 C CNN
F 1 "GND" H 5475 4500 50  0000 C CNN
F 2 "" H 5325 4550 50  0001 C CNN
F 3 "" H 5325 4550 50  0001 C CNN
	1    5325 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5325 4550 5325 4525
Wire Wire Line
	5675 4100 5675 4050
Wire Wire Line
	5675 4050 6100 4050
Wire Wire Line
	6100 4050 6100 4675
Wire Wire Line
	5375 4200 5325 4200
Connection ~ 5325 4200
$Comp
L power:GND #PWR043
U 1 1 5F8D9451
P 5675 4550
F 0 "#PWR043" H 5675 4300 50  0001 C CNN
F 1 "GND" H 5825 4500 50  0000 C CNN
F 2 "" H 5675 4550 50  0001 C CNN
F 3 "" H 5675 4550 50  0001 C CNN
	1    5675 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5675 4550 5675 4300
Wire Wire Line
	5275 4825 5300 4825
Wire Wire Line
	5300 5000 5300 4825
Wire Wire Line
	5300 5000 5400 5000
Wire Wire Line
	5725 5375 5725 5050
Wire Wire Line
	5725 5050 6000 5050
Wire Wire Line
	6000 5050 6000 4825
Wire Wire Line
	6000 4200 5925 4200
Connection ~ 5725 5375
Wire Wire Line
	5725 5375 5800 5375
Wire Wire Line
	5800 4825 6000 4825
Connection ~ 6000 4825
Wire Wire Line
	6000 4825 6000 4200
Wire Wire Line
	5500 4825 5300 4825
Connection ~ 5300 4825
Wire Wire Line
	1450 4225 1500 4225
Wire Wire Line
	1225 6225 1225 6125
Wire Wire Line
	1225 6575 1225 6525
$Comp
L power:GND #PWR034
U 1 1 5FE1AF96
P 1225 6575
F 0 "#PWR034" H 1225 6325 50  0001 C CNN
F 1 "GND" H 1225 6425 50  0000 C CNN
F 2 "" H 1225 6575 50  0001 C CNN
F 3 "" H 1225 6575 50  0001 C CNN
	1    1225 6575
	1    0    0    -1  
$EndComp
$Comp
L Device:R R13
U 1 1 5FE1ABA8
P 1225 6375
F 0 "R13" H 1375 6425 50  0000 C CNN
F 1 "1k" H 1375 6325 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1155 6375 50  0001 C CNN
F 3 "~" H 1225 6375 50  0001 C CNN
F 4 "https://www.chipdip.ru/product0/9000079676" H 1225 6375 50  0001 C CNN "Ссылка"
F 5 "2" H 1225 6375 50  0001 C CNN "Цена"
	1    1225 6375
	1    0    0    -1  
$EndComp
Wire Wire Line
	1225 5825 1225 5625
Wire Wire Line
	1025 5525 1025 5825
Wire Wire Line
	1025 6575 1025 6525
$Comp
L power:GND #PWR033
U 1 1 5FDDB303
P 1025 6575
F 0 "#PWR033" H 1025 6325 50  0001 C CNN
F 1 "GND" H 1025 6425 50  0000 C CNN
F 2 "" H 1025 6575 50  0001 C CNN
F 3 "" H 1025 6575 50  0001 C CNN
	1    1025 6575
	1    0    0    -1  
$EndComp
$Comp
L Device:LED_ALT D3
U 1 1 5FDDA5E4
P 1225 5975
F 0 "D3" V 1325 5925 50  0000 R CNN
F 1 "Led2" V 1225 5900 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 1225 5975 50  0001 C CNN
F 3 "~" H 1225 5975 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/to-1608bc-bf" H 1225 5975 50  0001 C CNN "Ссылка"
F 5 "7" H 1225 5975 50  0001 C CNN "Цена"
	1    1225 5975
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1025 6125 1025 6225
$Comp
L Device:R R12
U 1 1 5FDC9B23
P 1025 6375
F 0 "R12" H 875 6425 50  0000 C CNN
F 1 "1k" H 875 6325 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 955 6375 50  0001 C CNN
F 3 "~" H 1025 6375 50  0001 C CNN
F 4 "https://www.chipdip.ru/product0/9000079676" H 1025 6375 50  0001 C CNN "Ссылка"
F 5 "2" H 1025 6375 50  0001 C CNN "Цена"
	1    1025 6375
	1    0    0    -1  
$EndComp
$Comp
L Device:LED_ALT D5
U 1 1 5F6673F8
P 1025 5975
F 0 "D5" V 1125 6125 50  0000 R CNN
F 1 "Led1" V 1025 6200 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 1025 5975 50  0001 C CNN
F 3 "~" H 1025 5975 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/to-1608bc-bf" H 1025 5975 50  0001 C CNN "Ссылка"
F 5 "7" H 1025 5975 50  0001 C CNN "Цена"
	1    1025 5975
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1025 5525 1500 5525
Wire Wire Line
	1225 5625 1500 5625
Wire Wire Line
	5525 3700 5525 3775
Wire Wire Line
	5625 3700 5625 3775
Wire Wire Line
	5625 3775 5525 3775
Connection ~ 5525 3775
Wire Wire Line
	5525 3775 5525 3850
Wire Wire Line
	6250 4600 6250 4675
Wire Wire Line
	6250 4675 6100 4675
$Comp
L 74xGxx:74LVC2G14 U10
U 1 1 5FBFF322
P 6100 5375
F 0 "U10" H 5975 5550 50  0000 C CNN
F 1 "74LVC2G14" H 6325 5500 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 6100 5375 50  0001 C CNN
F 3 "https://www.ti.com/lit/ds/symlink/sn74lvc2g14.pdf" H 6100 5375 50  0001 C CNN
	1    6100 5375
	1    0    0    -1  
$EndComp
$Comp
L 74xGxx:74LVC2G14 U10
U 2 1 5FBFF7FA
P 5675 4200
F 0 "U10" H 5325 4300 50  0000 C CNN
F 1 "74LVC2G14" H 5450 4375 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 5675 4200 50  0001 C CNN
F 3 "https://www.ti.com/lit/ds/symlink/sn74lvc2g14.pdf" H 5675 4200 50  0001 C CNN
	2    5675 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 2675 8450 2675
Wire Wire Line
	9700 2825 9325 2825
Wire Wire Line
	9325 2825 9325 2325
Connection ~ 9325 2325
Wire Wire Line
	9325 2325 10300 2325
$Comp
L Device:LED_ALT D7
U 1 1 5F7409F3
P 1375 4625
F 0 "D7" V 1400 4925 50  0000 R CNN
F 1 "Прог. вкл" V 1275 5025 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 1375 4625 50  0001 C CNN
F 3 "~" H 1375 4625 50  0001 C CNN
F 4 "https://www.chipdip.ru/product/to-1608bc-bf" H 1375 4625 50  0001 C CNN "Ссылка"
F 5 "7" H 1375 4625 50  0001 C CNN "Цена"
	1    1375 4625
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1375 4475 1375 4425
Connection ~ 1375 4425
Wire Wire Line
	1375 4425 1500 4425
$Comp
L Device:R R23
U 1 1 5F777680
P 1375 4975
F 0 "R23" H 1250 5000 50  0000 C CNN
F 1 "1k" H 1275 4925 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1305 4975 50  0001 C CNN
F 3 "~" H 1375 4975 50  0001 C CNN
F 4 "https://www.chipdip.ru/product0/9000079676" H 1375 4975 50  0001 C CNN "Ссылка"
F 5 "2" H 1375 4975 50  0001 C CNN "Цена"
	1    1375 4975
	1    0    0    -1  
$EndComp
Wire Wire Line
	1375 4825 1375 4775
$Comp
L power:GND #PWR044
U 1 1 5F792E72
P 1375 5200
F 0 "#PWR044" H 1375 4950 50  0001 C CNN
F 1 "GND" H 1375 5050 50  0000 C CNN
F 2 "" H 1375 5200 50  0001 C CNN
F 3 "" H 1375 5200 50  0001 C CNN
	1    1375 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1375 5200 1375 5125
$EndSCHEMATC
