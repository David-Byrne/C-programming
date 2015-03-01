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
} ;

int numContacts = 0;
struct contact *contacts;  
int readFile(char *fileName);
int findContact(char *string);
void printContact(struct contact *theContact);
int countLines(char *fileName);

void main()
{
	char string[20];
	char fileName[] = "C:\\us-500b.txt";
	int i=0;
	int option;

	numContacts = countLines(fileName);

	contacts = (struct contact *)malloc(numContacts*sizeof(struct contact));


	if (!readFile(fileName)) 
	{
		printf( "File could not be opened !!\n" );
		return;
	} 
	puts("Options:\n1-search by name\n2-search by company\n3-search by sity\n4-search by county\n5-search by state\n6-search by zip\n");
	fflush(stdin);
	scanf("%d",&option);

	puts("Enter all \(or part\) of what you are looking for:");
	fflush(stdin);
	gets(string);
	
	switch(option)
	{
		case 1:
			findContact(string);
			break;
		case 2:
			// write and use a function to find by company
			break;
		case 3:
			// write and use a function to find by city
			break;
		case 4:
			// write and use a function to find by county
			break;
		case 5:
			// write and use a function to find by state
			break;
		case 6:
			// write and use a function to find by zip
			break;
		default:
			break;
	}

	
}

int findContact(char *string)
{
	int i,j=0;

	// insert code to find a string in either the first name or surname
	// you should use strstr()
	// your solution should be case INSENSITIVE

	return j;
}

void printContact(struct contact *theContact)
{
	// insert code to print out the contact

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
	fgets (line, 200, fptr);
	fgets (line,200,fptr);
	while (!feof(fptr))
	{ 
		nLines++;
		fgets (line,200,fptr);
	}

	fclose (fptr);

	return nLines;
}

int readFile(char *fileName)
{
	char line[200];
	FILE *fptr = fopen(fileName, "r");
	char *token;
	char delim[6]=",";  
	int n=0,i=0;

	if (fptr == NULL)
	{
		printf("Error opening file ! \n");
		return 0;
	}

	// use fgets to skip first line
	fgets (line, 200, fptr);

	//first data line
	fgets (line,200,fptr);
	while (!feof(fptr))
	{ 
		if ((token = strtok (line,delim)) != NULL) strcpy((contacts+n)->firstName,token);
		if ((token = strtok (NULL,delim)) != NULL) strcpy((contacts+n)->lastName,token);
		if ((token = strtok (NULL,delim)) != NULL) strcpy((contacts+n)->companyName,token);
		if ((token = strtok (NULL,delim)) != NULL) strcpy((contacts+n)->address,token);
		if ((token = strtok (NULL,delim)) != NULL) strcpy((contacts+n)->city,token);
		if ((token = strtok (NULL,delim)) != NULL) strcpy((contacts+n)->county,token);
		if ((token = strtok (NULL,delim)) != NULL) strcpy((contacts+n)->state,token);
		if ((token = strtok (NULL,delim)) != NULL) strcpy((contacts+n)->zip,token);
		if ((token = strtok (NULL,delim)) != NULL) strcpy((contacts+n)->phone1,token);
		if ((token = strtok (NULL,delim)) != NULL) strcpy((contacts+n)->phone2,token);
		if ((token = strtok (NULL,delim)) != NULL) strcpy((contacts+n)->email,token);
		if ((token = strtok (NULL,delim)) != NULL) strcpy((contacts+n)->web,token);
		//printContact((contacts+n));
		n++;
		//next data line
		fgets (line,200,fptr);

	} 
     
	fclose (fptr);

	return 1;
}

