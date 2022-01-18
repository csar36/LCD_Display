#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H


#include "gpio.h"
#include "Timer.h"


#define MODE 1

enum IR_CMD
{

};

class LCD_Display
{
    public:
        LCD_Display();
        ~LCD_Display();

        GPIOPin db0;
        GPIOPin db1;
        GPIOPin db2;
        GPIOPin db3;
        GPIOPin db4;
        GPIOPin db5;
        GPIOPin db6;
        GPIOPin db7;
        GPIOPin RW;
        GPIOPin RS;
        GPIOPin enable;
        Timer time;
        std::vector<GPIOPin*> Port = {&db0, &db1, &db2, &db3, &db4, &db5, &db6, &db7};
        // TODO: implement vektor with pointer to gpio Objs

        bool OnOff = true;

        void setPort(GPIONum _db0, GPIONum _db1, GPIONum _db2, GPIONum _db3, GPIONum _db4, GPIONum _db5, GPIONum _db6, GPIONum _db7, GPIONum _RW, GPIONum _RS, GPIONum _enable);
        void write8BitData(uint8_t _data);
        void waitBusyFlag();
        uint8_t readPort();
        void initializeLCD();
        void resetDisplay();
        void clearDisplay();
        void returnHome();
        
        void entryModeSet(bool _id, bool _shift);
        void displayOnOff(bool _display, bool _cursor, bool _cursorBlink);
        void cursorOrDisplayShift(bool _displayCursor, bool _rightLeft);
        void functionSet(bool _lengthControl, bool _lineNumberControl, bool _fontTypeControl);
        void putChar(uint8_t _zeichen);
        void setAddrCGRAM(uint8_t _addr);
        void setAddrDDRAM(uint8_t _addr);
        uint8_t readBFandAddr();
        int writeDataToRam();
        int readDataFromRam();



        




};

#endif