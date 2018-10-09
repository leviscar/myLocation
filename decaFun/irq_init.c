#include <decaFun/irq_init.h>
port_deca_isr_t port_deca_isr = 0;

void dw1000IRQ_init(void)
{
	// use RPI_V2_GPIO_P1_35 as irq pin
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_35,BCM2835_GPIO_FSEL_INPT);
	// with a pullup
	bcm2835_gpio_set_pud(RPI_V2_GPIO_P1_35,BCM2835_GPIO_PUD_UP);
	// and a rising detect enable
	bcm2835_gpio_ren(RPI_V2_GPIO_P1_35);
}

void port_set_deca_isr(port_deca_isr_t deca_isr)
{

    /* If needed, deactivate DW1000 IRQ during the installation of the new handler. */

    port_deca_isr = deca_isr;

}
