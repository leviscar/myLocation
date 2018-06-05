/*
 * testFun.h
 *
 *  Created on: Jun 5, 2018
 *      Author: leviscar
 */

#ifndef TESTFUN_TESTFUN_H_
#define TESTFUN_TESTFUN_H_
#include "main.h"
#include "deca_regs.h"
#include "deca_device_api.h"
void unlockflash(unsigned int passwd);
void testfun1(void);
void testfun2(void);
void DMA_test(void);
void SET_Tpoint(void);
void GET_Time2Tpoint(void);
void ShowTimeStack(void);
void getSYSstatus(void);
void read_test(unsigned char add);
extern uint32 time_record;
extern uint32 time_stack[];
extern uint16 timestack_cnt;
void going(void);
extern uint8 triggle;
#define HAULT_POINT {while(!triggle);triggle=0;}


#endif /* TESTFUN_TESTFUN_H_ */
