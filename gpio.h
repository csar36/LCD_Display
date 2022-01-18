#ifndef GPIO_H
#define GPIO_H
#include "stdafx.h"
#include "easylogging++.h"
#define GPIO_PATH "/sys/class/gpio"

enum GPIOEnable{
    LOW = 0,
    HIGH,
};

enum GPIODirection{
    INPUT = 0,
    OUTPUT,
};

enum GPIONum{
    GPIO_2 = 2,
    GPIO_3 = 3,
    GPIO_4 = 4,
    GPIO_5 = 5,
    GPIO_6 = 6,
    GPIO_7 = 7,
    GPIO_8 = 8,
    GPIO_9 = 9,
    GPIO_10 = 10,
    GPIO_11 = 11,
    GPIO_12 = 12,
    GPIO_13 = 13,
    GPIO_14 = 14,
    GPIO_15 = 15,
    GPIO_16 = 16,
    GPIO_17 = 17,
    GPIO_18 = 18,
    GPIO_19 = 19,
    GPIO_20 = 20,
    GPIO_21 = 21,
    GPIO_22 = 22,
    GPIO_23 = 23,
    GPIO_24 = 24,
    GPIO_25 = 25,
    GPIO_26 = 26,
    GPIO_27 = 27,
};

class GPIOPin
{

    private:
        std::string exportPath;
        std::string directionPath;
        std::string valuePath;

    public:
        GPIOPin();
        GPIOPin(GPIONum _GpioNumber);
        ~GPIOPin();

        int GpioNumber;
        bool direction = INPUT;
        bool value = HIGH;
        bool isExported = false;

        int exportGpio(GPIONum _pin);
        void setDirection(GPIODirection _direction);
        bool getDirection();
        void setValue(bool value);
        bool getValue();

//***Pfad-Operationen***
        void setExportPath();
        std::string getExportPath();
        void setDirectionPath();
        std::string getDirectionPath();
        void setValuePath();
        std::string getValuePath();

};

#endif