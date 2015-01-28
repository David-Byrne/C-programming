//Week 14 programming lab by David Byrne. 20/01/15

#include "stdafx.h"
#include <stdio.h>
#include "string.h"

FILE *openFile(char *fileName, char *mode);

void main()
{
	char vehtype[12], vehreg[12];
	char monthvalue;
	char montharray[12][20] = { "January", "February", "March", "April", "May", "June", "July",
		 "August","September", "October", "November", "December" };
	int i = 0;
	FILE *fptr;
	fptr = openFile("C:/Users/David/Desktop/MaintenanceSchedule.txt", "r");
	char fileline[1000];
	fgets(fileline , 1000, fptr);
	fgets(fileline, 1000, fptr);
	while (!feof(fptr))
	{
		fscanf(fptr, "%s\t%s\t", vehtype, vehreg);
		if (strcmp(vehtype, "END") == 0) break;
		for (i = 0; i < 12; i++)
		{
			fscanf(fptr, "%c\t",&monthvalue);
			if (monthvalue == 'S')
			{
				printf("%s with reg %s needs a SERVICE in %s\n", vehtype, vehreg, montharray[i]);
			}
			else if (monthvalue == 'I')
			{
				printf("%s with reg %s needs an INSPECTION in %s\n", vehtype, vehreg, montharray[i]);
			}
			else if (monthvalue == 'C')
			{
				printf("%s with reg %s needs a COMMERCIAL VEHICLE TEST in %s\n", vehtype, vehreg, montharray[i]);
			}
			else if (monthvalue == 'T')
			{
				printf("%s with reg %s needs a TWO YEAR TACHOO CHECK in %s\n", vehtype, vehreg, montharray[i]);
			}
			else {}
		}
	}
	fclose(fptr);
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
