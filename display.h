#ifndef DISPLAY_H
#define DISPLAY_H

#include "fsm.h"

void displayScreen(EVENTS currentEvent);
void multiplierFunc(int multi);


extern int snakeY[255];
extern int snakeX[255];

#endif // DISPLAY_H
