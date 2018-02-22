#include "macros.h"

int score = 0;
int length;

void scoreZero()
{
   score = 0;
   length = 0;
}

void increaseLength()
{
   length = length + LENGTHINC;
}

void increaseScore()
{
   score = score + SCOREINC;
}

int getScore()
{
   return score;
}

int getLength()
{
   return length;
}
