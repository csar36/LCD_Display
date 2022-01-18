#ifndef TIMER_H
#define TIMER_H
#include "stdafx.h"

/****** Timer.h/TimerOption
 *  NAME
 *      PWMPin -- Enum to generate StringPaths
 *      P9_22 -- PWM-1:0
 *      P9_21 -- PWM-1:1
 *      P9_14 -- PWM-4:0
 *      P9_16 = 3 -- PWM-4:1
 *      P8_19 = 4 -- PWM-7:0
 *      P8_13 = 5 -- PWM-7:1
******
*/
enum TimerUnit
{
   sec = 0,
   msec,
   usec,
   nsec,
};

 /****c* Timer.h/Timer
  *  NAME
  *    Timer
  *  DESCRIPTION
  *       Funktioniert im Prinzip wie eine Stoppuhr
  *  METHODS
  *       startTimer()
  *       stopTimer()
  *       getTime()
  *  ATTRIBUTES
  *       unit    -- Speicherung der zeitlichen Einheit
  *       start_t -- Rückgabewert von Clock() beim Starten des Timers
  *       end_t   -- Rückgabewert von Clock() beim Aufruf von StopTime
  *       diff_t  -- Differnz zwischen end und start
  *       time    -- Speicherung der Zeit
  *  NOTES
  *    Die Genauigkeit des Timers liegt in etwa bei 200 usec
  *
  ******
  *
*/
class Timer
{
      public:
         Timer();
      private:
         //TimerOption unit;
         clock_t start_t;
         clock_t end_t;
         clock_t diff_t;
         double time;
      public:
         void startTimer(void);
         double stopTimer();
         double getTime(TimerUnit);
         void sleepFor(double _time, TimerUnit _unit);
};


#endif