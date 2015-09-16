#include "stdafx.h"
#include "stdlib.h"
#include <stdio.h>
#include "string.h"

#define MARGIN 1500

FILE *openFile(char *fileName, char *mode);
void chooseFile();
char *file;

void main()
{
	char lineData[100];
	double cntr = 0;
	int time = 0, x = 0, y = 0, z = 0;
	int maxX = 0, maxY = 0, maxZ = 0;
	int minX = 9999, minY = 9999, minZ = 9999;
	FILE *fptr;
	chooseFile();
	fptr = openFile(file, "r");
	fgets(lineData, 100, fptr);//takes in first, unnecessary line
	fscanf(fptr, "%d,%d,%d,%d", &time, &x, &y, &z);
	float averagex = x / 1.0;
	float averagey = y / 1.0;
	float averagez = z / 1.0;
	int flag = 0;
	cntr = 1;
	while (!feof(fptr))
	{
		fscanf(fptr, "%d,%d,%d,%d", &time, &x, &y, &z);
		if (((x - averagex) > MARGIN) || ((x - averagex) < -MARGIN)) 
		{
			printf("\n\nfall at %d\n\n", time);
			flag = 1;
			break;
		}
		else if (((y - averagey) > MARGIN ) || ((y - averagey) < -MARGIN)) 
		{ 
			printf("\n\nfall at %d\n\n", time);
			flag = 1;
			break;
		}
		else if (((z - averagez) > MARGIN ) || ((z - averagez) < -MARGIN )) 
		{ 
			printf("\n\nfall at %d\n\n", time);
			flag = 1;
			break;
		}
		else
		{
			averagex = (x + averagex) / 2;//weights newer values more as they are more relevant
			averagey = (y + averagey) / 2;
			averagez = (z + averagez) / 2;
		}
		cntr++;
	}
	if (flag == 0) printf("\n\nNo fall was detected\n\n");
}

FILE * openFile(char *fileName, char *mode)
{
	FILE *fptr = fopen(fileName, mode);
	if (fptr == NULL)
	{
		printf("Error opening file ! \n");
	}
	return fptr;
}

void chooseFile()
{
	int option = 0;
	printf("Press 1 for fall1.csv\nPress 2 for fall2.csv\nPress 3 for fall3.csv\nPress 4 for slowWalk1.csv\nPress 5 for slowWalk2.csv\nPress 6 for slowWalk3.csv\n");
	fflush(stdin);
	scanf("%d", &option);
	switch (option)
	{
	case 1: 
		file = "fall1.csv";
		printf("You chose %s", file);
		break;
	case 2:
		file = "fall2.csv";
		printf("You chose %s", file);
		break;
	case 3:
		file = "fall3.csv";
		printf("You chose %s", file);
		break;
	case 4:
		file = "slowWalk1.csv";
		printf("You chose %s", file);
		break;
	case 5:
		file = "slowWalk2.csv";
		printf("You chose %s", file);
		break;
	case 6:
		file = "slowWalk3.csv";
		printf("You chose %s", file);
		break;
	default:
		printf("That is not an option.");
		file = "fall1.csv";
		printf(" %s was chosen as it's the default choice", file);
		break;

	}
}