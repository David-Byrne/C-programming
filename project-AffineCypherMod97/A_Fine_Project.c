//Affine programme by David Byrne
//Designed to discourage casual snooping rather than to withstand serious attention from Eve.
//Mod 97 is used as there are 95 easily typeable ascii characters but a prime mod is best (see below re. higher phi)
//The other two symbols are '30' and '31', triangle up and triangle down respectively.

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "math.h"
#include "string.h"

int alphaInverter(int aplha);
void txtencrypter();
void txtdecrypter();

int ALPHA = 3;
int BETA = 5;
int ALPHIN = 65;

void main()
{
	int ans = 1;
	printf("Welcome to the Affine converter program!\n");
	printf("Press 1 to encrypt, 2 to decrypt, 3 to find Alpha's inverse and 0 to quit.\n");
	fflush(stdin);
	scanf_s("%d", &ans);
	while (ans != 0)
	{
		if (ans == 1)
		{
			txtencrypter();
			printf("Press 1 to encrypt, 2 to decrypt, 3 to find Alpha's inverse and 0 to quit.\n");
			fflush(stdin);
			scanf_s("%d", &ans);
		}
	
		else if (ans == 2)
		{
			txtdecrypter();
			printf("Press 1 to encrypt, 2 to decrypt, 3 to find Alpha's inverse and 0 to quit.\n");
			fflush(stdin);
			scanf_s("%d", &ans);
		}
		else if (ans == 3)
		{
			int ALPHA = 0, ALPHIN = 0;
			scanf_s("%d", &ALPHA);
			ALPHIN = alphaInverter(ALPHA);
			printf("Inverse is %d", ALPHIN);

		}
		else
		{
			printf("Invalid Option\n");
			printf("Press 1 to encrypt, 2 to decrypt, 3 to find Alpha's inverse and 0 to quit.\n");
			fflush(stdin);
			scanf_s("%d", &ans);
		}
	}
}

void txtencrypter()
{
	char string[1000];
	int len = 0, i = 0;
	fflush(stdin);
	printf("Please enter the string you want to encrypt and then press the enter key.\n");
	gets_s(string);
	printf("You entered: %s \n", string);
	len = strlen(string);
	for (i = 0; i < len; i++)
	{
		if (string[i] > 29)
		{
			string[i] = string[i] - 30;//moves ascii down to space = 0, ! = 1...
			string[i] = ((ALPHA * string[i]) + BETA) % 97;
			//127 - 30 = 97 which is prime
			//the phi(m) of a prime number is the number of invertable elements mod m ie the number of possible aplha for which alpha
			//	has an inverse as aplha must be co-prime to m. This is needed for a decryption function
			//We make m = 97 to increase the number of possible aplha to 96
			string[i] = string[i] + 30;
		}
	}
	printf("\nThis is converted to:\n%s\n\n", string);
}

void txtdecrypter()
{
	char string[1000];
	int len = 0, i = 0;
	fflush(stdin);
	printf("Please enter the string you want to decrypt and then press the enter key.\n");
	gets_s(string);
	printf("You entered: %s \n", string);
	len = strlen(string);
	for (i = 0; i < len; i++)
	{
		if (string[i] > 29)
		{
			string[i] = string[i] - 30;//moves ascii down to space = 0, ! = 1...
			string[i] = ((string[i] - BETA) * ALPHIN) % 97;
			//127 - 30 = 97 which is prime
			//the phi(m) of a prime number is the number of invertable elements mod m ie the number of possible aplha for which alpha
			//	has an inverse as aplha must be co-prime to m. This is needed for a decryption function
			//We make m = 97 to increase the number of possible aplha to 96
			string[i] = (string[i] + 97) % 97;
			//(-3)%97 gives -3 but we need a positive char. number so we add 97 mod 97 to ensure it's between 0 and 96 incl.
			string[i] = string[i] + 30;
		}
	}
	printf("\nThis is decrypted to:\n%s\n\n", string);
}

int alphaInverter(int alpha)
{
	int i = 0; 
	int flag = 0;
	for (i = 0; i < 97; i++)
	{
		if ((alpha*i) % 97 == 1)
		{
			return i;
		}
	}
	printf("No inverse found\n");
	return 0;
}