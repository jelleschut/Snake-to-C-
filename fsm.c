#include <stdio.h>
#include <unistd.h>

#include "mode.h"
#include "score.h"
#include "macros.h"
#include "keyboard.h"
#include "display.h"
#include "position.h"
#include "collision.h"
#include "highscore.h"

STATES currentState = ST_INITIALIZE;            //Use ST_INITIALIZE to initialize snake.
STATES nextState;                               //nextState is used to determine next step.
STATES returnState;                             //When a menu is selected, currentState is stored in returnState.
//So user continues where he left off.
EVENTS event = EVT_NO;                          //EVT_NO is used as initializer, all states go to default and
//reload themselves if no other event occurs.
EVENTS eventGenerator();                        //eventGenerator is used to get input and test for Game Over condition.

void finiteStateMachineSnake()                  //The Function that controls the whole programme, the FSM.
{
   nextState = ST_NO;                           //ST_NO is used as initializer to show if an error has occured (FSM-->default).

   switch(currentState)
   {                                            ///I WILL THOUROUGHLY EXPLAIN THE FIRST CASE TO SHOW THE INTENTION OF THE SWITCH
      case ST_INITIALIZE:                       ///Initial state of SNAKE and main menu
         displayScreen(EVT_INITIALIZED);        //Send EVENT to display system.
         event = keyboardInput();               //Wait for input EVENT from keyboard.
         switch(event)
         {
            case EVT_KEY_1:                     //'1' is pressed.
               nextState = ST_GAME_START;       //Next loop, Start Game.
               break;
            case EVT_KEY_2:                     //'2' is pressed.
               nextState = ST_SHUT_DOWN;        //Next loop, Shut Down.
               break;
            case EVT_MODE_0:                    //')' is pressed.
               modeZero();                      //set mode to 0 (developement/simulation mode).
               nextState = ST_INITIALIZE;       //Next loop, reload main menu in mode 0.
               break;
            case EVT_MODE_1:                    //'!' is pressed.
               modeOne();                       //set mode to 1 (user mode).
               nextState = ST_INITIALIZE;       //Next loop, reload main menu in mode 1.
               break;
            case EVT_KEY_7:                     //'7' is pressed.
               nextState = ST_TEST_COLOUR1;     //Next loop, Test colour 1 LEDs.
               break;
            case EVT_KEY_8:                     //'8' is pressed.
               nextState = ST_TEST_COLOUR2;     //Next loop, Test colour 2 LEDs.
               break;
            case EVT_KEY_9:                     //'9' is pressed.
               nextState = ST_TEST_COLOUR3;     //Next loop, Test colour 3 LEDs.
               break;
            default:                            //in all other cases.
               nextState = ST_INITIALIZE;       //Next loop, reload Initialize.
         }
         break;
         //----------------------------------------------------//
         //NEXT STATES/CASES WILL BE EXPLAINED IN LESS DETAIL  //
         //ONLY WHEN A NEW STATE/TERM/FUNCTION IS INTRODUCED,  //
         //A STATE/CASE DEVIATES GREATLY OR WHEN SPECIAL       //
         //ATTENTION IS REQUIRED DETAILED EXPLANATION FOLLOWS. //
         //----------------------------------------------------//

      case ST_TEST_COLOUR1:                     ///Used to test colour 1 LEDs
         displayScreen(EVT_TEST_COLOUR1);
         event = keyboardInput();
         switch(event)
         {
            case EVT_KEY_7:                     //Key 7 could have been left out because it is covered by default
               nextState = ST_INITIALIZE;       //But to improve readability and to ensure a second key '7' press
               break;                           //returns to main menu even when default changes.
            case EVT_KEY_8:
               nextState = ST_TEST_COLOUR2;
               break;
            case EVT_KEY_9:
               nextState = ST_TEST_COLOUR3;
               break;
            default:
               nextState = ST_INITIALIZE;
         }
         break;

      case ST_TEST_COLOUR2:                     ///Used to test colour 2 LEDs
         displayScreen(EVT_TEST_COLOUR2);
         event = keyboardInput();
         switch(event)
         {
            case EVT_KEY_7:
               nextState = ST_TEST_COLOUR1;
               break;
            case EVT_KEY_8:
               nextState = ST_INITIALIZE;
               break;
            case EVT_KEY_9:
               nextState = ST_TEST_COLOUR3;
               break;
            default:
               nextState = ST_INITIALIZE;
         }
         break;

      case ST_TEST_COLOUR3:                     ///Used to test colour 2 LEDs
         displayScreen(EVT_TEST_COLOUR3);
         event = keyboardInput();
         switch(event)
         {
            case EVT_KEY_7:
               nextState = ST_TEST_COLOUR1;
               break;
            case EVT_KEY_8:
               nextState = ST_TEST_COLOUR2;
               break;
            case EVT_KEY_9:
               nextState = ST_INITIALIZE;
               break;
            default:
               nextState = ST_INITIALIZE;
         }
         break;

      case ST_SHUT_DOWN:                        ///Used to Shut Down all LEDs
         displayScreen(EVT_SHUT_DOWN);
         event = keyboardInput();
         switch(event)
         {
            case EVT_KEY_X:                     //'x' is pressed.
               nextState = ST_INITIALIZE;       //Next loop, Initialize.
               break;
            default:
               nextState = ST_SHUT_DOWN;
         }
         break;

      case ST_GAME_START:                       ///Starts game
         scoreZero();                             //score is set or reset to 0.
         move(EVT_START_POSITION);              //Movement function for starting game event is called to (re)set snake in starting position.
         displayScreen(EVT_GAME_STARTED);
         event = keyboardInput();
         switch(event)
         {
            case EVT_KEY_UP:                    //'w' is pressed.
               nextState = ST_SNAKE_UP;         //Next loop, move SNAKE up.
               break;
            case EVT_KEY_DOWN:                  //'s' is pressed.
               nextState = ST_SNAKE_DOWN;       //Next loop, move SNAKE down.
               break;
            case EVT_KEY_LEFT:                  //'a' is pressed.
               nextState = ST_SNAKE_RIGHT;      //Next loop, move SNAKE left.
               break;
            case EVT_KEY_RIGHT:                 //'d' is pressed.
               nextState = ST_SNAKE_RIGHT;      //Next loop, move SNAKE right.
               break;
            case EVT_KEY_M:                     //'m' is pressed.
               nextState = ST_CONFIRM_M;        //Next loop, ask for confirmation to return to main menu.
               break;
            case EVT_KEY_R:                     //'r' is pressed.
               nextState = ST_CONFIRM_R;        //Next loop, ask for confirmation to reset SNAKE and score.
               break;
            default:
               nextState = ST_SNAKE_RIGHT;
         }
         break;

      case ST_SNAKE_UP:                         ///Used to move SNAKE up
         returnState = currentState;            //When returning from Pause, this returnstate ensures proper contiuation
         move(EVT_CHANGE_DIRECTION_UP);         //movement function to change to/keep direction up
         displayScreen(EVT_SNAKE_UP);
         usleep(DELAY);                         //Delay by DELAY microseconds, so user has time to react.
         event = eventGenerator();              //Checks for input EVENTS and checks for Collision.
         switch(event)                          //Only perpendicular movements are defined in movement switches
         {                                      //because trying to move in opposite or same direction have no effect.
            case EVT_KEY_LEFT:
               nextState = ST_SNAKE_LEFT;
               break;
            case EVT_KEY_RIGHT:
               nextState = ST_SNAKE_RIGHT;
               break;
            case EVT_KEY_M:
               nextState = ST_CONFIRM_M;
               break;
            case EVT_KEY_P:                     //'p' is pressed.
               nextState = ST_PAUSE;            //Next loop, Pause Game.
               break;
            case EVT_KEY_R:
               nextState = ST_CONFIRM_R;
               break;
            case EVT_COLLISION:                 //SNAKE collided with itself or playingfield border.
               nextState = ST_GAME_OVER;        //Next loop, Game Over.
               break;
            default:
               nextState = ST_SNAKE_UP;
         }
         break;

      case ST_SNAKE_DOWN:                       ///Used to move SNAKE down
         returnState = currentState;
         move(EVT_CHANGE_DIRECTION_DOWN);
         displayScreen(EVT_SNAKE_DOWN);
         usleep(DELAY);
         event = eventGenerator();
         switch(event)
         {
            case EVT_KEY_LEFT:
               nextState = ST_SNAKE_LEFT;
               break;
            case EVT_KEY_RIGHT:
               nextState = ST_SNAKE_RIGHT;
               break;
            case EVT_KEY_M:
               nextState = ST_CONFIRM_M;
               break;
            case EVT_KEY_P:
               nextState = ST_PAUSE;
               break;
            case EVT_KEY_R:
               nextState = ST_CONFIRM_R;
               break;
            case EVT_COLLISION:
               nextState = ST_GAME_OVER;
               break;
            default:
               nextState = ST_SNAKE_DOWN;
         }
         break;

      case ST_SNAKE_LEFT:                       ///Used to move SNAKE left
         returnState = currentState;
         move(EVT_CHANGE_DIRECTION_LEFT);
         displayScreen(EVT_SNAKE_LEFT);
         usleep(DELAY);
         event = eventGenerator();
         switch(event)
         {
            case EVT_KEY_UP:
               nextState = ST_SNAKE_UP;
               break;
            case EVT_KEY_DOWN:
               nextState = ST_SNAKE_DOWN;
               break;
            case EVT_KEY_M:
               nextState = ST_CONFIRM_M;
               break;
            case EVT_KEY_P:
               nextState = ST_PAUSE;
               break;
            case EVT_KEY_R:
               nextState = ST_CONFIRM_R;
               break;
            case EVT_COLLISION:
               nextState = ST_GAME_OVER;
               break;
            default:
               nextState = ST_SNAKE_LEFT;
         }
         break;

      case ST_SNAKE_RIGHT:                      ///Used to move SNAKE right
         returnState = currentState;
         move(EVT_CHANGE_DIRECTION_RIGHT);
         displayScreen(EVT_SNAKE_RIGHT);
         usleep(DELAY);
         event = eventGenerator();
         switch(event)
         {
            case EVT_KEY_UP:
               nextState = ST_SNAKE_UP;
               break;
            case EVT_KEY_DOWN:
               nextState = ST_SNAKE_DOWN;
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
            case EVT_COLLISION:
               nextState = ST_GAME_OVER;
               break;
            default:
               nextState = ST_SNAKE_RIGHT;
         }
         break;

      case ST_CONFIRM_M:                        ///Used to ask for confirmation to return to main menu
         displayScreen(EVT_CONFIRM_MENU);
         event = keyboardInput();
         switch(event)
         {
            case EVT_KEY_N:                     //'n' is pressed.
               nextState = ST_PAUSE;
               break;
            case EVT_KEY_Y:                     //'y' is pressed.
               nextState = ST_INITIALIZE;
               break;
            default:
               nextState = ST_CONFIRM_M;
         }
         break;

      case ST_CONFIRM_R:                        ///Used to ask for confirmation to reset score and snake
         displayScreen(EVT_CONFIRM_RESET);
         event = keyboardInput();
         switch(event)
         {
            case EVT_KEY_N:
               nextState = ST_PAUSE;
               break;
            case EVT_KEY_Y:
               nextState = ST_GAME_START;
               break;
            default:
               nextState = ST_CONFIRM_R;
         }
         break;

      case ST_PAUSE:                            ///Used to pause game, and as return state from confirmation menu's
         move(EVT_PAUSE_POSITION);
         displayScreen(EVT_PAUSED);
         event = keyboardInput();
         switch(event)
         {
            case EVT_KEY_M:
               nextState = ST_CONFIRM_M;
               break;
            case EVT_KEY_R:
               nextState = ST_CONFIRM_R;
               break;
            case EVT_KEY_P:
               nextState = returnState;         //Return to the state FSM was in before menu or pause was pressed.
               break;
            default:
               nextState = ST_PAUSE;
         }
         break;

      case ST_GAME_OVER:                        ///Used to show Game Over screen and Score
         displayScreen(EVT_GAME_OVER);
         updateHighScore();
         event = keyboardInput();
         switch(event)
         {
            case EVT_KEY_Y:
               nextState = ST_INITIALIZE;
               break;
            default:
               nextState = ST_GAME_OVER;
         }
         break;

      default:                                  ///Used to make sure Errors are handled properly
         displayScreen(EVT_ERROR);
         event = keyboardInput();
         switch(event)
         {
            case EVT_KEY_Y:
               nextState = ST_INITIALIZE;
               break;
            default:
               nextState = ST_ERROR;            //ST_ERROR is not handled, returning FSM to default
         }

   }
   currentState = nextState;                    ///Ensures next loop enters next STATE
}



EVENTS eventGenerator()                         ///Used to generate input and check for collision
{
   EVENTS next = keyboardMovement();
   if(collisionChecker() == EVT_COLLISION)
   {
      next = EVT_COLLISION;
   }
   return next;
}
