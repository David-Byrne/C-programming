#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	int year;
	char county[3];
	int number;
} registration;

typedef struct
{
	char make[40];
	char model[40];
	int year;
	double price;
	registration reg;
	int sold;  // 0 = for sale; 1 = sold
} car;

// this function is already written
int printMenu();

// complete the code in these functions
int addCar(car stock[], int num, car newCar);
void displayCarsForSale(car stock[], int num);
void displayAllCars(car stock[], int num);
void displayCar(car car1);
void sellCar(car stock[], int num, registration reg);


void main()
{
	car stock[200];
	int numCars = 0;
	int option;
	car newCar; //soldCar;
	registration reg1;

	printf("Welcome to the Universal Car Sales \n");
	printf("------------------------------------\n");

	option = printMenu();
	while (option != 0)
	{
		switch (option)
		{
		case 1:
			// call displayCarsForSale if there are any in stock
			displayCarsForSale(stock, numCars);
			break;

		case 2:
			// get the user to enter the new car data & reg
			printf("Enter Car Make\n");
			fflush(stdin);
			gets(newCar.make);
			printf("Enter Car Model\n");
			fflush(stdin);
			gets(newCar.model);
			printf("Enter Car Year\n");
			scanf("%d", &newCar.year);
			printf("Enter Car Price\n");
			scanf("%lf", &newCar.price);
			printf("Enter Car Reg with spaces between the catagories (eg 07 G 12345)\n");
			scanf("%d %s %d", &newCar.reg.year, newCar.reg.county, &newCar.reg.number);
			newCar.sold = 0;
			numCars = addCar(stock, numCars, newCar);
			// use newCar to hold the data
			// call addCar (stock, numCars, newCar)
			// addCar returns the new number of cars (numCars+1)
			break;

		case 3:
			// get the user to enter the reg that is sold
			printf("Enter the sold Car's Reg with spaces between the catagories (eg 07 G 12345)\n");
			scanf("%d %s %d", &reg1.year, reg1.county, &reg1.number);
			// call sellCar(stock, numCars, reg1);
			sellCar(stock, numCars, reg1);
			// it sets  'sold' to 0 for this car
			break;

		case 4:
			// call displayAllCars if there are any in stock
			displayAllCars(stock, numCars);
			break;

		default:
			puts("Illegal Option!\n");
		}
		
		//scanf("%d", option);
		option = printMenu();
	}

}

int printMenu()
{
	int option = 0;
	printf("\n1 - Display Stock for Sale\n");
	printf("2 - Add Car \n");
	printf("3 - Sell Car \n");
	printf("4 - Display All Stock \n");
	printf("0 - Exit\n");
	printf("------------------------------------\n");
	printf("Choose your option:\n");
	scanf("%d", &option);
	printf("------------------------------------\n");
	return option;

}

int addCar(car stock[], int num, car newCar)
{
	
	*(stock + num) = newCar;
	return (num + 1);
}




void displayCar(car car1)
{
	// print out the details for a car, including the reg
	printf("The make is:%20s\n", car1.make);
	printf("The model is:%19s\n", car1.model);
	printf("The Car's year is:%14d\n", car1.year);
	printf("The Car's price is:%13.2lf\n", car1.price);
	printf("The Car's reg is:%7d %s %d\n", car1.reg.year, car1.reg.county, car1.reg.number);
	printf("This Car is: ");
	if (car1.sold == 0) printf("           FOR SALE\n");
	else printf("             -SOLD-\n");

}

void displayCarsForSale(car stock[], int num)
{
	int i, check = 0;
	// call displayCar for cars with 'sold' = 0
	for (i = 0; i < num; i++)
	{
		if (stock[i].sold == 0)
		{
			displayCar(stock[i]);
			printf("------------------------------------\n");
			check = 1;
		}
	}
	//printf("------------------------------------\n");
	if (check == 0) printf("There aren't any cars for sale...\n");

}

void displayAllCars(car stock[], int num)
{
	int i;
	for (i = 0; i < num; i++)
	{

		displayCar(stock[i]);
		printf("------------------------------------\n");

	}
	if (num == 0)printf("There aren't any cars...\n");
	// call displayCar for all cars
}

void sellCar(car stock[], int num, registration reg)
{
	int i;
	int flag = 0;
	for (i = 0; i < num; i++)
	{
		if (strcmp(reg.county, stock[i].reg.county) == 0 && reg.number == stock[i].reg.number && reg.year == stock[i].reg.year)
		{
			stock[i].sold = 1;
			printf("That Car has now been sold!\n");
			flag = 1;
			break;
		}
		if (i == num) printf("Car not Found\n");
	}
	if (i == 0 && flag == 0) printf("Car not Found\n");
	

	// set sold=0 for the car with this reg
	// print "Car Not Found\n" if it is not in stock
}