#include "stdio.h"
#include "string.h"

void main()
{
	int cntr;
	int values[30], input = 0, bigno = 0, total = 0, lono = 1000;
	double  mean = 0;
	printf("When finished, input 999 as the value\n");
	for (cntr = 0; cntr < 30; cntr++)
	{
		printf("Input Value # %d:\n", cntr + 1);
		scanf_s("%d", &input);
		if (input != 999)
		{
			values[cntr] = input;
			lono = values[0];
			bigno = values[0];
			if (input > bigno) bigno = input;
			if (input < lono) lono = input;
			total = total + input;

		}
		else break;
	}

	mean = (double)total / (double)cntr; //finds mean while converting to double so to store the 2 decimal places
	printf("--------------------------------------------------------------------------------\n");
	printf("\t\t Average Value is %.2lf \n", mean);
	printf("\t\t Highest Value is %d \n", bigno);
	printf("\t\t Lowest Value is %d \n\n", lono);
	printf("--------------------------------------------------------------------------------\n");

	for (cntr = cntr; cntr >0; cntr--)
		printf("Value # %d is %d \n", cntr, values[cntr - 1]);

}

