#include "stdio.h"
#include "stdafx.h"
#include "string.h"
#include "ctype.h"

#define IMPERIAL 1
#define METRIC 2
#define QUIT 3

float feetAndInchesToMetres(int feet, int inches);
float squareFeet(float aream);
float squareMetres(float width, float length);

void main()
{
	int choice, i1, i2, i3, i4, i5, i6, i7;
	float lm = 0, wm = 0, aream = 0, areai = 0, f1 = 0, f2 = 0;
	char c1, c2, c3, c4, c5, c6;
	char dimens[81];
	printf("Enter 1 for Imperial Units,2 for Metric units or 3 to Quit\n");
	scanf_s("%d",&choice);
	while (choice != 3)
	{ 
		switch (choice)
		{
		case IMPERIAL:
			printf("Enter the Dimensions like: 5'4\"x3'6\"\n");
			fflush(stdin);
			gets_s (dimens,81);
			sscanf_s(dimens,"%d%c%d%c%c%d%c%d%c",&i1,&c1,1,&i2,&c2,1,&c3,1,&i3,&c4,1,&i4,&c5,1);
			lm= feetAndInchesToMetres( i1, i2);
			wm = feetAndInchesToMetres(i3, i4);
			aream = squareMetres(wm, lm);
			areai = squareFeet(aream);
			printf("Area in Metres is %.2f\n", aream);
			printf("Area in Square Foot is %.2f\n", areai);
			break;
		case METRIC:
			printf("Enter the Dimensions like: 3.152x12.01\n");
			fflush(stdin);
			gets_s(dimens, 81);
			sscanf_s(dimens, "%f%c%f", &f1, &c1, 1, &f2);
			aream = squareMetres(f1, f2);
			printf("Area in Square Metres  is %f\n", aream);
			break;
		default:
			printf("Incorrect Input Choice!\n");
			break;
		}
		printf("\nCalculate again?\n");
		printf("Enter 1 for Imperial Units,2 for Metric units or 3 to Quit\n");
		scanf_s("%d", &choice);
	}
	
}

float feetAndInchesToMetres(int i1, int i2)
{
	float feet = (float)i1*0.3048;
	float inches = (float)i2*0.0254;

	return feet+inches;
}

float squareMetres(float wm, float lm)
{
	return wm*lm;
}

float squareFeet(float aream )
{
	return aream*10.7639;
}