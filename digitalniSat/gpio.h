#ifndef GPIO_H
#define GPIO_H

#include "stdint.h"

void init_gpio(void);
void setP2(uint8_t port2);
uint8_t getP0(void);

#endif
