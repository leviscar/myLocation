from ctypes import *
cdll_names ={
	'dw1000': 'dw1000.so'

}

clib = CDLL("./dw1000.so")
i=0
while i<10:
	clib.deca_sleep(500)
	print(clib.spiPiSetup(0,1000000))
	i = i+1;
	print(i)
i=0
