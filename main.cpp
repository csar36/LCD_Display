
#include "stdafx.h"
#include "LCD_Display.h"
#include "Timer.h"

INITIALIZE_EASYLOGGINGPP

int main()
{
    LCD_Display display;
    display.setPort(GPIO_21, GPIO_20, GPIO_16, GPIO_26, GPIO_19, GPIO_13, GPIO_6, GPIO_5, GPIO_17, GPIO_27, GPIO_12);
    display.resetDisplay();
    display.initializeLCD();
    display.putChar('N');
    display.putChar('o');
    display.putChar('t');
    display.putChar('h');
    display.putChar('i');
    display.putChar('n');
    display.putChar('g');

    display.setAddrDDRAM(0x40);
    //for(int i = 0; i < 33; i++)
   // {
    //    display.cursorOrDisplayShift(false, true);
   // }

    display.putChar('I');
    display.putChar('m');
    display.putChar('p');
    display.putChar('o');
    display.putChar('r');
    display.putChar('t');
    display.putChar('a');
    display.putChar('n');
    display.putChar('t');
    display.cursorOrDisplayShift(false, true);
    display.putChar('J');
    display.putChar('O');


}
