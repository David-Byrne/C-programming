//Lab week 4 by David Byrne

#include "stdafx.h"
#include "stdio.h"

void main()
{
	int cust = 1, item = 0;
	while (cust == 1)
	{
		double price = 0, product = 0, sum = 0;
		int quantity = 0;
		do
		{
			printf("What is the price of the item? \n");
			scanf_s("%lf", &price);
			printf("How many of this item are there? \n");
			scanf_s("%d", &quantity);
			product = price*quantity;
			sum = product + sum;
			printf("Is there another item? press 1 for yes and 0 for no \n");
			scanf_s("%d", &item);
		} while (item != 0);
		printf("\t Bill is %.2lf\n\n\n", sum);
		printf("Is there another customer? Press 1 for yes or press 0 for no\n");
		scanf_s("%d", &cust);
	}
}


