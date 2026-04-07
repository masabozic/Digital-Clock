#include "serijska.h"
#include "at89c51rc2.h"
#include "time.h"

#define BUFFER 32

uint8_t poruka_greska[] = "GRESKA\r\n";
uint8_t poruka_vreme[]  = "VREME PODESENO\r\n";
uint8_t poruka_alarm[]  = "ALARM PODESEN\r\n";


uint8_t bafer_za_prijem[BUFFER];
uint8_t indeks_za_upisivanje = 0;

uint8_t *tx_ptr = 0;

void parsiraj_poruku(void);
uint8_t procitaj_broj(char *buf, uint8_t *i);

void serial_init(void) {

	SCON = 0x50;
	PCON |= 0x80;
	BDRCON= 0x1C;
	BRL =253;

	TI =1;
	RI=0;
	REN=1;

	ES=1;
	EA=1;

}

void serial_ISR(void) interrupt 4 {
    char prijem;

    if (TI) {
        TI = 0;
        if (tx_ptr && *tx_ptr) {
            SBUF = *tx_ptr++;
        }
    }

    if (RI) {
        RI = 0;
        prijem = SBUF;

        if (prijem == '\r' || prijem == '\n')
            return;

        if (prijem == '(') {
            indeks_za_upisivanje = 0;
        }

        if (indeks_za_upisivanje < BUFFER - 1) {
            bafer_za_prijem[indeks_za_upisivanje++] = prijem;
        }

        if (prijem == ')') {
            bafer_za_prijem[indeks_za_upisivanje] = 0;
            parsiraj_poruku();
            indeks_za_upisivanje = 0;
        }
    }
}

void posalji_poruku(uint8_t *s) {
    if (!s) return;
    tx_ptr = s;
    SBUF = *tx_ptr++;      
}


uint8_t procitaj_broj(char *buf, uint8_t *i) {
    uint8_t broj = 0;

    if (buf[*i] < '0' || buf[*i] > '9')
        return 255;  

    while (buf[*i] >= '0' && buf[*i] <= '9') {
        broj = broj * 10 + (buf[*i] - '0');
        (*i)++;
    }
    return broj;
}

void parsiraj_poruku(void) {
    uint8_t i = 0;
    char tip;
    uint8_t h, m, s;

    if (bafer_za_prijem[0] != '(')
        goto greska;

    tip = bafer_za_prijem[1];
    if (tip != 'T' && tip != 'A')
        goto greska;

    if (bafer_za_prijem[2] != ',')
        goto greska;

    i = 3;
    h = procitaj_broj(bafer_za_prijem, &i);
    if (h == 255 || bafer_za_prijem[i++] != ',')
        goto greska;

    m = procitaj_broj(bafer_za_prijem, &i);
    if (m == 255 || bafer_za_prijem[i++] != ',')
        goto greska;

    s = procitaj_broj(bafer_za_prijem, &i);
    if (s == 255 || bafer_za_prijem[i] != ')')
        goto greska;

    if (h > 23 || m > 59 || s > 59)
        goto greska;

    if (tip == 'T') {
        trenutno_vreme.sat = h;
        trenutno_vreme.min = m;
        trenutno_vreme.sek = s;
        posalji_poruku(poruka_vreme);
    } else {
        alarm_vreme.sat = h;
        alarm_vreme.min = m;
        alarm_vreme.sek = s;
        posalji_poruku(poruka_alarm);
    }
    return;

greska:
    posalji_poruku(poruka_greska);
}