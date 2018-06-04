#include <string.h>
#include <stdio.h>
#include "deca_device_api.h"
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include "linux/spi/spidev.h"


int pin_ss = 27;

int spiPiSetup(int channel, int clock)
{

	wiringPiSetup();
	pinMode(pin_ss,OUTPUT);
	printf("new\r\n");
	return wiringPiSPISetup(channel,clock);
}



int writetospi(uint16 headerLength, uint8 *headerBuffer, uint32 bodylength, uint8 *bodyBuffer)
{
	int i=0;

    decaIrqStatus_t  stat ;

    stat = decamutexon() ;// global interrupter on

    digitalWrite(pin_ss, LOW);
    for(i=0;i<headerLength;i++)
    {
		wiringPiSPIDataRW(0,headerBuffer,sizeof(headerBuffer));

	}

	for(i=0; i<bodylength; i++)
    {
     	wiringPiSPIDataRW(0,bodyBuffer,sizeof(bodyBuffer));
	}
	digitalWrite(pin_ss, HIGH);

    decamutexoff(stat) ; //  global interrupter off

    return 0;
}



int readfromspi(uint16 headerLength, uint8 *headerBuffer, uint32 readlength, uint8 *readBuffer)
{
	int i=0;

    decaIrqStatus_t  stat ;

    stat = decamutexon() ;



    digitalWrite(pin_ss, LOW);
    for(i=0;i<headerLength;i++)
    {
		wiringPiSPIDataRW(0,headerBuffer,sizeof(headerBuffer));

	}

	for(i=0; i<readlength; i++)
    {
     	wiringPiSPIDataRW(0,readBuffer,sizeof(readBuffer));
	}

	digitalWrite(pin_ss, HIGH);


    decamutexoff(stat) ;
    return 0;
}
