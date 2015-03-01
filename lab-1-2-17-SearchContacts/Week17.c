//Lab week 17 by David Byrne, 10/02/15. 
#include "stdafx.h"
#include <stdio.h>
#include "string.h"
#include "stdlib.h"

struct contact
{
	char firstName[50];
	char lastName[50];
	char companyName[50];
	char address[50];
	char city[50];
	char county[50];
	char state[50];
	char zip[50];
	char phone1[50];
	char phone2[50];
	char email[50];
	char web[50];
};

int numContacts = 0;
struct contact *contacts;
int readFile(char *fileName);
int findContact(char *string);
int findCompany(char *string);
int findCity(char *string);
int findCounty(char *string);
int findState(char *string);
int findZip(char *string);
void printContact(struct contact *theContact);
int countLines(char *fileName);

void main()
{
	char string[20];
	char fileName[] = "C:/Users/David/Desktop/us-500b.txt";
	int i = 0;
	int option;

	numContacts = countLines(fileName);

	contacts = (struct contact *)malloc(numContacts*sizeof(struct contact));


	if (!readFile(fileName))
	{
		printf("File could not be opened !!\n");
		return;
	}
	puts("Options:\n1-search by name\n2-search by company\n3-search by city\n4-search by county\n5-search by state\n6-search by zip\n");
	fflush(stdin);
	scanf("%d", &option);

	puts("Enter all \(or part\) of what you are looking for:");
	fflush(stdin);
	gets(string);

	switch (option)
	{
	case 1:
		findContact(string);
		break;
	case 2:
		// write and use a function to find by company
		findCompany(string);
		break;
	case 3:
		// write and use a function to find by city
		findCity(string);
		break;
	case 4:
		// write and use a function to find by county
		findCounty(string);
		break;
	case 5:
		// write and use a function to find by state
		findState(string);
		break;
	case 6:
		// write and use a function to find by zip
		findZip(string);
		break;
	default:
		break;
	}
	free(contacts);// Changed this part to free the memory after we are finished with it. DB
}

int findContact(char *string)
{
	int i = 0, j = -1;
	char firstNameTemp[50], secondNameTemp[50];

	// insert code to find a string in either the first name or surname
	// you should use strstr()
	// your solution should be case INSENSITIVE
	_strlwr(string);
	for (i = 0; i < numContacts; i++)
	{
		strcpy(firstNameTemp, contacts[i].firstName);
		_strlwr(firstNameTemp);
		strcpy(secondNameTemp, contacts[i].lastName);
		_strlwr(secondNameTemp);
		if (strstr(firstNameTemp, string) != NULL || strstr(secondNameTemp, string) != NULL)
		{
			j = i;
			//printf("First Name: %s\nLast Name: %s\n", contacts[j].firstName, contacts[j].lastName);
			printContact(contacts + j);
		}
	}
	if (j == -1) printf("Not found\n");
	return j;
}

int findCompany(char *string)
{
	int i = 0, j = -1;
	char companyNameTemp[50];
	_strlwr(string);
	for (i = 0; i < numContacts; i++)
	{
		strcpy(companyNameTemp, contacts[i].companyName);
		_strlwr(companyNameTemp);
		if (strstr(companyNameTemp, string) != NULL)
		{
			j = i;
			printContact(contacts + j);
		}
	}
	if (j == -1) printf("Not found\n");
	return j;
}

int findCity(char *string)
{
	int i = 0, j = -1;
	char cityNameTemp[50];
	_strlwr(string);
	for (i = 0; i < numContacts; i++)
	{
		strcpy(cityNameTemp, contacts[i].city);
		_strlwr(cityNameTemp);
		if (strstr(cityNameTemp, string) != NULL)
		{
			j = i;
			printContact(contacts + j);
		}
	}
	if (j == -1) printf("Not found\n");
	return j;
}

int findCounty(char *string)
{
	int i = 0, j = -1;
	char countyNameTemp[50];
	_strlwr(string);
	for (i = 0; i < numContacts; i++)
	{
		strcpy(countyNameTemp, contacts[i].county);
		_strlwr(countyNameTemp);
		if (strstr(countyNameTemp, string) != NULL)
		{
			j = i;
			printContact(contacts + j);
		}
	}
	if (j == -1) printf("Not found\n");
	return j;
}

int findState(char *string)
{
	int i = 0, j = -1;
	char stateNameTemp[50];
	_strlwr(string);
	for (i = 0; i < numContacts; i++)
	{
		strcpy(stateNameTemp, contacts[i].state);
		_strlwr(stateNameTemp);
		if (strstr(stateNameTemp, string) != NULL)
		{
			j = i;
			printContact(contacts + j);
		}
	}
	if (j == -1) printf("Not found\n");
	return j;
}

int findZip(char *string)
{
	int i = 0, j = -1;
	char zipNameTemp[50];
	_strlwr(string);
	for (i = 0; i < numContacts; i++)
	{
		strcpy(zipNameTemp, contacts[i].zip);
		_strlwr(zipNameTemp);
		if (strstr(zipNameTemp, string) != NULL)
		{
			j = i;
			printContact(contacts + j);
		}
	}
	if (j == -1) printf("Not found\n");
	return j;
}


void printContact(struct contact *theContact)
{
	printf("First name: \t%s\n", theContact->firstName);
	printf("Last name: \t%s\n", theContact->lastName );
	printf("Company name: \t%s\n", theContact->companyName);
	printf("Address: \t%s\n", theContact->address);
	printf("City: \t\t%s\n", theContact->city);
	printf("County: \t%s\n", theContact->county);
	printf("State: \t\t%s\n", theContact->state);
	printf("Zip: \t\t%s\n", theContact->zip);
	printf("Phone #1: \t%s\n", theContact->phone1);
	printf("Phone #2: \t%s\n", theContact->phone2);
	printf("Email: \t\t%s\n", theContact->email);
	printf("Web: \t\t%s\n", theContact->web);
}

int countLines(char *fileName)
{
	char line[200];
	FILE *fptr = fopen(fileName, "r");
	int nLines = 0;

	if (fptr == NULL)
	{
		printf("Error opening file ! \n");
		return 0;
	}

	// use fgets to skip first line
	fgets(line, 200, fptr);
	fgets(line, 200, fptr);
	while (!feof(fptr))
	{
		nLines++;
		fgets(line, 200, fptr);
	}

	fclose(fptr);

	return nLines;
}

int readFile(char *fileName)
{
	char line[200];
	FILE *fptr = fopen(fileName, "r");
	char *token;
	char delim[6] = ",";
	int n = 0, i = 0;

	if (fptr == NULL)
	{
		printf("Error opening file ! \n");
		return 0;
	}

	// use fgets to skip first line
	fgets(line, 200, fptr);

	//first data line
	fgets(line, 200, fptr);
	while (!feof(fptr))
	{
		if ((token = strtok(line, delim)) != NULL) strcpy((contacts + n)->firstName, token);
		if ((token = strtok(NULL, delim)) != NULL) strcpy((contacts + n)->lastName, token);
		if ((token = strtok(NULL, delim)) != NULL) strcpy((contacts + n)->companyName, token);
		if ((token = strtok(NULL, delim)) != NULL) strcpy((contacts + n)->address, token);
		if ((token = strtok(NULL, delim)) != NULL) strcpy((contacts + n)->city, token);
		if ((token = strtok(NULL, delim)) != NULL) strcpy((contacts + n)->county, token);
		if ((token = strtok(NULL, delim)) != NULL) strcpy((contacts + n)->state, token);
		if ((token = strtok(NULL, delim)) != NULL) strcpy((contacts + n)->zip, token);
		if ((token = strtok(NULL, delim)) != NULL) strcpy((contacts + n)->phone1, token);
		if ((token = strtok(NULL, delim)) != NULL) strcpy((contacts + n)->phone2, token);
		if ((token = strtok(NULL, delim)) != NULL) strcpy((contacts + n)->email, token);
		if ((token = strtok(NULL, delim)) != NULL) strcpy((contacts + n)->web, token);
		//printContact((contacts+n));
		n++;
		//next data line
		fgets(line, 200, fptr);

	}

	fclose(fptr);

	return 1;
}

