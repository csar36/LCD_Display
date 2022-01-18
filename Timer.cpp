#include "Timer.h"



Timer::Timer()
{
    start_t = clock();
}


/****f* Timer.h/startTimer()
  *  NAME
  *    startTimer() -- Starten des Timers
  *  INPUTS
  *     NONE
  *  RETURN VALUE
  *     NONE
  ******
  *
*/
void Timer::startTimer()
{
    start_t = clock();
}



/****f* Timer.h/getTime()
  *  NAME
  *    getTime() -- Zeit wird
  *  INPUTS
  *     _edge - Value which overrides the attribute edge
  *  RETURN VALUE
  *     just 0
  *  NOTES
  *    getTime() stoppt nicht den Timer sondern berechnet nur die zeitliche Differenz von Start bis zum Aufruf der Methode.
  *    Würde man aus irgend einen Grund diese Zeit nochmals benötigen, wird diese nach aufruf von getTimer in time gespeichert
  *    -> Diese ist dann solange vorhanden, bis startTimer() aufgerufen wird
  ******
  *
*/
double Timer::getTime(TimerUnit _unit)
{
    TimerUnit unit = _unit;
    clock_t diff;
    double timeInUnit;

        end_t = clock();
        diff = end_t - start_t;
        time = (double) diff / CLOCKS_PER_SEC;

             switch(unit)
        {
            case sec: break;
            case msec:  timeInUnit = time * pow(10,3);
                        break;
            case usec: timeInUnit = time * pow(10,6);
                        break;
            case nsec: timeInUnit = time * pow(10,9);
                        break;
            default: std::cout << "TIMER_UNIT_ERROR" << std::endl; break;
        }
    return time;
}


void Timer::sleepFor(double _time, TimerUnit _unit)
{
    clock_t diff;
    TimerUnit unit = _unit;
    double time = _time;

    start_t = clock();
    do{

    }while(time < getTime(unit));
}