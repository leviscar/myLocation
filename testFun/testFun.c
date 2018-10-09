/*
 * testFun.c
 *
 *  Created on: Jun 5, 2018
 *      Author: leviscar
 */



#include "testFun.h"
uint32 time_record;
uint32 time_stack[10];
uint16 timestack_cnt=0;
uint8 triggle=0;
//void System_GetClocks(void)
//{
//  RCC_ClocksTypeDef rcc_clocks;
//
//  RCC_GetClocksFreq(&rcc_clocks);
//
//  printf("SYSCLK    = %dMHz\r\n", rcc_clocks.SYSCLK_Frequency / 1000000);
//  printf("HCLK(AHB) = %dMHz\r\n", rcc_clocks.HCLK_Frequency / 1000000);
//  printf("HCLK(AHB) = %dMHz\r\n", rcc_clocks.HCLK_Frequency / 1000000);
//  printf("PCLK(APB) = %dMHz\r\n", rcc_clocks.PCLK_Frequency / 1000000);
//}



void getSYSstatus(void)
{
	uint32 status_reg;
	status_reg = dwt_read32bitreg(SYS_STATUS_ID);
	printf("0x%lx\r\n",status_reg);

}
void getIDs(unsigned char index)
{
	uint8 headbuff[1]={0x00};
	uint8 headlength=1;
	uint8 bodylength=4;
	uint8 bodybuff[4];
	readfromspi(headlength,headbuff,bodylength,bodybuff);
	printf("%d\r\n",bodybuff[index]);
}

void read_test(unsigned char add)
{
	uint32 id;
	id=dwt_readdevid();
	printf("%lx\r\n",id);

}


// this func is wrote for show led register
void read_led(void)
{
	uint32 reg;
	reg = dwt_read32bitoffsetreg(GPIO_CTRL_ID, GPIO_MODE_OFFSET);
	printf("%lx\r\n",reg);
}

//void Prt_anchnum(void)
//{
//	static int i=ANCHOR_NUM;
//	printf("anchor num=%d\r\n",i);
//}
//
//void testfun1(void)
//{
//	uint8 txframe[19]={0x61,0x88,0x00,0xca,0xde,0x01,0x00,0x02,0x00,0xa1,0x02,0x00,0xac,0x2e,0x9d,0x7d,0x3d,0,0};
//	dwt_forcetrxoff();
//	dwt_writetxdata((19), txframe, 0); /* Zero offset in TX buffer. */
//	dwt_writetxfctrl((19), 0, 1); /* Zero offset in TX buffer, ranging. */
//	printf("testfun1 executed!\r\n");
//	dwt_starttx(DWT_START_TX_IMMEDIATE|DWT_RESPONSE_EXPECTED);
//}
//void testfun2(void)
//{
//	uint8 txframe[19]={0x41,0x88,0x00,0xca,0xde,0xFF,0xFF,0x01,0x00,0xa0,0,0,0xac,0x2e,0x9d,0x7d,0x3d,0,0};
//	dwt_forcetrxoff();
//	dwt_writetxdata((12), txframe, 0); /* Zero offset in TX buffer. */
//	dwt_writetxfctrl((12), 0, 1); /* Zero offset in TX buffer, ranging. */
//	printf("testfun2 executed!\r\n");
//	dwt_starttx(DWT_START_TX_IMMEDIATE|DWT_RESPONSE_EXPECTED);
//}



//void GET_Time2Tpoint(void)
//{
//	uint32 timetmp;
//	timetmp=dwt_readsystimestamphi32();
//	time_stack[timestack_cnt++]=timetmp-time_record;//µÍ¾ÅÎ»Îª³£0£¬¼Ä´æÆ÷40Î»·Ö±æÂÊ15.65ps£¬¸ß32Î»×Ö½Ú·Ö±æÂÊ4.006ns
//
//}

