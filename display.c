#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mode.h"
#include "score.h"
#include "fsm.h"
#include "position.h"
#include "collision.h"
#include "macros.h"

char display[HEIGHT][WIDTH];                          //Playing field as 2D array, globally defined so every
                                                      //function can add to the field
int snakeY[255];                                      //Array of Y-coordinates for SNAKE
int snakeX[255];                                      //Array of X-coordinates for SNAKE
typedef char PIXELMAP[7][5];                          //typedef of 2D array of characters PIXELMAP, used for printing pixelated characters

void screenShot();                                    ///used to screenshot playingfield before putting text over it

//-----------------------------------------------------------------------------------------------------//
// Basic screen functions

void newLinePrinter(int numberOfNewLines)
{
   int i;
   for(i = 0; i < numberOfNewLines; i++)
   {
      printf("\n");
   }
}

//Printing screen to terminal
void printField(void)                                 ///used to send the current state of display to LEDs
{
   int i,j;
   //newLinePrinter(30);
   for(i = 0; i < HEIGHT; i++)
   {
      for(j = 0; j < WIDTH; j++)
      {
         printf("%c", display[i][j]);                 //drive one row of LEDs
      }
      printf("\n");                                   //next row
   }
}

//Empty display with borders
void standardDisplay(void)                            ///Used to show borders
{
   int i,j;
   for(i = 0; i < HEIGHT; i++)
   {
      for(j = 0; j < WIDTH; j++)
      {
         if(i < BORDERTHICK)                                       // top 2 lines are borders
         {
            display[i][j] = LEDBORDER;
         }
         if(i >= HEIGHT - BORDERTHICK && i < HEIGHT)               // bottom 2 lines are borders
         {
            display[i][j] = LEDBORDER;
         }
         if(j < BORDERTHICK)                                       // first 2 columns are borders
         {
            display[i][j] = LEDBORDER;
         }
         if(j >= WIDTH - BORDERTHICK && i < WIDTH)                 // last 2 borders are columns
         {
            display[i][j] = LEDBORDER;
         }
         if((i >= BORDERTHICK && i < HEIGHT - BORDERTHICK) && (j >= BORDERTHICK && j < WIDTH - BORDERTHICK))  // area between borders is playingfield
         {
            display[i][j] = LEDOFF;
         }
      }
   }
}

//String writing function
void writeString(int startY, char *string)                        ///Used to write strings to display in Dev mode
{
   int i;
   int lengthString  = strlen(string);                            //determine string length
   int startX = (WIDTH/2) - (lengthString/2);                     //start at right offset on X-axis

   for (i = 0; i < lengthString; i++)
   {
      display[startY][startX+i] = string[i];                      //write string in display
   }
}
//Writing strings in pixel form
void writePixel(int startY, int startX, PIXELMAP string)          ///Used to write letters to display in user mode
{
   int i,j;
   for(i = 0; i < 7; i++)                                         //pixelmaps are 7x5
   {
      for (j = 0; j < 5; j++)
      {
         display[startY+i][startX+j] = string[i][j];              //write letter to display
      }
   }
}

//Test colour 1
void displayTestColour1()                    ///Used to write colour 1 to all of display
{
   int i,j;
   for(i = 0; i < HEIGHT; i++)
   {
      for(j = 0; j < WIDTH; j++)
      {
         display[i][j] = COLOUR1;
      }
   }
}

//Test colour 2
void displayTestColour2()                    ///Used to write colour 2 to all of display
{
   int i,j;
   for(i = 0; i < HEIGHT; i++)
   {
      for(j = 0; j < WIDTH; j++)
      {
         display[i][j] = COLOUR2;
      }
   }
}

//Test colour 3
void displayTestColour3()                    ///Used to write colour 3 to all of display
{
   int i,j;
   for(i = 0; i < HEIGHT; i++)
   {
      for(j = 0; j < WIDTH; j++)
      {
         display[i][j] = COLOUR3;
      }
   }
}

//Display Off
void displayShutDown(void)                   ///Used to write off to all of display
{
   int i,j;
   for(i = 0; i < HEIGHT; i++)
   {
      for(j = 0; j < WIDTH; j++)
      {
         display[i][j] = LEDOFF;
      }
   }
}

//end of basic screen functions
//-----------------------------------------------------------------------------------------------------//


//-----------------------------------------------------------------------------------------------------//
//Display States

/*PIXELMAP WRITING*/
//Main menu
void displayMenuPixel()                      ///Used to write main menu to display
{

   PIXELMAP oneStart    =     PIXEL1;        //all letters used are defined in macros.h
   PIXELMAP colonStart  =     PIXELCOLON;
   PIXELMAP sStart      =     PIXELS;
   PIXELMAP tStart      =     PIXELT;
   PIXELMAP aStart      =     PIXELA;
   PIXELMAP rStart      =     PIXELR;
   PIXELMAP t2Start     =     PIXELT;

   PIXELMAP twoQuit     =     PIXEL2;
   PIXELMAP colonQuit   =     PIXELCOLON;
   PIXELMAP qQuit       =     PIXELQ;
   PIXELMAP uQuit       =     PIXELU;
   PIXELMAP iQuit       =     PIXELI;
   PIXELMAP tQuit       =     PIXELT;

   standardDisplay();                        //use borders only in main menu

   writePixel(6,9,oneStart);                 //write text, one letter at a time
   writePixel(6,15,colonStart);
   writePixel(6,21,sStart);
   writePixel(6,27,tStart);
   writePixel(6,33,aStart);
   writePixel(6,39,rStart);
   writePixel(6,45,t2Start);

   writePixel(17,9,twoQuit);
   writePixel(17,15,colonQuit);
   writePixel(17,21,qQuit);
   writePixel(17,27,uQuit);
   writePixel(17,33,iQuit);
   writePixel(17,39,tQuit);
}

//Pause menu
void displayPausePixel()                     ///used write pause menu to display
{
   PIXELMAP pPause      =     PIXELP;
   PIXELMAP aPause      =     PIXELA;
   PIXELMAP uPause      =     PIXELU;
   PIXELMAP sPause      =     PIXELS;
   PIXELMAP ePause      =     PIXELE;

   PIXELMAP pPressP     =     PIXELP;
   PIXELMAP rPressP     =     PIXELR;
   PIXELMAP ePressP     =     PIXELE;
   PIXELMAP sPressP     =     PIXELS;
   PIXELMAP s2PressP    =     PIXELS;
   PIXELMAP P2PressP    =     PIXELP;

   screenShot();                             //screenshot snake and food in background

   writePixel(6,15,pPause);
   writePixel(6,21,aPause);
   writePixel(6,27,uPause);
   writePixel(6,33,sPause);
   writePixel(6,39,ePause);

   writePixel(17,9,pPressP);
   writePixel(17,15,rPressP);
   writePixel(17,21,ePressP);
   writePixel(17,27,sPressP);
   writePixel(17,33,s2PressP);

   writePixel(17,45,P2PressP);
}

//Confirm main menu
void displayconfirmMenuPixel()               ///Used to write confirmation to main menu to display
{
   PIXELMAP mMenu       =     PIXELM;
   PIXELMAP eMenu       =     PIXELE;
   PIXELMAP nMenu       =     PIXELN;
   PIXELMAP uMenu       =     PIXELU;
   PIXELMAP questionMenu=     PIXELQUESTION;

   PIXELMAP yYesNO      =     PIXELY;
   PIXELMAP slashYesNO  =     PIXELSLASH;
   PIXELMAP nYesNO      =     PIXELN;

   screenShot();

   writePixel(6,15,mMenu);
   writePixel(6,21,eMenu);
   writePixel(6,27,nMenu);
   writePixel(6,33,uMenu);
   writePixel(6,39,questionMenu);

   writePixel(17,21,yYesNO);
   writePixel(17,27,slashYesNO);
   writePixel(17,33,nYesNO);

}

//Confirm reset menu
void displayConfirmResetPixel()              ///Used to write confirmation reset to display
{
   PIXELMAP rReset      =     PIXELR;
   PIXELMAP eReset      =     PIXELE;
   PIXELMAP sReset      =     PIXELS;
   PIXELMAP e2Reset     =     PIXELE;
   PIXELMAP tReset      =     PIXELT;
   PIXELMAP questionReset=    PIXELQUESTION;

   PIXELMAP yYesNO      =     PIXELY;
   PIXELMAP slashYesNO  =     PIXELSLASH;
   PIXELMAP nYesNO      =     PIXELN;

   screenShot();

   writePixel(6,12,rReset);
   writePixel(6,18,eReset);
   writePixel(6,24,sReset);
   writePixel(6,30,e2Reset);
   writePixel(6,36,tReset);
   writePixel(6,42,questionReset);

   writePixel(17,21,yYesNO);
   writePixel(17,27,slashYesNO);
   writePixel(17,33,nYesNO);

}

//Score
void scorePixel()                            ///Used to convert score digits to individual PIXELMAPS
{
   int intScore = getScore();
   char charScore[5];
   int index, length, i;

   itoa(intScore, charScore, 10);               //convert integer to string
   length = strlen(charScore);               //determine number of digits

   static PIXELMAP arrayPixelMaps[10]=       //create array of PIXELMAPS to choose from
   {PIXEL0,PIXEL1,PIXEL2,PIXEL3,PIXEL4,
    PIXEL5,PIXEL6,PIXEL7,PIXEL8,PIXEL9};

   for(i = 0; i < length; i++)               //for every digit
   {
      switch(charScore[i])                   //check which number it is
      {
         case '0':
            index = 0;                       //index corresponds with PIXELMAP position of the number in arrayPixelMaps
            break;
         case '1':
            index = 1;
            break;
         case '2':
            index = 2;
            break;
         case '3':
            index = 3;
            break;
         case '4':
            index = 4;
            break;
         case '5':
            index = 5;
            break;
         case '6':
            index = 6;
            break;
         case '7':
            index = 7;
            break;
         case '8':
            index = 8;
            break;
         case '9':
            index = 9;
            break;
      }
      int xPos = (39 + (i * 6));                      //after every digit, change start location of writing
      writePixel(12, xPos, arrayPixelMaps[index]);    //write pixelated digit
   }

}

//Game over
void displayGameOverPixel()                  ///Used to write Game Over menu and score to display
{
   PIXELMAP gGame       =     PIXELG;
   PIXELMAP aGame       =     PIXELA;
   PIXELMAP mGame       =     PIXELM;
   PIXELMAP eGame       =     PIXELE;
   PIXELMAP oOver       =     PIXELO;
   PIXELMAP vOver       =     PIXELV;
   PIXELMAP eOver       =     PIXELE;
   PIXELMAP rOver       =     PIXELR;

   PIXELMAP sScore      =     PIXELS;
   PIXELMAP cScore      =     PIXELC;
   PIXELMAP oScore      =     PIXELO;
   PIXELMAP rScore      =     PIXELR;
   PIXELMAP eScore      =     PIXELE;
   PIXELMAP colonScore  =     PIXELCOLON;

   PIXELMAP pPressY     =     PIXELP;
   PIXELMAP rPressY     =     PIXELR;
   PIXELMAP ePressY     =     PIXELE;
   PIXELMAP sPressY     =     PIXELS;
   PIXELMAP s2PressY    =     PIXELS;

   PIXELMAP yPressY     =     PIXELY;


   writePixel(4,3,gGame);
   writePixel(4,9,aGame);
   writePixel(4,15,mGame);
   writePixel(4,21,eGame);

   writePixel(4,33,oOver);
   writePixel(4,39,vOver);
   writePixel(4,45,eOver);
   writePixel(4,51,rOver);

   writePixel(12,3,sScore);
   writePixel(12,9,cScore);
   writePixel(12,15,oScore);
   writePixel(12,21,rScore);
   writePixel(12,27,eScore);
   writePixel(12,33,colonScore);

   scorePixel();                             //get score as pixels

   writePixel(20,9,pPressY);
   writePixel(20,15,rPressY);
   writePixel(20,21,ePressY);
   writePixel(20,27,sPressY);
   writePixel(20,33,s2PressY);

   writePixel(20,45,yPressY);
}

//Error!
void displayErrorPixel(void)                 ///Used to display error message
{
   PIXELMAP eError      =     PIXELP;
   PIXELMAP rError      =     PIXELA;
   PIXELMAP r2Error     =     PIXELU;
   PIXELMAP oError      =     PIXELS;
   PIXELMAP r3Error     =     PIXELE;
   PIXELMAP exclError   =     PIXELEXCL;

   PIXELMAP pPressY     =     PIXELP;
   PIXELMAP rPressY     =     PIXELR;
   PIXELMAP ePressY     =     PIXELE;
   PIXELMAP sPressY     =     PIXELS;
   PIXELMAP s2PressY    =     PIXELS;

   PIXELMAP YPressY     =     PIXELP;

   screenShot();

   writePixel(6,12,eError);
   writePixel(6,18,rError);
   writePixel(6,24,r2Error);
   writePixel(6,30,oError);
   writePixel(6,36,r3Error);
   writePixel(6,42,exclError);

   writePixel(17,9 ,pPressY);
   writePixel(17,15,rPressY);
   writePixel(17,21,ePressY);
   writePixel(17,27,sPressY);
   writePixel(17,33,s2PressY);

   writePixel(17,45,YPressY);
}
/*END OF PIXELMAP WRITING*/

/*DEV/SIM MODE WRITING*/
//Main Menu
void displayMenu(void)                       ///Used to write main menu to display in dev/sim mode
{
   char newGame[20]  = "1: NEW GAME ";
   char shutDown[20] = "2: SHUT DOWN";

   standardDisplay();

   writeString(6, newGame);
   writeString(10, shutDown);
}

//Return to main menu
void displayPause(void)                      ///Used to write pause menu to display in dev/sim mode
{
   char gamePaused[40] = "GAME PAUSED";
   char pressP[40] = "PRESS P TO CONTINUE";

   screenShot();

   writeString(7, gamePaused);
   writeString(9, pressP);
}

//Return to main menu
void displayConfirmMenu(void)                ///Used to write confirmation to main menu to display in dev/sim mode
{
   char areYouSureReturn[40] = "ARE YOU SURE YOU WANT TO RETURN";
   char toMainMenu[40] = "TO MAIN MENU?";
   char yesOrNo[20] = "Y / N";

   screenShot();

   writeString(7, areYouSureReturn);
   writeString(8, toMainMenu);
   writeString(9, yesOrNo);
}

//Reset menu
void displayConfirmReset(void)               ///Used to write confirmation to reset to display in dev/sim mode
{
   char areYouSureReset[40] = "ARE YOU SURE YOU WANT TO RESET?";
   char yesOrNo[20] = "Y / N";

   screenShot();

   writeString(7, areYouSureReset);
   writeString(9, yesOrNo);

}

//Reset menu
void displayGameOver(void)                   ///Used to write Game Over menu and score to display in dev/sim mode
{
   char gameOver[40] = "GAME OVER";
   char finalScore[20] = "FINAL SCORE: ";
   char pressContinue[20] = "PRESS Y TO CONTINUE";
   char charScore[5];

   int intScore = getScore();

   itoa(intScore, charScore, 10);
   strcat(finalScore, charScore);

   writeString(5, gameOver);
   writeString(7, finalScore);
   writeString(9, pressContinue);

}

//Error!
void displayError(void)                      ///Used to write Error to display in dev/sim mode
{
   char errorMessage[40] = "ERROR!";
   char pressY[40] = "PRESS Y FOR MAIN MENU";

   screenShot();

   writeString(7, errorMessage);
   writeString(9, pressY);
}
/*END OFDEV/SIM MODE WRITING*/

//End of display states
//-----------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------//
//Display SNAKE

void displayCollision(int Y, int X)          ///Used to write the collision X to display
{
   display[Y-2][X+2] = LEDCOLLISION;
   display[Y-2][X-2] = LEDCOLLISION;
   display[Y-1][X-1] = LEDCOLLISION;
   display[Y-1][X+1] = LEDCOLLISION;
   display[Y][X] = LEDCOLLISION;
   display[Y+1][X-1] = LEDCOLLISION;
   display[Y+1][X+1] = LEDCOLLISION;
   display[Y+2][X-2] = LEDCOLLISION;
   display[Y+2][X+2] = LEDCOLLISION;

}

void displayNewFood()                              ///Used to write food to display at new location
{
   randomFoodY();                                  //randomly choose Y-coordinate
   randomFoodX();                                  //randomly choose X-coordinate

   EVENTS spawnChecker = foodSpawnCollision();     //Location Checked for collision with SNAKE on spawn

   while(spawnChecker == EVT_FOOD_SPAWN_COLLISION) //while food will spawn on SNAKE
   {
      randomFoodY();                               //create new randomly choose Y-coordinate
      randomFoodX();                               //create new randomly choose X-coordinate
      foodSpawnCollision();                        //check again
   }

   int Y = foodNoCollisionY();                     //safe food Y-coordinate
   int X = foodNoCollisionX();                     //safe food X-coordinate

   display[Y][X] = LEDFOOD;                        //write LEDFOOD to display
}

void displayFood()                                 ///used to write food to display
{
   int Y = foodNoCollisionY();
   int X = foodNoCollisionX();

   display[Y][X] = LEDFOOD;
}


void displaySnakeStartPosition()                      ///used to write SNAKE starting position to display
{
   int i;

   snakeY[0] = STARTY;                                //SNAKE head Y-coordinate will start on STARTY
   snakeX[0] = STARTX;                                //SNAKE head X-coordinate will start on STARTY

   for(i = 0; i < SNAKELENGTH; i++)
   {

      snakeY[i+1] = STARTY;                           //SNAKE body will start horizontally
      snakeX[i+1] = STARTX-i;                         //SNAKE body will start behind head

      display[snakeY[i+1]][snakeX[i+1]] = LEDSNAKE;   //write SNAKE position to display

   }
}

void displaySnakePosition()                           ///Used to write SNAKE position to display after start
{
   int i;
   int j = getLength();
   for(i = SNAKELENGTH + j; i > 0; i--)
   {
      snakeY[i] = snakeY[i-1];                        //all bodyparts' coordinates are now their predecessing
      snakeX[i] = snakeX[i-1];                        //bodyparts coordinates from last loop

      display[snakeY[i]][snakeX[i]] = LEDSNAKE;       //write SNAKE position to display
   }



}

void screenShot()                                     ///used to screenshot playingfield in current state
{
   int i;
   int j = getLength();

   standardDisplay();                                 //borders
   for(i = 0; i < SNAKELENGTH + j; i++)
   {
      display[snakeY[i]][snakeX[i]] = LEDSNAKE;       //SNAKE
   }
   displayFood();                                     //food
}


void displayStart()                                   ///Used to write the starting playingfield to display
{
   standardDisplay();                                 //borders
   displaySnakeStartPosition();                       //SNAKE at start
   displayNewFood();                                  //new food
}

void displaySnake()                                   ///Used to write playingfield to display
{
   standardDisplay();                                 //borders
   displaySnakePosition();                            //SNAKE during gameplay
   displayFood();                                     //food
}
//End of display SNAKE
//-----------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------//
//Display input handler

//-------------------------------------------------------//
//EVENTS are sent from FSM at the start of every state   //
//When a new state is entered which requires an update   //
//on screen or on LED matrix, the Display input handler  //
//processes this and writes the corresponding information//
//to display. Which is then sent to screen or LED matrix //
//-------------------------------------------------------//

void displayScreen(EVENTS currentEvent)               ///Used to determine what to display
{
   STATES displayState = ST_DISPLAY_STANDBY;          //standard state

   STATES displayMode = getMode();

   switch(displayMode)                                 //Dev/Sim or user mode
   {
      case ST_MODE_0:                                 //Dev/Sim mode
         switch(currentEvent)                         //This switch handles what to write to display
         {
            case EVT_SHUT_DOWN:
               displayShutDown();
               displayState = ST_DISPLAY_SHUT_DOWN;   //States are used to check for self/border/foodcollision later on
               break;

            case EVT_INITIALIZED:
               displayMenu();
               displayState = ST_DISPLAY_MAIN_MENU;
               break;

            case EVT_TEST_COLOUR2:
               displayTestColour1();
               displayState = ST_DISPLAY_TEST_GREEN;
               break;

            case EVT_TEST_COLOUR1:
               displayTestColour2();
               displayState = ST_DISPLAY_TEST_RED;
               break;

            case EVT_TEST_COLOUR3:
               displayTestColour3();
               displayState = ST_DISPLAY_TEST_YELLOW;
               break;

            case EVT_CONFIRM_MENU:
               displayConfirmMenu();
               displayState = ST_DISPLAY_CONFIRM_MENU;
               break;

            case EVT_CONFIRM_RESET:
               displayConfirmReset();
               displayState = ST_DISPLAY_CONFIRM_RESET;
               break;

            case EVT_PAUSED:
               displayPause();
               displayState = ST_DISPLAY_PAUSE;
               break;

            case EVT_GAME_OVER:
               displayGameOver();
               displayState = ST_DISPLAY_GAME_OVER;
               break;

            case EVT_ERROR:
               displayError();
               displayState = ST_DISPLAY_ERROR;

            case EVT_GAME_STARTED:
               displayStart();
               displayState = ST_DISPLAY_GAME_START;
               break;

            case EVT_SNAKE_UP:
               displaySnake();
               displayState = ST_DISPLAY_SNAKE;
               break;

            case EVT_SNAKE_DOWN:
               displaySnake();
               displayState = ST_DISPLAY_SNAKE;
               break;

            case EVT_SNAKE_LEFT:
               displaySnake();
               displayState = ST_DISPLAY_SNAKE;
               break;

            case EVT_SNAKE_RIGHT:
               displaySnake();
               displayState = ST_DISPLAY_SNAKE;
               break;

            default:
               displayError();
               displayState = ST_DISPLAY_ERROR;
         }
         break;

      case ST_MODE_1:                                 //user mode
         switch(currentEvent)
         {
            case EVT_SHUT_DOWN:
               displayShutDown();
               displayState = ST_DISPLAY_SHUT_DOWN;
               break;

            case EVT_INITIALIZED:
               displayMenuPixel();
               displayState = ST_DISPLAY_MAIN_MENU;
               break;

            case EVT_TEST_COLOUR2:
               displayTestColour1();
               displayState = ST_DISPLAY_TEST_GREEN;
               break;

            case EVT_TEST_COLOUR1:
               displayTestColour2();
               displayState = ST_DISPLAY_TEST_RED;
               break;

            case EVT_TEST_COLOUR3:
               displayTestColour3();
               displayState = ST_DISPLAY_TEST_YELLOW;
               break;

            case EVT_CONFIRM_MENU:
               displayconfirmMenuPixel();
               displayState = ST_DISPLAY_CONFIRM_MENU;
               break;

            case EVT_CONFIRM_RESET:
               displayConfirmResetPixel();
               displayState = ST_DISPLAY_CONFIRM_RESET;
               break;

            case EVT_PAUSED:
               displayPausePixel();
               displayState = ST_DISPLAY_PAUSE;
               break;

            case EVT_GAME_OVER:
               displayGameOverPixel();
               displayState = ST_DISPLAY_GAME_OVER;
               break;

            case EVT_ERROR:
               displayErrorPixel();
               displayState = ST_DISPLAY_ERROR;

            case EVT_GAME_STARTED:
               displayStart();
               displayState = ST_DISPLAY_GAME_START;
               break;

            case EVT_SNAKE_UP:
               displaySnake();
               displayState = ST_DISPLAY_SNAKE;
               break;

            case EVT_SNAKE_DOWN:
               displaySnake();
               displayState = ST_DISPLAY_SNAKE;
               break;

            case EVT_SNAKE_LEFT:
               displaySnake();
               displayState = ST_DISPLAY_SNAKE;
               break;

            case EVT_SNAKE_RIGHT:
               displaySnake();
               displayState = ST_DISPLAY_SNAKE;
               break;

            default:
               displayErrorPixel();
               displayState = ST_DISPLAY_ERROR;
         }
         break;
      default:
         displayMode = ST_MODE_1;
   }

   if(displayState == ST_DISPLAY_SNAKE)               //if game is played
   {
      EVENTS food = foodCollision();                  //check for food collision
      EVENTS collision = collisionChecker();          //check for Game Over

      if(food == EVT_FOOD_COLLISION)                  //if food collision
      {
         increaseScore();                             //increase score (and length)
         increaseLength();
         displayNewFood();                            //new food
      }

      if (collision == EVT_COLLISION)                 //if selfcollision or bordercollision
      {
         displayCollision(snakeY[0], snakeX[0]);      //write collision to display
      }
   }
   int x = getScore();
   printf("%d", x);
   system("cls");
   printField();                                      //Send display data to screen or LED matrix
}








