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
Wire Wire Line
	4700 3500 3300 3500
Wire Wire Line
	3300 3500 3300 3900
Wire Wire Line
	4000 3900 4700 3900
Wire Wire Line
	6300 3200 6900 3200
Wire Wire Line
	6900 3200 6900 3300
Wire Wire Line
	6300 3300 6700 3300
Wire Wire Line
	6700 3300 6700 3600
Wire Wire Line
	6700 3600 6900 3600
Wire Wire Line
	4700 3800 4400 3800
Wire Wire Line
	4400 3800 4400 5100
Wire Wire Line
	4400 5100 8300 5100
Wire Wire Line
	8300 5100 8300 3300
Wire Wire Line
	8300 3300 8000 3300
$Comp
L eagle_ChristmasLights-eagle-import:ARDUINO_NANO ARDUINO_NANO1
U 1 1 8CDB80C1
P 5500 4100
F 0 "ARDUINO_NANO1" H 4900 3300 59  0000 L BNN
F 1 "ARDUINO_NANO" H 4900 3200 59  0000 L BNN
F 2 "eagle_ChristmasLights:ARDUINO_NANO" H 5500 4100 50  0001 C CNN
F 3 "" H 5500 4100 50  0001 C CNN
	1    5500 4100
	1    0    0    -1  
$EndComp
$Comp
L eagle_ChristmasLights-eagle-import:FSM6JSMA SW1
U 1 1 E9E31E47
P 3700 4000
F 0 "SW1" H 3400 4220 59  0000 L BNN
F 1 "FSM6JSMA" H 3400 3709 59  0000 L BNN
F 2 "eagle_ChristmasLights:FSM6JSMA" H 3700 4000 50  0001 C CNN
F 3 "" H 3700 4000 50  0001 C CNN
	1    3700 4000
	1    0    0    -1  
$EndComp
$Comp
L eagle_ChristmasLights-eagle-import:WS2812" U1
U 1 1 C40DF5FE
P 7500 3500
F 0 "U1" H 7000 3830 59  0000 L BNN
F 1 "WS2812" H 7000 3200 59  0000 L BNN
F 2 "eagle_ChristmasLights:LED-TRICOLOR-5050-IC" H 7500 3500 50  0001 C CNN
F 3 "" H 7500 3500 50  0001 C CNN
	1    7500 3500
	1    0    0    -1  
$EndComp
Text GLabel 6300 3500 0    10   BiDi ~ 0
5V
$EndSCHEMATC
