#include "BoardIO.h"
void delay2(unsigned int ms);

int main()
{
    // put your setup code here, to run once:
    WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer
    DCOCTL &= ~0xE0;
    DCOCTL |= CALDCO_16MHZ;
    BCSCTL1 &= ~0x0F;
    BCSCTL1 |= CALBC1_16MHZ;
    BoardIO io = BoardIO();
    for(;;)
    {
        io.updateDisplay();
        delay2(1);
    }
    return 0;
}

void delay2(unsigned int ms)
{
    while (ms--)
    {
        __delay_cycles(16000); // 16000 set for 16Mhz change it to 1000 for 1 Mhz
    }
}
