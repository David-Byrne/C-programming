#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
#define SIZE 10
char custName[SIZE][30]; // array of customer names
float custBal[SIZE]; // array of customer balances
void initArrays(); // use any method you think useful to put sample data in the customer name and balance arrays
void printCustomer(int i); // prints the name and balance of customer[i]
int findHighest(); // finds the index of the customer with the highest balance
int findLowest(); // finds the index of the customer with the lowest balance
float findAverage(); // finds the average of all customer balances
void main()
{
	int i;
	float avg;
	initArrays();
	i = findHighest();
	printCustomer(i);
	i = findLowest();
	printCustomer(i);
	avg = findAverage();
	printf("\nAverage Balance = %.2f \n\n", avg);
}

void initArrays()
{
	int i = 0;
	for (i = 0; i < SIZE; i++)
	{
		
		sprintf(custName[i], "Customer%d", i);
		custBal[i] = rand()%1000;
	}
}

void printCustomer(i)
{

	printf("%s's", custName[i]);
	printf(" balance is %.2f\n", custBal[i]);
}

int findHighest()
{
	int max = 0, i, location = 0;
	for (i = 0; i < SIZE; i++)
	{
		if (max < custBal[i])
		{	
				max = custBal[i];
				location = i;
		}
	}
	
	return location;
}

int findLowest()
{
	int min = 33000, i, location = 0;
	for (i = 0; i < SIZE; i++)
	{
		if (min > custBal[i])
		{
			min = custBal[i];
			location = i;
		}
	}
	
	return location;
}

float findAverage()
{
	float total=0,mean=0;
	int i;
	for (i = 0; i < SIZE; i++)
	{
		total = total + custBal[i];
	}
	mean = total / SIZE;
	return mean;
}