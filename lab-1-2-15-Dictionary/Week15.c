//Lab week 15 by David Byrne on 27/02/15

#include "stdafx.h"
#include <stdio.h>
#include "string.h"


int countCharOccurence(char *string, char c);
int getOption();
int checkSpelling();
int findWord();

long int nwords = 0;
char dictionary[80000][20];

void main(void)
{
	FILE *fptr;
	char fileName[] = "C:/Users/David/Desktop/webster.txt";
	int option = 0;
	fptr = fopen(fileName, "r");

	if (fptr == NULL)
	{
		printf("File could not be opened !!\n");
		return;
	}
	else
	{
		while (!feof(fptr))
		{

			fscanf(fptr, "%s\n", dictionary[nwords]);
			nwords++;
		}
		fclose(fptr);
	}

	printf("%ld words read from file \n\n", nwords);

	option = getOption();
	while (option != 0)
	{
		if (option == 1) checkSpelling();
		if (option == 2) findWord();
		if (option == 0) return;
		option = getOption();
	}
}

int getOption()
{
	int option = 0;
	puts("Enter all characters in lower case!");
	puts("Options: 1=check spelling, 2=find words, 0=quit\n");
	fflush(stdin);
	scanf("%d", &option);
	return option;
}

int checkSpelling()
{
	int i = 0;
	char temp[20];
	int len;
	int comp;

	puts("Enter word to check");
	fflush(stdin);
	gets(temp);
	len = strlen(temp);
	for (i = 0; i < nwords; i++)
	{
		comp = strcmp(temp, dictionary[i]);
		if (comp == 0)
		{
			printf("Spelling Correct!\n");
			return 1;
		}
	}
	
	puts("Word not found\n");
	return 0;
}

int findWord()
{
	char bestFit[20] = "";
	int numMatches = 0;
	int highestMatch = 0;
	int i = 0, j = 0;
	int charloc = 0;
	char temp[20];
	int tempCount = 0, wordCount = 0;
	int mincharno = 20;
	int numTimesInTemp, numTimesInDict;
	int curBest = 0;
	int flag = 0;

	puts("Enter letters you have");

	scanf("%s", temp);
	int len = strlen(temp);
	// ENTER YOUR CODE HERE
	for (i = 0; i < nwords; i++)
	{
		tempCount = 0;
		mincharno = strlen(dictionary[i]);
		for (j = 0; j < mincharno; j++)
		{
			flag = 0;
			numTimesInTemp = countCharOccurence(temp, dictionary[i][j]);
			numTimesInDict = countCharOccurence(dictionary[i], dictionary[i][j]);
			if (numTimesInDict <= numTimesInTemp)
			{
				tempCount++;
			}
			else
			{
				tempCount = 0;
				flag = 1;
				break;
			}
		}
		if ((tempCount > curBest) && (flag == 0))
		{
			curBest = tempCount;
			strcpy(bestFit, dictionary[i]);
			highestMatch = tempCount;
		}
	}

	printf("Best Fit for \"%s\" is \"%s\"  [%d]\n", temp, bestFit, highestMatch);

	return numMatches;
}

int countCharOccurence(char *string, char c)
{
	int i = 0, count = 0, len = 0;
	len = strlen(string);

	for (i = 0; i<len; i++)
	{
		if (string[i] == c) count++;
	}
	return count;
}
