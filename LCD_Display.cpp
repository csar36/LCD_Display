#include "LCD_Display.h"


LCD_Display::LCD_Display(){}

LCD_Display::~LCD_Display(){}

void LCD_Display::setPort(GPIONum _db0, GPIONum _db1, GPIONum _db2, GPIONum _db3, GPIONum _db4, GPIONum _db5, GPIONum _db6, GPIONum _db7, GPIONum _RW, GPIONum _RS, GPIONum _enable)
{

    db0.exportGpio(_db0);
    db1.exportGpio(_db1);
    db2.exportGpio(_db2);
    db3.exportGpio(_db3);
    db4.exportGpio(_db4);
    db5.exportGpio(_db5);
    db6.exportGpio(_db6);
    db7.exportGpio(_db7);
    RW.exportGpio(_RW);
    RS.exportGpio(_RS);
    enable.exportGpio(_enable);

    RW.setDirection(OUTPUT);
    RW.setValue(LOW);
    RS.setDirection(OUTPUT);
    RS.setValue(LOW);
    enable.setDirection(OUTPUT);
    enable.setValue(LOW);
}


void LCD_Display::write8BitData(uint8_t _data)
{
    data = _data;
    db0.setValue(data & 0x01);
    db1.setValue(data & 0x02);
    db2.setValue(data & 0x04);
    db3.setValue(data & 0x08);
    db4.setValue(data & 0x10);
    db5.setValue(data & 0x20);
    db6.setValue(data & 0x40);
    db7.setValue(data & 0x80);

    return;
}


void LCD_Display::waitBusyFlag()
{
    bool busyFlag = true;
    bool output;
    
    db0.setDirection(INPUT);
    db1.setDirection(INPUT);
    db2.setDirection(INPUT);
    db3.setDirection(INPUT);
    db4.setDirection(INPUT);
    db5.setDirection(INPUT);
    db6.setDirection(INPUT);
    db7.setDirection(INPUT);

    RS.setValue(LOW);
    RW.setValue(HIGH);
    LOG(INFO) << "Waiting for BF.. ";
    while(busyFlag)
    {
        time.sleepFor(85, usec);
        enable.setValue(HIGH);
        enable.setValue(LOW);
        busyFlag = db7.getValue(); 
    };

    db7.setDirection(OUTPUT);
    db6.setDirection(OUTPUT);
    db5.setDirection(OUTPUT);
    db4.setDirection(OUTPUT);
    db3.setDirection(OUTPUT);
    db2.setDirection(OUTPUT);
    db1.setDirection(OUTPUT);
    db0.setDirection(OUTPUT);
    RW.setValue(LOW);
    return;
}


uint8_t LCD_Display::readPort()
{
    bool val;
    uint8_t prepData = 0x00;
    val = db0.getValue();
    if(db0.getValue()){(prepData += 1 << 0);}
    if(db1.getValue()){(prepData += 1 << 0);}
    if(db2.getValue()){(prepData += 1 << 0);}
    if(db3.getValue()){(prepData += 1 << 0);}
    if(db4.getValue()){(prepData += 1 << 0);}
    if(db5.getValue()){(prepData += 1 << 0);}
    if(db6.getValue()){(prepData += 1 << 0);}
    if(db7.getValue()){(prepData += 1 << 0);}

    return data;
}


int LCD_Display::clearDisplay()
{
    db7.setDirection(OUTPUT);
    db6.setDirection(OUTPUT);
    db5.setDirection(OUTPUT);
    db4.setDirection(OUTPUT);
    db3.setDirection(OUTPUT);
    db2.setDirection(OUTPUT);
    db1.setDirection(OUTPUT);
    db0.setDirection(OUTPUT);
    RW.setValue(LOW);
    RS.setValue(LOW);
    write8BitData(0x01);
    enable.setValue(HIGH);
    enable.setValue(LOW);
    time.sleepFor(80, usec);
    waitBusyFlag();
    return 0; //could be used for Error-Handling
}


int LCD_Display::returnHome()
{
    db7.setDirection(OUTPUT);
    db6.setDirection(OUTPUT);
    db5.setDirection(OUTPUT);
    db4.setDirection(OUTPUT);
    db3.setDirection(OUTPUT);
    db2.setDirection(OUTPUT);
    db1.setDirection(OUTPUT);
    db0.setDirection(OUTPUT);
    RW.setValue(LOW);
    RS.setValue(LOW);

    write8BitData(0x02);
    enable.setValue(HIGH);
    enable.setValue(LOW);
    time.sleepFor(80, usec);
    waitBusyFlag();
    return 0;
}


int LCD_Display::entryModeSet(bool _id, bool _shift)
{
    bool id;
    bool shift;
    id = _id;
    shift = _shift;
    db7.setDirection(OUTPUT);
    db6.setDirection(OUTPUT);
    db5.setDirection(OUTPUT);
    db4.setDirection(OUTPUT);
    db3.setDirection(OUTPUT);
    db2.setDirection(OUTPUT);
    db1.setDirection(OUTPUT);
    db0.setDirection(OUTPUT);
    RW.setValue(LOW);
    RS.setValue(LOW);

    uint8_t prepData = 0;
    if(shift)   {   prepData += 1 << 0;   }
    if(id)  {   prepData += 1 << 1;   }
    write8BitData(prepData);
    enable.setValue(HIGH);
    enable.setValue(LOW);
    time.sleepFor(80, usec);
    //waitBusyFlag();
    return 0;
}


int LCD_Display::displayOnOff(bool _display, bool _cursor, bool _cursorBlink)
{
    bool display = _display;
    bool cursor = _cursor;
    bool cursorBlink = _cursorBlink;
    RW.setValue(0);
    RS.setValue(0);
    db0.setDirection(OUTPUT);
    db1.setDirection(OUTPUT);
    db2.setDirection(OUTPUT);
    db3.setDirection(OUTPUT);
    db4.setDirection(OUTPUT);
    db5.setDirection(OUTPUT);
    db6.setDirection(OUTPUT);
    db7.setDirection(OUTPUT);

    uint8_t prepData = 0x08;
    if(cursorBlink) {   prepData += 1 << 0; }
    if(cursor) {    prepData += 1 << 1; }
    if(display) {   prepData += 1 << 2; }
    int show = (int) prepData;
    LOG(INFO) << "Prepdata :" << show;
    write8BitData(prepData);
    enable.setValue(HIGH);
    enable.setValue(LOW);
    time.sleepFor(80, usec);
    waitBusyFlag();
    return 0;
}

int LCD_Display::cursorOrDisplayShift(bool _displayCursor, bool _rightLeft)
{
    bool displayCursor = _displayCursor;
    bool rightLeft = _rightLeft;
    RW.setValue(0);
    RS.setValue(0);
    db0.setDirection(OUTPUT);
    db1.setDirection(OUTPUT);
    db2.setDirection(OUTPUT);
    db3.setDirection(OUTPUT);
    db4.setDirection(OUTPUT);
    db5.setDirection(OUTPUT);
    db6.setDirection(OUTPUT);
    db7.setDirection(OUTPUT);

    uint8_t prepData = 0x10;
    if(rightLeft){(prepData += 1 << 2);} 
    if(displayCursor){(prepData += 1 << 3);}
    write8BitData(prepData);
    enable.setValue(HIGH);
    enable.setValue(LOW);
    time.sleepFor(80, usec);
    waitBusyFlag();
    return 0;
}

int LCD_Display::functionSet(bool _dl, bool _n, bool _f)
{
    bool dl = _dl;
    bool n = _n;
    bool f = _f;

    RW.setValue(0);
    RS.setValue(0);
    db0.setDirection(OUTPUT);
    db1.setDirection(OUTPUT);
    db2.setDirection(OUTPUT);
    db3.setDirection(OUTPUT);
    db4.setDirection(OUTPUT);
    db5.setDirection(OUTPUT);
    db6.setDirection(OUTPUT);
    db7.setDirection(OUTPUT);

    uint8_t prepData = 0x20;
    if(dl){prepData += 1 << 4;}
    if(n){(prepData += 1 << 3);}
    if(f){ (prepData += 1 << 2);}
    int show = (int) prepData;
    LOG(INFO) << "PrepData: " <<show;
    write8BitData(prepData);
    enable.setValue(HIGH);
    enable.setValue(LOW);
    time.sleepFor(80, usec);
    //waitBusyFlag();
    return 0;
}

int LCD_Display::putChar(uint8_t _zeichen)
{   

    RS.setValue(true);
    RW.setValue(false);
    uint8_t zeichen = _zeichen;
    db0.setValue(zeichen & 0x01);
    db1.setValue(zeichen & 0x02);
    db2.setValue(zeichen & 0x04);
    db3.setValue(zeichen & 0x08);
    db4.setValue(zeichen & 0x10);
    db5.setValue(zeichen & 0x20);
    db6.setValue(zeichen & 0x40);
    db7.setValue(zeichen & 0x80);
    enable.setValue(HIGH);
    enable.setValue(LOW);
    time.sleepFor(80, usec);
    waitBusyFlag();
    return 0;
    

}

int LCD_Display::initializeLCD()
{   
    LOG(INFO) << "_____________INIT DISPLAY_______________";
    time.sleepFor(50, msec);
    LOG(INFO) << "Function Set";
    functionSet(true, true, false);
    time.sleepFor(40, usec);
    LOG(INFO) << "Function Set";
    functionSet(true, true, false);
    time.sleepFor(40, usec);
    LOG(INFO) << "Display ON/OFF";
    displayOnOff(true, false, false);
    time.sleepFor(40, usec);
    LOG(INFO) << "Clear Display";
    clearDisplay();
    time.sleepFor(1600, usec);
    LOG(INFO) << "Entry Mode Set";
    entryModeSet(true, false);
    return 0;
}


int LCD_Display::resetDisplay()
{
    LOG(INFO) << "_____________RESET DISPLAY_______________";
    LOG(INFO) << "Clear Display";
    clearDisplay();
    time.sleepFor(1600, usec);
    LOG(INFO) << "Function Set";
    functionSet(true, false, false);
    time.sleepFor(37, usec);
    LOG(INFO) << "Display OFF";
    displayOnOff(false, false, false);
    time.sleepFor(37, usec);
    LOG(INFO) << "Entry Mode Set";
    entryModeSet(true, false);
    time.sleepFor(80, usec);
    LOG(INFO) << "wait busy Flag";
    waitBusyFlag();
    return 0;

}
