//Week 16 programming lab by David Byrne. 03/02/15

#include "stdafx.h"
#include <stdio.h>
#include "string.h"
#include "stdlib.h"

//float fixtotal(char inputtotal[10]);

struct salerec
{
	char date[10];
	//int day;
	//int month;
	//int year;
	char region[10];
	char rep[10];
	char item[10];
	int units;
	float unitCost;
	float total;

};

FILE *openFile(char *fileName, char *mode);

void main()
{
	struct salerec salerecs[100];
	int i = 0;
	char linedata[1000];
	char deliminator[10] = "\t";
	FILE *fptr;
	fptr = openFile("C:/Users/David/Desktop/SampleData.txt", "r");
	fgets(linedata, 1000, fptr);
	char *token;
	//printf("test");
	while (!feof(fptr))
	{
		fgets(linedata, 1000, fptr);
		token = strtok(linedata, deliminator);
		
		//printf("token is %s\n", token);
		strcpy(salerecs[i].date, token);
		token = strtok(NULL, deliminator);
		//printf("token is %s\n", token);
		strcpy(salerecs[i].region, token);
		token = strtok(NULL, deliminator);
		//printf("token is %s\n", token);
		strcpy(salerecs[i].rep, token);
		token = strtok(NULL, deliminator);
		//printf("token is %s\n", token);
		strcpy(salerecs[i].item, token);
		token = strtok(NULL, deliminator);
		//printf("token is %s\n", token);
		salerecs[i].units = atoi(token);
		token = strtok(NULL, deliminator);
		//printf("token is %s\n", token);
		salerecs[i].unitCost = atof(token);
		token = strtok(NULL, deliminator);
		salerecs[i].total = atof(token);
		//salerecs[i].total = fixtotal(token);
		//printf("token is %s\n", token);
		token = strtok(NULL, deliminator);
		i++;
	}
	fclose(fptr);
	printf("Press 1 to search by region\nPress 2 to search by Sales Rep\nPress 3 to search by item\nPress 4 to search by year\nPress 5 to quit\n");
	int choice = 0;
	fflush(stdin);
	scanf("%d", &choice);
	while (choice !=5)
	{ 
		switch (choice)
		{
		case 1:
			printf("Enter the region you want to find the total for)\n");
			int j = 0;
			float totalSales = 0;
			char region[10];
			fflush(stdin);
			gets(region);
			_strlwr(region);
			for (; j < i; j++)
			{
				if (strcmp(region, _strlwr(salerecs[j].region))== 0) totalSales = totalSales + salerecs[j].total;
				//printf("%f\n", salerecs[j].total);
			}
			if (totalSales == 0 ) printf("This region is not referenced in the text file.\n");
			else printf("The total sales in the %s region were %.2f\n", region, totalSales);
			break;

		case 2:
			totalSales = 0;// resets to be able to use again
			j = 0;// resets counter to use it again
			char salesrep[10];
			printf("Enter the Sales Rep you want to find the total for\n");
			fflush(stdin);
			gets(salesrep);
			_strlwr(salesrep);
			for (; j < i; j++)
			{
				if (strcmp(salesrep, _strlwr(salerecs[j].rep)) == 0) totalSales = totalSales + salerecs[j].total;
			}
			if (totalSales == 0) printf("This Sales rep is not referenced in the text file.\n");
			else printf("The total sales by %s %.2f\n", salesrep, totalSales);
			break;

		case 3:
			totalSales = 0;// resets to be able to use again
			j = 0;// resets counter to use it again
			char item[10];
			printf("Enter the item you want to find the total for\n");
			fflush(stdin);
			gets(item);
			_strlwr(item);
			for (; j < i; j++)
			{
				if (strcmp(item, _strlwr(salerecs[j].item)) == 0) totalSales = totalSales + salerecs[j].total;
			}
			if (totalSales == 0) printf("This item is not referenced in the text file.\n");
			else printf("The total sales of %s is %.2f\n", item, totalSales);
			break;

		case 4:
			totalSales = 0;// resets to be able to use again
			j = 0;// resets counter to use it again
			int day = 0;
			int month = 0;
			int year = 0;
			int targetyear = 15;
			char waste1;
			char waste2;
			printf("Enter the last two digits of the year you want to find the total for. eg 15 for 2015\n");
			scanf("%d", &targetyear);
			for (; j < i; j++)
			{
				sscanf(salerecs[j].date, "%d%c%d%c%d", &day, &waste1, &month, &waste2, &year);
				if (year == targetyear) totalSales = totalSales + salerecs[j].total;
			}
			if (totalSales == 0) printf("This year is not referenced in the text file.\n");
			else printf("The total sales in 20%d is %.2f\n", targetyear, totalSales);
			break;

		case 5:
			break;
		default:
			printf("Input not an option! Try again!");
		}
		printf("Press 1 to search by region\nPress 2 to search by Sales Rep\nPress 3 to search by item\nPress 4 to search by year\nPress 5 to quit\n");
		fflush(stdin);
		scanf("%d", &choice);
	}
}


FILE * openFile(char *fileName, char *mode)
{
	FILE *fptr = fopen(fileName, mode);
	if (fptr == NULL)
	{
		printf("Error opening file ! \n");
	}
	else{
		printf("successfully opened file\n");
	}
	return fptr;
}