#include "fsm.h"

STATES mode = ST_MODE_1;

void modeZero ()
{
   mode = ST_MODE_0;
}

void modeOne()
{
   mode = ST_MODE_1;
}

STATES getMode()
{
   return mode;
}
