#include "gpio.h"
#include "at89c51rc2.h"

void init_gpio(void)
{
    P2 = 0x00;
    P0 = 0xFF;
}

void setP2(uint8_t port2){ P2 = port2; }
uint8_t getP0(void){ return P0; }
