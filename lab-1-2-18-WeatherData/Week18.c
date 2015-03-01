#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#define FILENAME "C:\\Users\\David\\Desktop\\Weather.dat"

FILE *openFile(char *fileName, char *mode);

void enterMeasurements(FILE *point);
int findDay(FILE *point);
void listAll(FILE *point);

struct weather 
{
	char date[10];
	int minTemp;
	int maxTemp;
	int rainfall;
	char description[20];
};

int main()
{
	FILE *fptr;
	fptr = openFile(FILENAME, "ab+");

	int option = 1;

	printf("1:Enter Reading\n2:Find a Day's weather\n3:List All\n4:Quit\n");
	scanf("%d", &option);
	while (option != 0)
	{
		switch (option)
		{
		case 1:
			enterMeasurements(fptr);
			break;
		case 2:
			findDay(fptr);
			break;
		case 3:
			listAll(fptr);
			break;
		case 4:
			printf("Goodbye\n");
			fclose(fptr);
			return 0;
		default:
			printf("Not recognised\n");
			break;
		}
		printf("1:Enter Reading\n2:Find a Day's weather\n3:List All\n4:Quit\n");
		scanf("%d", &option);
	}
	fclose(fptr);
	return 1;
}

void enterMeasurements(FILE *fptr)
{
	struct weather entered;
	printf("What is the Date? Enter in form ddmmyyyy without gaps or slashes\n");
	scanf("%s", entered.date);
	printf("What is the Min Temperature?\n");
	scanf("%d", &entered.minTemp);
	printf("What is the Max Temperature?\n");
	scanf("%d", &entered.maxTemp);
	printf("What is the RainFall?\n");
	scanf("%d", &entered.rainfall);
	printf("What is the weather like\n");
	fflush(stdin);
	gets(entered.description);
	fwrite(&entered, sizeof(struct weather),1, fptr);
}

int findDay( FILE *fptr)
{
	fclose(fptr);
	fptr = openFile(FILENAME, "rb");
	char dateWanted[10];
	printf("What is the Date you want? Enter in form ddmmyyyy without gaps or slashes\n");
	scanf("%s", dateWanted);
	while (!feof(fptr))
	{
		struct weather tempday;
		fread(&tempday, sizeof(struct weather), 1, fptr);//better than feof as there can be some data left due to concurrency problems. This ensures an entire waether struct is there
		if (strcmp(dateWanted, tempday.date) == 0)
		{
			printf("-----------------------------------------------------\n");
			printf("Date: \t\t%c%c/%c%c/%c%c%c%c", tempday.date[0], tempday.date[1], tempday.date[2], tempday.date[3], tempday.date[4], tempday.date[5], tempday.date[6], tempday.date[7]);
			printf("\nMin Temp: \t%d\nMax Temp: \t%d\nRainFall: \t%d\nDespription: \t%s\n\n",tempday.minTemp, tempday.maxTemp, tempday.rainfall, tempday.description);
			printf("-----------------------------------------------------\n");
			fclose(fptr);
			fptr = openFile(FILENAME, "ab+");
			return 1;
		}

	}
	printf("Not Found\n");
	fclose(fptr);
	fptr = openFile(FILENAME, "ab+");
	return 0;
}

void listAll(FILE *fptr)
{
	fclose(fptr);// closes file so we can open it in rb mode
	fptr = openFile(FILENAME, "rb");
	struct weather tempday;
	while (fread(&tempday, sizeof(struct weather), 1, fptr)==1)//better than feof as there can be some data left due to concurrency problems. This ensures an entire waether struct is there
	{
		printf("-----------------------------------------------------\n");
		printf("Date: \t\t%c%c/%c%c/%c%c%c%c", tempday.date[0], tempday.date[1], tempday.date[2], tempday.date[3], tempday.date[4], tempday.date[5], tempday.date[6], tempday.date[7]);
		printf("\nMin Temp: \t%d\nMax Temp: \t%d\nRainFall: \t%d\nDespription: \t%s\n\n", tempday.minTemp, tempday.maxTemp, tempday.rainfall, tempday.description);
	}
	printf("-----------------------------------------------------\n");
	fclose(fptr);
	fptr = openFile(FILENAME, "ab+");
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
