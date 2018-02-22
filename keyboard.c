#include <conio.h>
#include <stdio.h>
#include <ctype.h>

#include "fsm.h"

EVENTS keyboardInput(void)             ///Used to control input to non-movement STATES in FSM
{
   EVENTS event;
   char input, inputLowerCase;
   fflush(stdin);                      //flushes buffer
   input = getch();                    //gets character

   inputLowerCase = tolower(input);    //Caps Lock security

   switch(inputLowerCase)              //switch handles which event is associated with character and sends to FSM
   {
      case 'w':
         event = EVT_KEY_UP;
         break;
      case 's':
         event = EVT_KEY_DOWN;
         break;
      case 'a':
         event = EVT_KEY_LEFT;
         break;
      case 'd':
         event = EVT_KEY_RIGHT;
         break;
      case '1':
         event = EVT_KEY_1;
         break;
      case '2':
         event = EVT_KEY_2;
         break;
      case '7':
         event = EVT_KEY_7;
         break;
      case '8':
         event = EVT_KEY_8;
         break;
      case '9':
         event = EVT_KEY_9;
         break;
      case 'm':
         event = EVT_KEY_M;
         break;
      case 'n':
         event = EVT_KEY_N;
         break;
      case 'p':
         event = EVT_KEY_P;
         break;
      case 'r':
         event = EVT_KEY_R;
         break;
      case 'x':
         event = EVT_KEY_X;
         break;
      case 'y':
         event = EVT_KEY_Y;
         break;
      case ')':
         event = EVT_MODE_0;
         break;
      case '!':
         event = EVT_MODE_1;
         break;
      default:
         event = EVT_NO;
   }
   return event;
}


EVENTS keyboardMovement(void)          ///Used to control input to movement STATES in FSM
{
   EVENTS event;
   char input, inputLowerCase;

   fflush(stdin);                      //flush buffer
   if(kbhit())                         //if the keyboard is hit
   {
      input = getch();                 //get character
   }

      inputLowerCase = tolower(input); //Caps Lock security

   switch(inputLowerCase)              //switch handles which event is associated with character and sends to FSM
   {
      case 'w':
         event = EVT_KEY_UP;
         break;
      case 'd':
         event = EVT_KEY_RIGHT;
         break;
      case 's':
         event = EVT_KEY_DOWN;
         break;
      case 'a':
         event = EVT_KEY_LEFT;
         break;
      case 'm':
         event = EVT_KEY_M;
         break;
      case 'n':
         event = EVT_KEY_N;
         break;
      case 'p':
         event = EVT_KEY_P;
         break;
      case 'r':
         event = EVT_KEY_R;
         break;
      case 'x':
         event = EVT_KEY_X;
         break;
      case 'y':
         event = EVT_KEY_Y;
         break;
      case '1':
         event = EVT_KEY_1;
         break;
      case '2':
         event = EVT_KEY_2;
         break;
      default:
         event = EVT_NO;
   }

   return event;
}
