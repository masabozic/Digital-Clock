#ifndef SERIJSKA_H
#define SERIJSKA_H

#include "stdint.h"

void serial_init(void);
void posalji_poruku(char *s);
void parsiraj_poruku(void);

#endif