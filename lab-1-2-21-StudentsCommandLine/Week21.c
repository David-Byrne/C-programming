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

void main(int argc, char *argv[])
{
	ns = 0;
	int write = 1;
	char loc[20];
	if (argc == 5)
	{
		write = 0;
		//loc[20] = "";
	}
	readResults("C:\\Users\\David\\Desktop\\results.txt");
	char *firstName, *lastName;
	char *start, *end;
	char *inPath, *outPath = NULL;
	int toFile = 0;
	int ret;

	/*
	insert your code here to read in the command line arguments
	and call the correct functions
	*/
	if (strcmp(argv[2], "/s") == 0)
	{
		writeSingle(argv[3], argv[4], write, argv[6]);
	}
	else if (strcmp(argv[2], "/r") == 0)
	{
		writeRange(argv[3], argv[4], write, argv[6]);
	}
	else printf("%s", argv[2]);
}

/* this function reads the data file and populates the array of student data structures */
int readResults(char *inPath)
{
	char temp[200];
	FILE *fptr;
	fptr = fopen(inPath, "r");

	if (fptr == NULL)
	{
		printf("Error in readResults opening data file: %s \n", inPath);
		return 0;
	}

	fgets(temp, 200, fptr);
	fscanf(fptr, "%d %s %s %c %c %c %c", &students[ns].ID, students[ns].firstName, students[ns].lastName, &students[ns].english,
		&students[ns].maths, &students[ns].french, &students[ns].philosophy);

	while (!feof(fptr))
	{
		ns++;
		fscanf(fptr, "%d %s %s %c %c %c %c", &students[ns].ID, students[ns].firstName, students[ns].lastName, &students[ns].english,
			&students[ns].maths, &students[ns].french, &students[ns].philosophy);
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
	FILE *fptr = NULL;
	if (toFile == 1) fptr = fopen(outPath, "w");
	int i = 0;
	for (; i < ns; i++)
	{
		if (strcmp(students[i].lastName, start) >= 0)
		{
			
			if (toFile == 0) printf("%d %s %s %c %c %c %c\n", students[i].ID, students[i].firstName, students[i].lastName, students[i].english,
				students[i].maths, students[i].french, students[i].philosophy);
			else fprintf(fptr, "%d %s %s %c %c %c %c\n", students[i].ID, students[i].firstName, students[i].lastName, students[i].english,
				students[i].maths, students[i].french, students[i].philosophy);
			if (strcmp(students[i].lastName, end) >= 0) break;
		}
	}
	if (toFile == 1) fptr = fclose(outPath);
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
	FILE *fptr = NULL;
	
	int i = 0;
	
	if (toFile == 1) fptr = fopen(outPath, "w");
	for (; i < ns; i++)
	{
		if ((strcmp(students[i].firstName, firstName) == 0) && strcmp(students[i].lastName, lastName) == 0)
		{
			if (toFile == 0) printf("%d %s %s %c %c %c %c\n", students[i].ID, students[i].firstName, students[i].lastName, students[i].english,
				students[i].maths, students[i].french, students[i].philosophy);
			else fprintf(fptr, "%d %s %s %c %c %c %c\n", students[i].ID, students[i].firstName, students[i].lastName, students[i].english,
				students[i].maths, students[i].french, students[i].philosophy);
		}
	}
	if (toFile == 1) fptr = fclose(outPath);
	return 1;
}