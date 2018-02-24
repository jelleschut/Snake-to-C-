#ifndef STATEMACHINE_H
#define STATEMACHINE_H
typedef enum
{

   ST_NO,
   ST_START, ST_INITIALIZE, ST_WAIT_MAIN,
   ST_START_GAME,

   ST_HIGHSCORE, ST_WAIT_HIGHSCORE,

   ST_SETTINGS, ST_WAIT_SETTINGS,

   ST_QUIT,

}  state;

typedef enum
{
   EVT_NO, EVT_SEQ, EVT_INITIALIZED,
   EVT_START, EVT_HIGHSCORE, EVT_SETTINGS, EVT_QUIT,
   EVT_BACK_MAIN,

}  event;

class MainWindow;
class GameWindow;

class StateMachine
{
public:
   StateMachine(MainWindow *pWindow):
      pWindow(pWindow),
      currentState(ST_START) {}
   StateMachine(GameWindow *pGWindow):
      pGWindow(pGWindow),
      currentState(ST_START_GAME) {}

   ~StateMachine() {}

   void handleEvent(event eventIn);

private:
   MainWindow *pWindow;
   GameWindow *pGWindow;
   state currentState;
   event stateMachine(event eventIn);


};

#endif // STATEMACHINE_H
