#include "mainwindow.h"
#include "StateMachine.h"

#include <QtGui>
#include <QTextEdit>
#include <QPushButton>
#include <iostream>
#include <sstream>

void StateMachine::handleEvent(event eventIn)
{
   while (eventIn != EVT_NO)
   {
      eventIn = stateMachine(eventIn);
   }
}

event StateMachine::stateMachine(event eventIn)
{
   state nextState = ST_NO;
   event eventOut = EVT_NO;

   switch(eventIn)
   {
      case EVT_INITIALIZED:
         currentState = ST_INITIALIZE;
         eventOut = EVT_SEQ;
         break;

      default:
         break;
   }

   switch(currentState)
   {
      case ST_START:
         pWindow->setLogger("-state: Start");
         nextState = ST_INITIALIZE;
         eventOut = EVT_SEQ;
         break;

      case ST_INITIALIZE:
         pWindow->setLogger("-state: Initialize");
         pWindow->enableButtons(true);
         nextState = ST_WAIT_MAIN;
         eventOut = EVT_NO;
         break;

      case ST_WAIT_MAIN:
         pWindow->setLogger("-state: Wait for input");
         switch(eventIn)
         {
            case EVT_START:
               pWindow->setLogger("Start clicked");
               nextState = ST_START_GAME;
               break;

            case EVT_HIGHSCORE:
               pWindow->setLogger("Highscore clicked");
               nextState = ST_HIGHSCORE;
               break;

            case EVT_SETTINGS:
               pWindow->setLogger("Settings clicked");
               nextState = ST_SETTINGS;
               break;

            case EVT_QUIT:
               pWindow->setLogger("Quit clicked");
               nextState = ST_QUIT;
               break;

            default:
               pWindow->setLogger("-ST_WAIT_MAIN ERROR: Unknown event");
               break;
         }
         eventOut = EVT_SEQ;
         break;

      case ST_START_GAME:
         pWindow->setLogger("-state: Start Game");
         pWindow->createGameSpace();
         nextState = ST_WAIT_MAIN;
         eventOut = EVT_NO;
         break;

      case ST_HIGHSCORE:
         pWindow->setLogger("-state: Highscore");
         pWindow->createHighscoreMenu();
         nextState = ST_WAIT_HIGHSCORE;
         eventOut = EVT_NO;
         break;

      case ST_WAIT_HIGHSCORE:
         pWindow->setLogger("-state: Wait Highscore");
         switch(eventIn)
         {
            case EVT_BACK_MAIN:
               pWindow->setLogger("Back clicked");
               pWindow->mainMenu(pWindow->highscoreGroupBox);
               nextState = ST_START;
               break;
            default:
               break;
         }
         eventOut = EVT_SEQ;
         break;

      case ST_SETTINGS:
         pWindow->setLogger("-state: Settings");
         pWindow->createSettingsMenu();
         nextState = ST_WAIT_SETTINGS;
         eventOut = EVT_NO;
         break;

      case ST_WAIT_SETTINGS:
         pWindow->setLogger("-state: Wait Settings");
         switch(eventIn)
         {
            case EVT_BACK_MAIN:
               pWindow->setLogger("Back clicked");
               pWindow->mainMenu(pWindow->settingsGroupBox);
               nextState = ST_START;
               break;
            default:
               break;
         }
         eventOut = EVT_SEQ;
         break;

      case ST_QUIT:
         pWindow->setLogger("-state: Quit");
         exit(EXIT_SUCCESS);
         nextState = ST_WAIT_MAIN;
         eventOut = EVT_NO;
         break;

      case ST_NO:
         pWindow->setLogger("-state: Default");
         break;

      default:
         pWindow->setLogger("ERROR: Unknown state");
         eventOut = EVT_NO;
   }
   currentState = nextState;
   return eventOut;
}

