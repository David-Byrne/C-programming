#include "stdafx.h"
#include <stdio.h>
#include "string.h"

int readResults(char *inPath);
int writeRange(char *start, char *end, int toFile, char *outPath);
int writeSingle(char *firstName, char *lastName, int toFile, char *outPath);

typedef struct
{
	int ID;
	char firstName[25];
	char lastName[25];
	char english, french, maths, philosophy;
} student;

student students[100];
int ns;

void main( int argc, char *argv[] )
{ 
	char *firstName, *lastName;
	char *start, *end;
	char *inPath, *outPath = NULL;
	int toFile = 0;
	ns = 0;
	int ret;

	/* 
	insert your code here to read in the command line arguments
	and call the correct functions
	*/
} 

/* this function reads the data file and populates the array of student data structures */
int readResults(char *inPath)
{
	char temp[200];
	FILE *fptr;
	fptr = fopen(inPath, "r");

	if (fptr == NULL)
	{
		printf ("Error in readResults opening data file: %s \n", inPath);
		return 0;
	}

	fgets(temp,200, fptr);
	fscanf(fptr,"%d %s %s %c %c %c %c", &students[ns].ID,students[ns].firstName, students[ns].lastName,&students[ns].english,
		&students[ns].maths, &students[ns].french,&students[ns].philosophy);

	while (!feof(fptr))
	{
		ns++;
		fscanf(fptr,"%d %s %s %c %c %c %c", &students[ns].ID,students[ns].firstName, students[ns].lastName,&students[ns].english,
			&students[ns].maths, &students[ns].french,&students[ns].philosophy);
	}
	fclose(fptr);
	return 1;

}
/*
this function prints out the results for students in the range start-end
if toFile is false then the results are written to the stdout
if tofile is true then the results are written to the file specified by outPath
*/
int writeRange(char *start, char *end, int toFile, char *outPath)
{
/*
insert your code here for this function
*/

	return 1;
}

/*
this function prints out the results for a students with
the given firstName and lastName
if toFile is false then the results are written to the stdout
if tofile is true then the results are written to the file specified by outPath
*/
int writeSingle(char *firstName, char *lastName, int toFile, char *outPath)
{
/*
insert your code here for this function
*/
	return 1;
}