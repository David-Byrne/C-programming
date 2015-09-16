#include <stdio.h>


struct book 
{
	char title[20];
	char author[20];
	int year;
	int ISBN;
	float wholesale_price;
	float retail_price;
};

void textFile(FILE *readPtr);
void updateBook(FILE *fPtr);
void deleteBook(FILE *fPtr);
void newBook(FILE *fPtr);

int randomAccess();

int main()
{
	FILE *cfPtr; /* credit.dat file pointer */
	int choice;  /* user's choice */
	randomAccess();

	cfPtr = fopen("C:\\Users\\David\\Desktop\\week19book.dat", "rb+");

		/* enable user to specify action */
	while ((choice = enterChoice()) != 5) {

		switch (choice) {

				/* create text file from record file */
		case 1:
				textFile(cfPtr);
				break;

			/* update record */
		case 2:
			updateBook(cfPtr);
			break;
							/* create record */
		case 3:
			newBook(cfPtr);
			break;

				/* delete existing record */
		case 4:
			deleteBook(cfPtr);
			break;

				/* display message if user does not select valid choice */
		default:
			printf("Incorrect choice\n");
			break;

		} /* end switch */

	} /* end while */
	fclose(cfPtr); /* fclose closes the file */
	return 0; /* indicates successful termination */

} /* end main */

/* create formatted text file for printing */
void textFile(FILE *readPtr)
{
	FILE *writePtr; /* accounts.txt file pointer */

	/* create book with default information */
	struct book abook = { "","",0,0,0,0 };

	/* fopen opens the file; exits if file cannot be opened */
	if ((writePtr = fopen("C:\\Users\\David\\Desktop\\week19book.txt", "w")) == NULL) {
		printf("File could not be opened.\n");
	} /* end if */
	else {
		rewind(readPtr); /* sets pointer to beginning of file */
		fprintf(writePtr, "Title\tAuthor\tISBN\tYear\tWholesale price\tRetail Price\n");

		/* copy all records from random-access file into text file */
		while (!feof(readPtr)) {
			fread(&abook, sizeof(struct book), 1, readPtr);

			/* write single record to text file */
			if (abook.ISBN != 0) {
				fprintf(writePtr, "%s\t%s\t%d\t%d\t%f\t%f\n",
					abook.title, abook.author, abook.ISBN, abook.year, abook.wholesale_price, abook.retail_price);
			} /* end if */

		} /* end while */

		fclose(writePtr); /* fclose closes the file */
	} /* end else */

} /* end function textFile */

/* update balance in record */
void updateBook(FILE *fPtr)
{
	int booknum;        /* account number */
	float newWprice;
	float newRprice;
	//double transaction; /* transaction amount */

	/* create book with no information */
	struct book blankbook = { "", "", 0, 0, 0, 0 };

	/* obtain number of account to update */
	printf("Enter book to update ( 1 - 100 ): ");
	scanf("%d", &booknum);

	/* move file pointer to correct record in file */
	fseek(fPtr, (booknum - 1) * sizeof(struct book),
		SEEK_SET);

	/* read record from file */
	fread(&blankbook, sizeof(struct book), 1, fPtr);

	/* display error if account does not exist */
	if (blankbook.ISBN == 0) {
		printf("book #%d has no information.\n", booknum);
	} /* end if */
	else { /* update record */
		printf("%s %s %d %d %f %f\n",
			blankbook.title, blankbook.author, blankbook.ISBN, blankbook.year, blankbook.wholesale_price, blankbook.retail_price );

		/* request transaction amount from user */

		printf("Enter new retail price ");
		scanf("%f", &newRprice);
		blankbook.retail_price = newRprice; /* update record balance */

		printf("%s %s %d %d %f %f\n",
			blankbook.title, blankbook.author, blankbook.ISBN, blankbook.year, blankbook.wholesale_price, blankbook.retail_price);

		/* move file pointer to correct record in file */
		fseek(fPtr, (booknum - 1) * sizeof(struct book),
			SEEK_SET);

		/* write updated record over old record in file */
		fwrite(&booknum, sizeof(struct book), 1, fPtr);
	} /* end else */

} /* end function updateRecord */

/* delete an existing record */
void deleteBook(FILE *fPtr)
{

	struct book book; /* stores record read from file */
	struct book blankbook = { "", "", 0, 0, 0.0, 0.0 }; /* blank client */

	int accountNum; /* account number */

	/* obtain number of account to delete */
	printf("Enter account number to delete ( 1 - 100 ): ");
	scanf("%d", &accountNum);

	/* move file pointer to correct record in file */
	fseek(fPtr, (accountNum - 1) * sizeof(struct book),
		SEEK_SET);

	/* read record from file */
	fread(&book, sizeof(struct book), 1, fPtr);

	/* display error if record does not exist */
	if (book.ISBN == 0) {
		printf("Account %d does not exist.\n", accountNum);
	} /* end if */
	else { /* delete record */

		/* move file pointer to correct record in file */
		fseek(fPtr, (accountNum - 1) * sizeof(struct book),
			SEEK_SET);

		/* replace existing record with blank record */
		fwrite(&blankbook,
			sizeof(struct book), 1, fPtr);
	} /* end else */

} /* end function deleteRecord */

/* create and insert record */
void newBook(FILE *fPtr)
{
	/* create book with default information */
	struct book book = { "", "", 0, 0, 0.0, 0.0 };

	int bookNum; /* account number */

	/* obtain number of account to create */
	printf("Enter new account number ( 1 - 100 ): ");
	scanf("%d", &bookNum);

	/* move file pointer to correct record in file */
	fseek(fPtr, (bookNum - 1) * sizeof(struct book), SEEK_SET);

	/* read record from file */
	fread(&book, sizeof(struct book), 1, fPtr);

	/* display error if account already exists */
	if (book.ISBN != 0) {
		printf("Account #%d already contains information.\n",
			book.ISBN);
	} /* end if */
	else { /* create record */

		/* user enters last name, first name and balance */
		printf("Enter title, author, year, Wholesale price, retail price\n? ");
		scanf("%s %s %d %f %f", book.title, book.author, &book.year, &book.wholesale_price, &book.retail_price);
		book.ISBN = bookNum;
			

		/* move file pointer to correct record in file */
		fseek(fPtr, (book.ISBN - 1) *
			sizeof(struct book), SEEK_SET);

		/* insert record in file */
		fwrite(&book,
			sizeof(struct book), 1, fPtr);
	} /* end else */

} /* end function newRecord */

/* enable user to input menu choice */
int enterChoice(void)
{
	int menuChoice; /* variable to store user's choice */

	/* display available options */
	printf("\nEnter your choice\n"
		"1 - store a formatted text file of acounts called\n"
		"    \"accounts.txt\" for printing\n"
		"2 - update an account\n"
		"3 - add a new account\n"
		"4 - delete an account\n"
		"5 - end program\n? ");

	scanf("%d", &menuChoice); /* receive choice from user */

	return menuChoice;

} /* end function enterChoice */

int randomAccess()
{
	int i; /* counter used to count from 1-100 */
	FILE *cfPtr;

	/* create book with default information */
	struct book blankBook = { "", "",0,0,0.0, 0.0 };

	//FILE *cfPtr; /* credit.dat file pointer */

	/* fopen opens the file; exits if file cannot be opened */
	//if ((cfPtr = fopen("C:\\Users\\David\\Desktop\\credit.dat", "wb")) == NULL) {
	//	printf("File could not be opened.\n");
	//}

	//fclose(cfPtr);
	if (cfPtr = fopen("C:\\Users\\David\\Desktop\\week19book.dat", "rb+") != NULL) return 0;
	cfPtr = fopen("C:\\Users\\David\\Desktop\\week19book.dat", "wb");
		
	for (i = 1; i <= 100; i++) 
	{
		fwrite(&blankBook, sizeof(struct book), 1, cfPtr);
	} 

	fclose(cfPtr);

	return 0; /* indicates successful termination */
}