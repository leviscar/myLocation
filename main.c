
#include "main.h"


//static void dw1000_init(void);
//static void system_init(void);
//
//
//static dwt_config_t config = {
//    1,               /* Channel number. */
//    DWT_PRF_16M,     /* Pulse repetition frequency. */
//    DWT_PLEN_128,   /* Preamble length. Used in TX only. */
//    DWT_PAC8,       /* Preamble acquisition chunk size. Used in RX only. */
//    2,               /* TX preamble code. Used in TX only. */
//    2,               /* RX preamble code. Used in RX only. */
//    0,               /* 0 to use standard SFD, 1 to use non-standard SFD. */
//    DWT_BR_6M8,     /* Data rate. */
//    DWT_PHRMODE_STD, /* PHY header mode. */
//    (129 + 8 - 8) /* SFD timeout (preamble length + 1 + SFD length - PAC size). Used in RX only. */
//};
//sys_config_t sys_config={
//	.timebase=0,
//	.ACtype=0,
//	.id=ANCHOR_NUM,
//	.TBfreq=1000,
//	.acnum=ANCHORCNT,
//};
//uint8_t nrf_Tx_Buffer[33] ; // nrfÎÞÏß´«Êä·¢ËÍÊý¾Ý
//uint8_t nrf_Rx_Buffer[33] ; // nrfÎÞÏß´«Êä½ÓÊÕÊý¾Ý
///* Frames used in the ranging process. See NOTE 2 below. */
///* Buffer to store received response message.
// * Its size is adjusted to longest frame that this example code is supposed to handle. */
//static uint16 pan_id = 0xDECA;
//static uint8 eui[] = {'A', 'C', 'K', 'D', 'A', 'T', 'R', 'X'};
//static uint16 Achor_addr = ANCHOR_NUM; /* "RX" */
//
//uint8 rx_buffer[RX_BUF_LEN];
//volatile uint8 DMA_transing=0;
//uint8 frame_seq_nb=0;
////uint8 ACKframe[12]={0x41, 0x88, 0, 0xCA, 0xDE, 0x00, 0x00, 0x00, 0x00, 0xAC, 0, 0};
//uint8 ACKframe[5]={ACK_FC_0,ACK_FC_1,0,0,0};
//uint8 send_pc[20]={0xFB, 0xFB, 0x11, 0, 0, 0x02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//uint8 dw_payloadbuff[127];
//uint16 TBsyctime=0xff;
//float *pglobalmpudata;
//int idxreco=-1;
//uint16 TAG_datacnt=0;
//uint8 crc=0;
//uint8 QuantityAC=QUANTITY_ANCHOR;
//uint8 TBPOLL[TDOAMSGLEN] = {0x41, 0x88, 0, 0xCA, 0xDE, 0xFF, 0xFF, 0, 0, 0x80, 0, 0};
//
//LIST_HEAD(TAG_list);
//
//typedef struct
//{
//	uint16 Mark;
//	uint16 Tagid;
//	uint8 Idx;
//	uint8 Accnt;
//	uint8 Rangingtype;
//	uint8 Mpu;
//	uint16 datalen;
//}	Headdata_t;

int pin_irq = 24;


int main(void)
{

//		int spi1;
		int i=0;
//		int pin_ss = 27;
//		int clock = 4000000;
//		int spiChannel = 0;
//		uint32 addtime;
//		uint32 txtime;
//		addtime=(uint32)((float)sys_config.TBfreq/0.0000040064);

//		wiringPiSetup();
//		pinMode(pin_ss,OUTPUT);
//		spi1 = wiringPiSPISetup(spiChannel,clock);
		openspi();
		printf("test01\n");
//		if(spi1<0)
//		{
//			printf("error: spi \n");
//		}

		delay(1000);
		for(i=0;i<8;i++)
		{
//			delay(500);
			getSYSstatus();
			read_test(0);
			deca_sleep(500);
		}

		return 0;

}


//static void system_init(void)
//{
//	dw1000_init();
//	if(sys_config.id==1)
//	{
//		sys_config.ACtype=0;
//	}
//	else
//	{
//		sys_config.ACtype=1;
//	}
//	if(!sys_config.ACtype)
//	{
//		DMA_init();
//	}
//	if(!sys_config.timebase)
//	{
//		dwt_rxenable(DWT_START_RX_IMMEDIATE);
//	}
//	else
//	{
//		sys_config.id=0;
//		TBPOLL[FRAME_SN_IDX]=frame_seq_nb++;
//		TBPOLL[WLIDX]=0;
//		TBPOLL[WRIDX]=0;
//		TBPOLL[UWBFREQ1]=(uint8)sys_config.TBfreq;
//		TBPOLL[UWBFREQ2]=(uint8)(sys_config.TBfreq>>8);
//		dwt_writetxdata(sizeof(TBPOLL), TBPOLL, 0); /* Zero offset in TX buffer. */
//		dwt_writetxfctrl(sizeof(TBPOLL), 0, 1); /* Zero offset in TX buffer, ranging. */
//		dwt_starttx(DWT_START_TX_IMMEDIATE);
//
//	}
//	pglobalmpudata=(float*)malloc(MAX_MPUDATA_CNT);
//
//
//}
//
//static void dw1000_init(void)
//{
//	decaIrqStatus_t  stat ;
//	reset_DW1000();
//	if (dwt_initialise(DWT_LOADUCODE) == DWT_ERROR)	//dw1000 init
//	{
//			printf("INIT FAILED\r\n");
//			while (1)
//			{ };
//	}
//	else
//	{
//			printf("UWB Device initialised\r\n");
//	}
//
//		dw1000IRQ_init();
//		stat = decamutexon() ;
//		set_spi_high();
//		dwt_configure(&config);
//		dwt_setleds(DWT_LEDS_ENABLE);
//		port_set_deca_isr(dwt_isr);
//		decamutexoff(stat) ;
////--------------------------------
//		/* Apply default antenna delay value. See NOTE 2 below. */
//    dwt_setrxantennadelay(RX_ANT_DLY);
//    dwt_settxantennadelay(TX_ANT_DLY);
//		 /* Set expected response's delay and timeout. See NOTE 1 and 5 below.
//     * As this example only handles one incoming frame with always the same delay and timeout, those values can be set here once for all. */
//		dwt_write32bitreg(SYS_STATUS_ID, SYS_STATUS_RXFCG|SYS_STATUS_SLP2INIT);
//    dwt_setinterrupt(DWT_INT_ALLERR|DWT_INT_TFRS|DWT_INT_RFCG|DWT_INT_RFTO,1);
//		//dw_setARER(1);
//		dwt_setcallbacks(&tx_conf_cb, &rx_ok_cb, &rx_to_cb, &rx_err_cb);
//
//		dwt_setpanid(pan_id);
//    dwt_seteui(eui);
//    dwt_setaddress16(Achor_addr);
//
//    /* Configure frame filtering. Only data frames are enabled in this example. Frame filtering must be enabled for Auto ACK to work. */
//		dwt_enableframefilter(DWT_FF_DATA_EN|DWT_FF_ACK_EN);
//
//    /* Activate auto-acknowledgement. Time is set to 0 so that the ACK is sent as soon as possible after reception of a frame. */
//    dwt_enableautoack(8);
//		dwt_setrxtimeout(0);
//		dwt_setlnapamode(1,1);
//		dwt_write16bitoffsetreg(PMSC_ID,PMSC_RES3_OFFSET+2,0);
//}


