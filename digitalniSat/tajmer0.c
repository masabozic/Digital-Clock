#include "tajmer0.h"
#include "at89c51rc2.h"
#include "time.h"
#include "stdint.h"

static uint8_t cnt = 0;

void tajmer0_init(void)
{
    TMOD &= 0xF0;
    TMOD |= 0x01;

    TH0 = 0x4C;   // ~50ms
    TL0 = 0x00;

    TR0 = 1;
    ET0 = 1;
}

void pokreni_tajmer0(void) { TR0 = 1; }
void dozvoli_prekid_tajmer0(void) { ET0 = 1; }

void prekid_tajmer0(void) interrupt 1
{
    TH0 = 0x4C;
    TL0 = 0x00;

    cnt++;
    if(cnt >= 20)   // 20 * 50ms = 1 sekunda
    {
        cnt = 0;
        time_tick();
    }
}
