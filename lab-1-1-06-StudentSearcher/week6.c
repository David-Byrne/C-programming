//Lab week 6 by David Byrne
#include "stdafx.h"
#include <stdio.h>
#include <string.h>

void main()
{
	int ID[10] = { 101, 102, 103, 104, 105, 106, 107, 108, 109, 110 };
	int mark[10] = { 45, 67, 23, 91, 40, 50, 60, 70, 80, 99 };
	char surname[10][20] = { "Holmes", "Gates", "Byrne", "Hernan", "Zenkevich", "Nolan", "Egan", "Brian", "Arran", "Fin" };
	char attsname[20];
	int studid = 101;
	int search = 0;
	char choose = 'I';
	int cntr = 0;
	while (choose != 'Q' || choose != 'q')
	{
		if (choose == 'I' || choose == 'i')
		{
			printf("If you would like to Search by ID, press 1. \nIf you would like to search by Surname, press 2.\n");
			scanf_s("%d", &search);
			if (search == 1)
			{
				printf("Enter the student's ID\n");
				scanf_s("%d", &studid);
				for (cntr = 0; cntr < 10; cntr++)
				{
					if (studid == ID[cntr])
					{
						printf("%d \n", mark[cntr]);
						break;
					}
					if (cntr == 9) printf("Invalid ID\n");
				}
			}
			else if (search == 2)
			{
				printf("What is the surname?\n");
				scanf_s("%s", attsname, 20);
				printf("You typed %s\n", attsname);


				for (cntr = 0; cntr < 10; cntr++)
				{
					if (strcmp(attsname, surname[cntr]) == 0)
					{
						printf("%d \n", mark[cntr]);
						break;
					}

					if (cntr == 9) printf("Invalid name\n");
				}
			}
			else
			{
				printf("You entered an invalid option!!!\n");
			}
			printf("Would you like to search again? Press I to search or press Q to quit\n");
			fflush(stdin);
			choose = getchar();
		}
		else if (choose == 'Q' || choose == 'q')
		{
			break;
		}
		else
		{
			printf("Invalid Input! Press I to search or press Q to quit\n");
			fflush(stdin);
			choose = getchar();
		}
	}
}