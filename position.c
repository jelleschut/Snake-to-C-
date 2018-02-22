#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "display.h"
#include "macros.h"
#include "fsm.h"

int randFoodY;                                     //random food Y coordinate
int randFoodX;                                     //random food X coordinate
int movement[2];                                   //array representing movement direction

STATES posState;                                   //posStates tracks requirement to reset snake

void positionHead();                               ///Used to adjust the position of SNAKE head
void positionStart();                              ///Used to (re)set SNAKE to starting position

void move(EVENTS event)                            ///Used to handle movement EVENTS received from FSM
{
   switch(event)
   {
      case EVT_START_POSITION:
         posState = ST_START_POSITION;             //posState now meets requirement to reset SNAKE in positionHead();
         break;
      case EVT_CHANGE_DIRECTION_UP:
         movement[0] = -1;                         //adjust SNAKE head Y-coordinate with -1
         movement[1] = 0;                          //do not adjust SNAKE head X-coordinate
         posState = ST_MOVE_UP;                    //change posState so reset requirement is not met
         break;
      case EVT_CHANGE_DIRECTION_DOWN:
         movement[0] = 1;                          //adjust SNAKE head Y-coordinate with +1
         movement[1] = 0;                          //do not adjust SNAKE head X-coordinate
         posState = ST_MOVE_DOWN;                  //change posState so reset requirement is not met
         break;
      case EVT_CHANGE_DIRECTION_LEFT:
         movement[0] = 0;                          //do not adjust SNAKE head Y-coordinate
         movement[1] = -1;                         //adjust SNAKE head X-coordinate with -1
         posState = ST_MOVE_LEFT;                  //change posState so reset requirement is not met
         break;
      case EVT_CHANGE_DIRECTION_RIGHT:
         movement[0] = 0;                          //do not adjust SNAKE head Y-coordinate
         movement[1] = 1;                          //adjust SNAKE head X-coordinate with +1
         posState = ST_MOVE_RIGHT;                 //change posState so reset requirement is not met
         break;
      case EVT_PAUSE_POSITION:
         movement[0] = 0;                          //do not adjust SNAKE head Y-coordinate
         movement[1] = 0;                          //do not adjust SNAKE head X-coordinate
         posState = ST_MOVE_STOP;                  //change posState so reset requirement is not met
         break;
      default:
         movement[0] = 0;                          //do not adjust SNAKE head Y-coordinate
         movement[1] = 0;                          //do not adjust SNAKE head X-coordinate
         posState = ST_MOVE_STOP;                  //change posState so reset requirement is not met
   }

   positionHead();
}

void positionHead()                                ///Used to adjust the position of SNAKE head
{
   if(posState == ST_START_POSITION)               //if SNAKE needs to return to start position
   {
      positionStart();                             //return SNAKE to start position, stop movement
   }

   snakeY[0] += movement[0];                       //update SNAKE head Y-coordinate
   snakeX[0] += movement[1];                       //update SNAKE head Y-coordinate
}

void positionStart()                               ///Used to return snake to start position
{
   snakeY[0] = STARTY;                             //set SNAKE head to start position
   snakeX[0] = STARTX;                             //set SNAKE head to start position
   movement[0] = 0;                                //stop movement
   movement[1] = 0;                                //stop movement
}

void randomFoodY()                                 ///Used to randomize Y-coordinate of food
{
   srand(time(NULL));
   randFoodY = rand() % (HEIGHT - (2 * BORDERTHICK)) + BORDERTHICK;
}

int positionFoodY()                                ///Used to retrieve food Y-coordinate in other functions
{
   return randFoodY;
}

void randomFoodX()                                 ///Used to randomize Y-coordinate of food
{
   srand(time(NULL));
   randFoodX = rand() % (WIDTH - (2 * BORDERTHICK)) + BORDERTHICK;
}

int positionFoodX()                                ///Used to retrieve food X-coordinate in other functions
{
   return randFoodX;
}

