#include "at89c51rc2.h"
#include "time.h"
#include "serijska.h"
#include "display.h"

unsigned char alarm_poslat = 0;  

#define TASTER_VREME_SAT   P0_0
#define TASTER_VREME_MIN   P0_1
#define TASTER_VREME_SEK   P0_2

#define TASTER_ALARM_SAT   P0_3
#define TASTER_ALARM_MIN   P0_4
#define TASTER_ALARM_SEK   P0_5

#define TASTER_STOP   P0_6
#define TASTER_START  P0_7

void delay50ms(void) {
    uint8_t i, j;
    for(i=0;i<50;i++)
        for(j=0;j<120;j++);
}

void main(void) {

    
   	// P1 = 0xFF;

	P0 = 0xFF;

    serial_init();
    timer2_init();
    initDisplay();
    EA = 1;

	while(TASTER_VREME_SAT == 0 ||
      TASTER_VREME_MIN == 0 ||
      TASTER_VREME_SEK == 0 ||
      TASTER_ALARM_SAT == 0 ||
      TASTER_ALARM_MIN == 0 ||
      TASTER_ALARM_SEK == 0);
		delay50ms();

    

    while(1) {

		
        uint8_t buf[9];

  		 clearDisplay();

	 /* ----- ALARM ----- */
	if(alarm_flag){

		posalji_poruku((uint8_t*) "ALARM\r\n" );

		alarm_flag=0;
	}

        /* ----- LCD ----- */
       
        buf[0] = trenutno_vreme.sat/10 + '0';
        buf[1] = trenutno_vreme.sat%10 + '0';
        buf[2] = ':';
        buf[3] = trenutno_vreme.min/10 + '0';
        buf[4] = trenutno_vreme.min%10 + '0';
        buf[5] = ':';
        buf[6] = trenutno_vreme.sek/10 + '0';
        buf[7] = trenutno_vreme.sek%10 + '0';
        buf[8] = 0;
        writeLine(buf);

        newLine();

       
        buf[0] = alarm_vreme.sat/10 + '0';
        buf[1] = alarm_vreme.sat%10 + '0';
        buf[2] = ':';
        buf[3] = alarm_vreme.min/10 + '0';
        buf[4] = alarm_vreme.min%10 + '0';
        buf[5] = ':';
        buf[6] = alarm_vreme.sek/10 + '0';
        buf[7] = alarm_vreme.sek%10 + '0';
        buf[8] = 0;
        writeLine(buf);

        delay50ms();

  /* ----- TASTERI ? VREME ----- */
	if(TASTER_VREME_SAT == 0) {
    	trenutno_vreme.sat = (trenutno_vreme.sat + 1) % 24;
    	while(TASTER_VREME_SAT == 0);  
    		delay50ms();
	}

	if(TASTER_VREME_MIN == 0) {
    	trenutno_vreme.min++;
    	if(trenutno_vreme.min >= 60) {
        	trenutno_vreme.min = 0;
        	trenutno_vreme.sat = (trenutno_vreme.sat + 1) % 24;
    }

    while(TASTER_VREME_MIN == 0);
    delay50ms();
	}

	if(TASTER_VREME_SEK == 0) {
    	trenutno_vreme.sek++;
    	if(trenutno_vreme.sek >= 60) {
        	trenutno_vreme.sek = 0;
        	trenutno_vreme.min++;
        if(trenutno_vreme.min >= 60) {
            trenutno_vreme.min = 0;
            trenutno_vreme.sat = (trenutno_vreme.sat + 1) % 24;
        }
    }
    while(TASTER_VREME_SEK == 0);
    delay50ms();
	}

/* ----- TASTERI ? ALARM ----- */
	if(TASTER_ALARM_SAT == 0) {
   		 alarm_vreme.sat = (alarm_vreme.sat + 1) % 24;
   		 while(TASTER_ALARM_SAT == 0);
    		delay50ms();
	}

	if(TASTER_ALARM_MIN == 0) {
    	alarm_vreme.min++;
    if(alarm_vreme.min >= 60) {
        alarm_vreme.min = 0;
        alarm_vreme.sat = (alarm_vreme.sat + 1) % 24;
    }
    while(TASTER_ALARM_MIN == 0);
    delay50ms();
	}

	if(TASTER_ALARM_SEK == 0) {
   		 alarm_vreme.sek++;
    if(alarm_vreme.sek >= 60) {
        alarm_vreme.sek = 0;
        alarm_vreme.min++;
        if(alarm_vreme.min >= 60) {
            alarm_vreme.min = 0;
            alarm_vreme.sat = (alarm_vreme.sat + 1) % 24;
        }
    }
    while(TASTER_ALARM_SEK == 0);
    delay50ms();
	}

/* ----- START I STOP ----- */
	if(TASTER_STOP == 0) {
    	sat_radi = 0;  
    	while(TASTER_STOP == 0);
    		delay50ms();
	}

	if(TASTER_START == 0) {
    	sat_radi = 1;  
    	while(TASTER_START == 0);
    		delay50ms();
	}
 
    }
}