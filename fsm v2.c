#include "fsm.h"
#include "keyboard.h"
#include "display.h"
#include "position.h"
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#define DELAY 250000

STATES previousState;
STATES nextState;
STATES currentState = ST_INITIALISE;
EVENTS event = EVT_NO;
int score = 0;
int none = 0;
int up = 1;
int right = 2;
int down = 3;
int left = 4;
int start = 5;
int direction;

void eventhandler(EVENTS event)
{
   nextState = ST_NO;

   switch(currentState)
   {
      case ST_NO:
         printf("error\n");
         break;

      case ST_INITIALISE:
         displayMenu();
         event = keyboardInput();
         switch(event)
         {
            case EVT_START_GAME:
               nextState = ST_GAME_START;
               break;
            case EVT_SHUT_DOWN:
               nextState = ST_SHUT_DOWN;
               break;
            default:
               nextState = ST_INITIALISE;
         }
         break;

      case ST_SHUT_DOWN:
         displayShutDown();
         event = keyboardInput();
         switch(event)
         {
            case EVT_KEY_X:
               nextState = ST_INITIALISE;
               break;
         }
         break;

      case ST_GAME_START:
         printf("begin start: direction = %d\n", direction);
         move(start);
         event = keyboardInput();
         switch(event)
         {
            case EVT_KEY_UP:
               nextState = ST_SNAKE_UP;
               direction = up;
               break;
            case EVT_KEY_RIGHT:
               nextState = ST_SNAKE_RIGHT;
               direction = right;
               break;
            case EVT_KEY_DOWN:
               nextState = ST_SNAKE_DOWN;
               direction = down;
               break;
            case EVT_KEY_LEFT:
               nextState = ST_SNAKE_RIGHT;
               direction = right;
               break;
            default:
               nextState = ST_GAME_START;
         }
         break;

      case ST_SNAKE_UP:
         move(up);
         usleep(DELAY);
         event = keyboardMovement();
         switch(event)
         {
            case EVT_KEY_RIGHT:
               nextState = ST_SNAKE_RIGHT;
               direction = right;
               break;
            case EVT_KEY_LEFT:
               nextState = ST_SNAKE_LEFT;
               direction = left;
               break;
            case EVT_KEY_M:
               nextState = ST_CONFIRM_M;
               break;
            case EVT_KEY_R:
               nextState = ST_CONFIRM_R;
               break;
            case EVT_KEY_P:
               nextState = ST_PAUSE;
               break;
            default:
               nextState = ST_SNAKE_UP;
               event = keyboardMovement();
         }
         break;

      case ST_SNAKE_RIGHT:
         move(right);
         usleep(DELAY);
         event = keyboardMovement();
         switch(event)
         {
            case EVT_KEY_UP:
               nextState = ST_SNAKE_UP;
               direction = up;
               break;
            case EVT_KEY_DOWN:
               nextState = ST_SNAKE_DOWN;
               direction = down;
               break;
            case EVT_KEY_M:
               nextState = ST_CONFIRM_M;
               break;
            case EVT_KEY_R:
               nextState = ST_CONFIRM_R;
               break;
            case EVT_KEY_P:
               nextState = ST_PAUSE;
               break;
            default:
               nextState = ST_SNAKE_RIGHT;
               event = keyboardMovement();
         }
         break;

      case ST_SNAKE_DOWN:
         move(down);
         usleep(DELAY);
         event = keyboardMovement();
         switch(event)
         {
            case EVT_KEY_RIGHT:
               nextState = ST_SNAKE_RIGHT;
               direction = right;
               break;
            case EVT_KEY_LEFT:
               nextState = ST_SNAKE_LEFT;
               direction = left;
               break;
            case EVT_KEY_M:
               nextState = ST_CONFIRM_M;
               break;
            case EVT_KEY_R:
               nextState = ST_CONFIRM_R;
               break;
            case EVT_KEY_P:
               nextState = ST_PAUSE;
               break;
            default:
               nextState = ST_SNAKE_DOWN;
               event = keyboardMovement();
         }
         break;

      case ST_SNAKE_LEFT:
         move(left);
         usleep(DELAY);
         event = keyboardMovement();
         switch(event)
         {
            case EVT_KEY_UP:
               nextState = ST_SNAKE_UP;
               direction = up;
               break;
            case EVT_KEY_DOWN:
               nextState = ST_SNAKE_DOWN;
               direction = down;
               break;
            case EVT_KEY_M:
               nextState = ST_CONFIRM_M;
               break;
            case EVT_KEY_R:
               nextState = ST_CONFIRM_R;
               break;
            case EVT_KEY_P:
               nextState = ST_PAUSE;
               break;
            default:
               nextState = ST_SNAKE_LEFT;
               event = keyboardMovement();
         }
         break;

      case ST_CONFIRM_M:
         displayConfirmMenu();
         event = keyboardInput();
         switch(event)
         {
            case EVT_KEY_N:
               nextState = ST_GAME_RUN;
               break;
            case EVT_KEY_Y:
               nextState = ST_INITIALISE;
               break;
            default:
               nextState = ST_CONFIRM_M;
         }
         break;

      case ST_CONFIRM_R:

         displayConfirmReset();
         event = keyboardInput();
         switch(event)
         {
            case EVT_KEY_N:
               nextState = ST_GAME_RUN;
               break;
            case EVT_KEY_Y:
               nextState = ST_GAME_START;
               break;
            default:
               nextState = ST_CONFIRM_R;
         }
         break;



         /*case ST_PAUSE:
            displaySnake(none);
            switch(event)
            {
               case EVT_KEY_UP:
                  if(direction != down)
                  {
                     nextState = ST_GAME_RUN;
                     direction = up;
                  }
                  else
                  {
                     nextState = ST_PAUSE;
                  }
                  break;
               case EVT_KEY_RIGHT:
                  if(direction != left)
                  {
                     nextState = ST_GAME_RUN;
                     direction = right;
                  }
                  else
                  {
                     nextState = ST_PAUSE;
                  }
                  break;
               case EVT_KEY_DOWN:
                  if(direction != up)
                  {
                     nextState = ST_GAME_RUN;
                     direction = down;
                  }
                  else
                  {
                     nextState = ST_PAUSE;
                  }
                  break;
               case EVT_KEY_LEFT :
                  if(direction != right)
                  {
                     nextState = ST_GAME_RUN;
                     direction = left;
                  }
                  else
                  {
                     nextState = ST_PAUSE;
                  }
                  
                  
            }*/
   }
   currentState = nextState;
}


