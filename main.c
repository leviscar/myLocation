
#include "main.h"



void getIDs(unsigned char index);
void setIDs(void);
static void dw1000_init(void);
static void system_init(void);


static dwt_config_t config = {
    1,               /* Channel number. */
    DWT_PRF_16M,     /* Pulse repetition frequency. */
    DWT_PLEN_128,   /* Preamble length. Used in TX only. */
    DWT_PAC8,       /* Preamble acquisition chunk size. Used in RX only. */
    2,               /* TX preamble code. Used in TX only. */
    2,               /* RX preamble code. Used in RX only. */
    0,               /* 0 to use standard SFD, 1 to use non-standard SFD. */
    DWT_BR_6M8,     /* Data rate. */
    DWT_PHRMODE_STD, /* PHY header mode. */
    (129 + 8 - 8) /* SFD timeout (preamble length + 1 + SFD length - PAC size). Used in RX only. */
};
sys_config_t sys_config={
	.timebase=0,
	.ACtype=0,
	.id=ANCHOR_NUM,
	.TBfreq=1000,
	.acnum=ANCHORCNT,
};
uint8_t nrf_Tx_Buffer[33] ; // nrfÎÞÏß´«Êä·¢ËÍÊý¾Ý
uint8_t nrf_Rx_Buffer[33] ; // nrfÎÞÏß´«Êä½ÓÊÕÊý¾Ý
/* Frames used in the ranging process. See NOTE 2 below. */
/* Buffer to store received response message.
 * Its size is adjusted to longest frame that this example code is supposed to handle. */
static uint16 pan_id = 0xDECA;
static uint8 eui[] = {'A', 'C', 'K', 'D', 'A', 'T', 'R', 'X'};
static uint16 Achor_addr = ANCHOR_NUM; /* "RX" */

uint8 rx_buffer[RX_BUF_LEN];
volatile uint8 DMA_transing=0;
uint8 frame_seq_nb=0;
//uint8 ACKframe[12]={0x41, 0x88, 0, 0xCA, 0xDE, 0x00, 0x00, 0x00, 0x00, 0xAC, 0, 0};
uint8 ACKframe[5]={ACK_FC_0,ACK_FC_1,0,0,0};
uint8 send_pc[20]={0xFB, 0xFB, 0x11, 0, 0, 0x02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8 dw_payloadbuff[127];
uint16 TBsyctime=0xff;
float *pglobalmpudata;
int idxreco=-1;
uint16 TAG_datacnt=0;
uint8 crc=0;
uint8 QuantityAC=QUANTITY_ANCHOR;
uint8 TBPOLL[TDOAMSGLEN] = {0x41, 0x88, 0, 0xCA, 0xDE, 0xFF, 0xFF, 0, 0, 0x80, 0, 0};

LIST_HEAD(TAG_list);

typedef struct
{
	uint16 Mark;
	uint16 Tagid;
	uint8 Idx;
	uint8 Accnt;
	uint8 Rangingtype;
	uint8 Mpu;
	uint16 datalen;
}	Headdata_t;

int pin_irq = 24;


int main(void)
{

		int spi1;
		int i=0;
		int pin_ss = 27;
		int clock = 4000000;
		int spiChannel = 0;
		wiringPiSetup();
		pinMode(pin_ss,OUTPUT);
		spi1 = wiringPiSPISetup(spiChannel,clock);
		if(spi1<0)
		{
			printf("error: spi \n");
		}

		delay(1000);
		for(i=0;i<8;i++)
		{
			delay(500);
			getIDs(i);
		}

		return 0;

}



void getIDs(unsigned char index)
{
	uint8 headbuff[1]={0x00};
	uint8 headlength=1;
	uint8 bodylength=4;
	uint8 bodybuff[4];
	readfromspi(headlength,headbuff,bodylength,bodybuff);
	printf("%x\r\n",bodybuff[index]);
}

void setIDs(void)
{
	uint8 headbuff[1]={0x80};
	uint8 headlength=1;
	uint8 bodylength=4;
	uint8 bodybuff[4]={0xAA,0x02,0x03,0xCA};
	writetospi(headlength,headbuff,bodylength,bodybuff);
}



