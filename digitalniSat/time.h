#ifndef TIME_H
#define TIME_H

#include "stdint.h"

typedef struct {
    uint8_t sat;
    uint8_t min;
    uint8_t sek;
} TIME;

extern TIME trenutno_vreme;
extern TIME alarm_vreme;

extern bit sekunda_prosla;
extern bit sat_radi;
extern bit alarm_flag;

void timer2_init(void);
void time_tick(void);
uint8_t vreme_poklapanje(void);

#endif