#include "stdio.h"
#include "accounts.h"
#include "math.h"
#include "stdlib.h"

// sets up the array of accounts with random balances and account numbers
void setupAccounts(struct account accounts[], int num)
{
	int i = 0;
	for (i = 0; i < num; i++)
	{
		accounts[i].num = i + 1;
		accounts[i].balance = rand() %10000;
		accounts[i].interest = 0;
		accounts[i].tax = 0;
	}
}

// uses calcInterest and calcTax to calculate the interest and tax, and update the account balances
void updateAccounts(struct account accounts[], int num)
{
	int i = 0;
	for (i = 0; i < num; i++)
	{
		accounts[i].interest = calcInterest(accounts[i].balance);
		accounts[i].tax = calcTax(accounts[i].interest);
		accounts[i].balance = accounts[i].balance + accounts[i].interest - accounts[i].tax;

	}
}

// calculates the interest on the balance, using the interest rate defined in accounts.h
double calcInterest(double balance)
{
	return balance * interestRate;
}

// calculates the tax on the interest, using the tax rate defined in accounts.h
double calcTax(double interest)
{
	return interest*taxRate;
}

// uses printAccount to print out an array of accounts
void printAccounts(struct account accounts[], int num)
{
	int i = 0;
	for (i = 0; i < num; i++)
	{
		printAccount(accounts[i]);
	}
	
}
// prints an individual account
void printAccount(struct account anAccount)
{
	printf("Account #: %5d \n", anAccount.num);
	printf("Balance: %10.2lf \n", anAccount.balance);
	printf("Interest: %9.2lf \n", anAccount.interest);
	printf("Tax: %14.2lf \n\n\n", anAccount.tax);
}