#include "time.h"
#include "serijska.h"
#include "at89c51rc2.h"

TIME trenutno_vreme = {0,0,0};
TIME alarm_vreme = {0,0,0};

uint8_t alarm[]  = "ALARM\r\n";

bit sekunda_prosla = 0;
bit sat_radi = 1;
bit alarm_flag=0;

void timer2_init(void) {
    T2CON = 0x00;
    RCAP2H = 0x3C;
    RCAP2L = 0xB0;   
    TH2 = RCAP2H;
    TL2 = RCAP2L;

    ET2 = 1;
    TR2 = 1;
}

void timer2_ISR(void) interrupt 5 {
    static uint16_t ms = 0;
  
    TF2 = 0;

    ms++;
    if(ms >= 20) {          
        ms = 0;

        if(sat_radi) {      
            time_tick();

            if(trenutno_vreme.sat == alarm_vreme.sat &&
               trenutno_vreme.min == alarm_vreme.min &&
               trenutno_vreme.sek >= alarm_vreme.sek && trenutno_vreme.sek <= (alarm_vreme.sek) && !alarm_flag) {
                alarm_flag=1;

            }
        }   
    }
}


void time_tick(void) {
    trenutno_vreme.sek++;

    if(trenutno_vreme.sek == 60) {
        trenutno_vreme.sek = 0;
        trenutno_vreme.min++;
    }
    if(trenutno_vreme.min == 60) {
        trenutno_vreme.min = 0;
        trenutno_vreme.sat++;
    }
    if(trenutno_vreme.sat == 24) {
        trenutno_vreme.sat = 0;
    }
}
/*
uint8_t vreme_poklapanje(void) {
    return (trenutno_vreme.sat == alarm_vreme.sat &&
            trenutno_vreme.min == alarm_vreme.min &&
            trenutno_vreme.sek == alarm_vreme.sek);
}
*/