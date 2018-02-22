#include <stdio.h>

#include "score.h"
#include "display.h"
#include "fsm.h"
#include "position.h"
#include "macros.h"

int foodY;
int foodX;


EVENTS borderCollision()                                                ///Used to check for border collision
{
   if(snakeY[0] < BORDERTHICK || snakeY[0] >= (HEIGHT - BORDERTHICK))   //if SNAKE head is in border
   {
      return EVT_BORDER_COLLISION;                                      //border collision
   }
   if(snakeX[0] < BORDERTHICK || snakeX[0] >= (WIDTH - BORDERTHICK))    //if SNAKE head is in border
   {
      return EVT_BORDER_COLLISION;                                      //border collision
   }
   return EVT_NO_BORDER_COLLISION;                                      //else no border collision
}

EVENTS selfCollision()                                                  ///Used to check for self collision
{
   int i;
   int j = getLength();
   for (i = 2; i < SNAKELENGTH + j; i++)                            //for every bodypart
   {
      if(( snakeY[0] == snakeY[i]) && ( snakeX[0] == snakeX[i]))        //if head hits bodypart
      {
         return EVT_SELF_COLLISION;                                     //self collision
      }
   }
   return EVT_NO_SELF_COLLISION;                                        //else no collision
}

EVENTS foodSpawnCollision()                              ///Used to check if food spawns in SNAKE current position
{
   int i;
   int j = getLength();
   foodY = positionFoodY();                              //retrieve food Y-coordinate
   foodX = positionFoodX();                              //retrieve food X-coordinate



   for (i = 0; i < SNAKELENGTH + j; i++)             //for every bodypart
   {
      if(( foodY == snakeY[i]) && ( foodX == snakeX[i])) //if food hits bodypart
      {
         return EVT_FOOD_SPAWN_COLLISION;                //spawncollision
      }
   }
   return EVT_FOOD_SPAWN_NO_COLLISION;                   //else no spawn collision
}

int foodNoCollisionY()                                   ///Used to retrieve food Y-coordinates for use in other functions
{
   return foodY;
}

int foodNoCollisionX()                                   ///Used to retrieve food X-coordinates for use in other functions
{
   return foodX;
}

EVENTS foodCollision()                                   ///Used to check for food collision with SNAKE head
{
   if((foodY == snakeY[0]) && (foodX == snakeX[0]))      //if SNAKE head collides with food
   {
      return EVT_FOOD_COLLISION;                         //food collision
   }
   return EVT_NO_FOOD_COLLISION;                         //else no food collision
}

EVENTS collisionChecker()                                ///Used to check for Game Over conditions, combines self/border collision
{
   if (borderCollision() == EVT_BORDER_COLLISION)
   {
      return EVT_COLLISION;
   }

   if(selfCollision() == EVT_SELF_COLLISION)
   {
      return EVT_COLLISION;
   }

   return EVT_NO_COLLISION;
}
