#include "gpio.h"


//TODO; Konstruktor, Destruktor bauen
//Funktionen entsprechend Klassenfunktionalitäten anpassen
GPIOPin::GPIOPin()
{}
GPIOPin::~GPIOPin()
{}

//*************PFADE************//
void GPIOPin::setExportPath()
{
    exportPath = "/sys/class/gpio/export";
}

std::string GPIOPin::getExportPath()
{
    return exportPath;
}

void GPIOPin::setDirectionPath()
{
    directionPath = "/sys/class/gpio/gpio" + std::to_string(GpioNumber) + "/direction";
}

std::string GPIOPin::getDirectionPath()
{
    return directionPath;
}

void GPIOPin::setValuePath()
{
    valuePath = "/sys/class/gpio/gpio" + std::to_string(GpioNumber) + "/value";

}

std::string GPIOPin::getValuePath()
{

    return valuePath;
}

int GPIOPin::exportGpio(GPIONum _pin)
{

    GpioNumber = _pin;
    setExportPath();
    std::string checkExpo = GPIO_PATH;
    checkExpo += "/gpio" + std::to_string(GpioNumber);
    if(opendir(checkExpo.c_str()) == NULL)
    {
        std::string exportCmd = "sudo echo " + std::to_string(GpioNumber) + " > " + exportPath;
        LOG(INFO) << "GPIOPin::initGpio - GPIO Export durchgeführt";
        system(exportCmd.c_str());
    }
    std::string orgPath = GPIO_PATH + std::to_string(GpioNumber);

    if(opendir(orgPath.c_str()) != NULL)
    {
        LOG(WARNING) << "GPIOPin::initGpio - GPIO Export: Pfad nicht gefunden!";
        return 1;
    }
    else
    {
        isExported = true;
        setDirectionPath();
        setValuePath();
    }
    return 0;
}

void GPIOPin::setValue(bool _value)
{
    if (isExported && direction)
    {
        std::string enableCmd;

        value = _value;

        if(value)
        {
            enableCmd = "echo 1 > " + valuePath;
            system(enableCmd.c_str());
        }
        else
        {
            enableCmd = "echo 0 > " + valuePath;
            system(enableCmd.c_str());
        }
        return;
    }
    else if(isExported && !direction)
    {
        LOG(WARNING) << "GPIOPin::setValue - GPIO" << GpioNumber <<" is set as input";
        return;
    }
    else if(!isExported)
    {
        LOG(WARNING) << "GPIOPin::setValue - GPIO" << GpioNumber <<" is not exported!";
        return;
    }
    else
    {
        LOG(ERROR) << "GPIOPin::setValue - __unknown";
        return;
    }
}

void GPIOPin::setDirection(GPIODirection _direction)
{

    direction = _direction;
    if (isExported)
    {
        if(direction == getDirection())
        {
            //LOG(INFO) << "GPIOPin::setDirection - GPIO" << GpioNumber <<" already [0:Input, 1:Output] --> "<< direction;
            return;
        }
        std::string directionCmd;
        if(direction)
        {
            directionCmd = "echo out > " + directionPath;
            system(directionCmd.c_str());
        }
        else
        {
            directionCmd = "echo in > " + directionPath;
            system(directionCmd.c_str());
        }
        return;
    }
    else
    {
        LOG(WARNING) << "GPIOPin::setDirection - GPIO" << GpioNumber <<" not exported";
        return;
    }
}

bool GPIOPin::getDirection()
{
    std::fstream fs(directionPath);
    std::string value;
    fs >> value;
    fs.close();

    return (value == "in") ? INPUT : OUTPUT;
}

bool GPIOPin::getValue()
{
    if (isExported)
    {
        if(direction)
        {
            LOG(WARNING) << "GPIOPin::getValue - GPIO" << GpioNumber << " set as output";
            return value;
        }
        else
        {
            return value;
        }
    }
    else
    {
        LOG(WARNING) << "GPIOPin::getValue - GPIO" << GpioNumber <<" not exported";
        return direction;
    }
}


/*
int GPIOPin::initGpio(int gpioNum, GPIODirection direction)
{
    std::string exportCmd;
    std::string directionCmd;
    std::string exportPath =  "/sys/class/gpio/export";
    std::string path =  "/sys/class/gpio/gpio" + std::to_string(gpioNum);

    if(opendir(path.c_str()) == NULL)
    {
        exportCmd = "echo " + std::to_string(gpioNum) + " > " + exportPath;
        system(exportCmd.c_str());
    }


    if(direction)
    {
        directionCmd = "echo out > " + path + "/direction";
        system(directionCmd.c_str());
    }
    else
    {
        directionCmd = "echo in > " + path + "/direction";
        system(directionCmd.c_str());
    }

    return 0;           //could be used for error handling
}


int GPIOPin::setGpio(int gpioNum, GPIOEnable value)
{
    std::string valueCmd;
    std::string path =  "/sys/class/gpio/gpio" + std::to_string(gpioNum);

    if(opendir(path.c_str()) == NULL)
    {
        printf("GPIOPin existiert nicht oder wurde nicht exportiert!! \n");
        return 1;
    }

    if(value)
    {
        valueCmd = "echo 1 > /sys/class/gpio/gpio" + std::to_string(gpioNum) + "/value";
        system(valueCmd.c_str());
    }
    else
    {
        valueCmd = "echo 0 > /sys/class/gpio/gpio" + std::to_string(gpioNum) + "/value";
        system(valueCmd.c_str());
    }
    return 0;
}
*/
