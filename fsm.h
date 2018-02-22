#ifndef SNAKE_H
#define SNAKE_H

typedef enum
{
   /* FSM STATES           */
   ST_NO,
   ST_SHUT_DOWN,
   ST_INITIALIZE,
   ST_GAME_START,
   ST_GAME_OVER,
   ST_SNAKE_UP,
   ST_SNAKE_RIGHT,
   ST_SNAKE_DOWN,
   ST_SNAKE_LEFT,
   ST_CONFIRM_M,
   ST_CONFIRM_R,
   ST_CONFIRM_Q,
   ST_PAUSE,
   ST_MODE_0,
   ST_MODE_1,
   ST_ERROR,
   //----------------------//

   /*TEST STATES           */
   ST_TEST_COLOUR2,
   ST_TEST_COLOUR1,
   ST_TEST_COLOUR3,
   //----------------------//

   /* DISPLAY STATES       */
   ST_DISPLAY_TEST_GREEN,
   ST_DISPLAY_TEST_RED,
   ST_DISPLAY_TEST_YELLOW,
   ST_DISPLAY_STANDBY,
   ST_DISPLAY_SHUT_DOWN,
   ST_DISPLAY_MAIN_MENU,
   ST_DISPLAY_CONFIRM_MENU,
   ST_DISPLAY_CONFIRM_RESET,
   ST_DISPLAY_PAUSE,
   ST_DISPLAY_GAME_OVER,
   ST_DISPLAY_GAME_START,
   ST_DISPLAY_SNAKE,
   ST_DISPLAY_ERROR,
   //----------------------//

   /* POSITION STATES      */
   ST_START_POSITION,
   ST_MOVE_UP,
   ST_MOVE_DOWN,
   ST_MOVE_LEFT,
   ST_MOVE_RIGHT,
   ST_MOVE_STOP,
   //----------------------//

}  STATES;

typedef enum
{
   /*FSM EVENTS            */
   EVT_NO,
   EVT_KEY_UP,
   EVT_KEY_DOWN,
   EVT_KEY_LEFT,
   EVT_KEY_RIGHT,
   EVT_KEY_1,
   EVT_KEY_2,
   EVT_KEY_7,
   EVT_KEY_8,
   EVT_KEY_9,
   EVT_KEY_G,
   EVT_KEY_M,
   EVT_KEY_N,
   EVT_KEY_P,
   EVT_KEY_R,
   EVT_KEY_X,
   EVT_KEY_Y,
   EVT_MODE_0,
   EVT_MODE_1,
   EVT_ERROR,
   //----------------------//

   /*TEST EVENTS           */
   EVT_TEST_COLOUR2,
   EVT_TEST_COLOUR1,
   EVT_TEST_COLOUR3,
   //----------------------//

   /* COLLISION EVENTS     */
   EVT_NO_FOOD_COLLISION,
   EVT_NO_BORDER_COLLISION,
   EVT_NO_SELF_COLLISION,
   EVT_BORDER_COLLISION,
   EVT_SELF_COLLISION,
   EVT_FOOD_SPAWN_COLLISION,
   EVT_FOOD_SPAWN_NO_COLLISION,
   EVT_FOOD_COLLISION,
   EVT_COLLISION,
   EVT_NO_COLLISION,
   //----------------------//


   /* DISPLAY EVENTS       */
   EVT_INITIALIZED,
   EVT_SHUT_DOWN,
   EVT_CONFIRM_MENU,
   EVT_CONFIRM_RESET,
   EVT_PAUSED,
   EVT_GAME_OVER,
   EVT_GAME_STARTED,
   EVT_SNAKE_UP,
   EVT_SNAKE_DOWN,
   EVT_SNAKE_LEFT,
   EVT_SNAKE_RIGHT,
   //----------------------//

   /* POSITION EVENTS      */
   EVT_CHANGE_DIRECTION_UP,
   EVT_CHANGE_DIRECTION_DOWN,
   EVT_CHANGE_DIRECTION_LEFT,
   EVT_CHANGE_DIRECTION_RIGHT,
   EVT_START_POSITION,
   EVT_PAUSE_POSITION,
   //----------------------//

}  EVENTS;

void finiteStateMachineSnake();

#endif // SNAKE_H
