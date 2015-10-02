#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <pthread.h>


const unsigned int MAX_BUFF_SIZE = 1024;
const unsigned int MAX_WORD_LEN  = 128;

typedef unsigned int _RESULT;

typedef enum 
{
	eFILE_NOT_FOUND = -1,
	eGENERIC_FAILURE = 0,
	eGENERIC_SUCCESS = 1,
	
}_ERROR_CODES;

#define DEBUG_ALL (1)

/* Function prototypes */
_RESULT printWordsFromParag(char *inputFile);
unsigned int getNumOfWordsinParag(char *inputFileName);


/****************************************************************************************************
* What needs to be implemented ?                                                                    *
* You are given a paragraph , which contain n number of words, you are given m threads.             *
* What you need to do is , each thread should print one word and give the control to next thread,   * 
* this way each thread will keep on printing one word , in case last thread come, it should invoke  *
* first thread. Printing will repeat until all the words are printed in paragraph.                  * 
* Finally all threads should exit gracefully. What kind of synchronization will use?                *
****************************************************************************************************/



int main(int argc,char *argv[])
{
  unsigned int numOfWordsinParag = 0, rc;
  int numofThreads = 0;
  char *inputFileName = "input.txt";
  rc = printWordsFromParag(inputFileName);
  numOfWordsinParag = getNumOfWordsinParag(inputFileName);
  numofThreads = numOfWordsinParag;
  pthread_t threads[numofThreads];
#ifdef DEBUG_ALL
  printf("Debug2: %d \n", numOfWordsinParag);
#endif
  
  return 0;
}

unsigned int getNumOfWordsinParag(char *inputFileName)
{
	FILE *inputFilePtr = NULL;
	char buff[MAX_BUFF_SIZE];
	char word[MAX_WORD_LEN];
	unsigned int wCount = 0;
	inputFilePtr = fopen(inputFileName,"r");
	if(!inputFilePtr)
	{
		printf("Unable to read the file %s\n",inputFileName);
		return eFILE_NOT_FOUND;
	}
	else
	{
	  while(fgets(buff,MAX_BUFF_SIZE,inputFilePtr)!= NULL) 
	  {
		  int i, isWord, isWhite, length;
		  isWord = 0;
		  length = strlen(buff);
		  for(i = 0; i < length; i++) 
		  {
			 isWhite = (buff[i]!=' ' && buff[i]!= '\n' && buff[i] != '\t') ? 1 : 0;
			 if (isWhite == 1) 
			 {
			   if(isWord != 1) wCount++;
			   isWord = 1;
			 }
			 if(isWhite == 0 && isWord == 1)
			 {
			   isWord = 0;
			 }
		  }
	  }
    }
	fclose(inputFilePtr);
	return wCount;
}

_RESULT printWordsFromParag(char *inputFileName)
{
	FILE *inputFilePtr = NULL;
	char buff[MAX_BUFF_SIZE];
	char word[MAX_WORD_LEN];
	inputFilePtr = fopen(inputFileName,"r");
	if(!inputFilePtr)
	{
		printf("Unable to read the file %s\n",inputFileName);
		return eFILE_NOT_FOUND;
	}
	else
	{	
        while(fgets(buff,MAX_BUFF_SIZE,inputFilePtr)!= NULL) 
        { 
			 int k = 0, j = 0;
			 int length = strlen(buff);
			 while(k < length)
			 {
			   int wordlen = 0;
			   while(buff[j] != ' ' || buff[j] == '\n' || buff[j] == '\t')
			   {
				 word[wordlen++] = buff[j++];
				 k++;
			   }
			   j++;
			   word[wordlen] = '\0';
			   printf("Debug: %s \n", word);
			   memset(word,0,MAX_WORD_LEN);
			 }
        }
	}
    fclose(inputFilePtr);
	return eGENERIC_SUCCESS;
}