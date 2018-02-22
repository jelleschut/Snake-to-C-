#include <stdio.h>
#include "score.h"

int arrayScore[10];

struct highScores {
   int rank;
   int score;
};

struct highScores rankTable[10];

void sortArray(int nElements, int array[])
{
   int i;
   int tmp;

   for(i = 0; i < nElements; i++)
   {
      if(i != 0 && array[i-1] < array[i])
      {
         tmp = array[i];
         array[i] = array[i-1];
         array[i-1] = tmp;
         i = i - 2;
      }
   }
}

void rankScore()
{
   int i;
   for(i = 0; i < 10; i++)
   {
      rankTable[i].rank = i + 1;
      sortArray(10, arrayScore);
      rankTable[i].score = arrayScore[i];
   }
}

void getCurrentHighscore()
{
   int i, rank;
   FILE *highScoreFile;
   highScoreFile = fopen("c:\\Users\\Jelle\\Desktop\\HighScore.txt", "r");

   for(i = 0; i < 10; i++)
   {
      fscanf(highScoreFile, "%d: %d ", &rank, &arrayScore[i]);
   }
}

void updateHighScore()
{
   int newScore, i;
   FILE *highScoreFile;

   getCurrentHighscore();

   sortArray(10,arrayScore);
   newScore = getScore();

   if(newScore >= arrayScore[9])
   {
      arrayScore[9] = newScore;
      rankScore();

      highScoreFile = fopen("c:\\Users\\Jelle\\Desktop\\HighScore.txt", "w+");

      for(i = 0; i < 10; i++)
      {
         fprintf(highScoreFile,"%d:\t%d\n", rankTable[i].rank, rankTable[i].score);
      }
      fclose(highScoreFile);
   }

}

