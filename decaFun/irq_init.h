/*
 * irq_init.h
 *
 *  Created on: Jun 6, 2018
 *      Author: leviscar
 */

#ifndef DECAFUN_IRQ_INIT_H_
#define DECAFUN_IRQ_INIT_H_
#include "main.h"
#include <bcm2835.h>

typedef void (*port_deca_isr_t)(void);
/* DW1000 IRQ handler declaration. */
extern port_deca_isr_t port_deca_isr;

void dw1000IRQ_init(void);
void port_set_deca_isr(port_deca_isr_t deca_isr);
#endif /* DECAFUN_IRQ_INIT_H_ */
