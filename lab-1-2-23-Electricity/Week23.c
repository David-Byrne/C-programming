#include "stdafx.h"
#include <stdio.h>
#include "string.h"
#include "stdlib.h"

typedef struct
{
	int year;
	double price[12];
	double average;
} electricity;
electricity records[30];

FILE *openFile(char *fileName, char *mode); // open file
void highestAverage( int numYears);
void highestMonth(int numYears);

void main()
{
	char junk[300];
	FILE *fptr = openFile("electricity.txt", "r");
	fgets(junk, 300, fptr);//read in junk lines at beginning of file x4
	fgets(junk, 300, fptr);
	fgets(junk, 300, fptr);
	fgets(junk, 300, fptr);
	double sum = 0;
	int i = 0, m = 0;
	int temp = 1;
	while (!feof(fptr))
	{
		fscanf(fptr, "%d", &temp);
		if (temp == 0) break;
		records[i].year = temp;
		m = 0;
		sum = 0;
		for (; m < 12; m++)
		{
			fscanf(fptr, ",%lf", &records[i].price[m] );
			sum = sum + records[i].price[m];
		}
		records[i].average = (sum / 12);
		i++;
	}
	fclose(fptr);
	int choice = 3;
	while (choice != 0)
	{
		printf("Enter Choice:\n0->Quit\n1->Find the month with the highest price\n2->Find the year with the highest avarage price\n");
		fflush(stdin);
		scanf("%d", &choice);
		switch (choice)
		{
		case 0:
			printf("You have quit\nGoodbye\n");
			break;
		case 1:
			highestMonth(i);
			break;
		case 2:
			highestAverage(i);
			break;
		default:
			printf("Input not recognised...\n");
		}
	}
}

void highestAverage( int numYears)
{
	double highest = 0;
	int i = 0;
	int recordYear = 0;
	for (; i < numYears; i++)
	{
		if (records[i].average > highest)
		{
			recordYear = records[i].year;
			highest = records[i].average;
		}
	}
	printf("The highest annual average price was %lf in %d\n", highest, recordYear);
}

void highestMonth(int numYears)
{
	double highest = 0;
	int i = 0, m = 0;
	char montharray[12][20] = { "January", "February", "March", "April", "May", "June", "July",
		"August", "September", "October", "November", "December" };
	int recordYear = 0;
	int recordMonth = 0;
	for (; i < numYears; i++)
	{
		for (; m < 12; m++)
		{
			if (records[i].price[m] > highest)
			{
				recordMonth = m;
				recordYear = i;
				highest = records[i].price[m];
			}
		}
		m = 0;
	}
	printf("The highest monthly price was %lf in %s of %d\n", highest, montharray[recordMonth] ,records[recordYear].year);
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