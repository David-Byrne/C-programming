//Simplified version of the board game monopoly created by David Byrne in 2015
//See associated pdf for details, instructions and a visual representation of the board.

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "time.h"

struct player
{
	char name[30];
	int balance;
	int location;
	int jailStatus;
	int bankrupt;
	int finalworth;
};

struct tile
{
	char name[30];
	int price;
	int ownedBy;
};

struct player players[8];
struct tile tiles[20];

int p = 0;//p is number of players

void initialisePlayers();
void initialiseTiles();
void printStatus(int round);
int rollDice();
int turnManager(int playerNum, int round);
void specialTile(int playerNum, int location );
void buyProperty(int playerNum, int location);
int payRent(int playerNum, int location, int round);
int sellProperty(int playerNum, int creditor, int bill, int round);
void passGo(int playerNum);
void endGame(int round);


void main()
{
	int roundnum = 0, i = 0;
	char choice = 'c';
	printf("How many players are there? (must be between 2 and 8 players) \n");
	scanf("%d", &p);
	while ((p < 2) || (p > 8))
	{
		printf("How many players are there? (must be between 2 and 8 players) \n");
		scanf("%d", &p);
	}
	initialisePlayers(p);
	initialiseTiles();
	while (choice != 'x')
	{
		printStatus(roundnum);
		roundnum++;
		for (; i < p; i++)
		{
			turnManager(i , roundnum);
		}
		//roundnum++;
		i = 0;
		fflush(stdin);
		printf("Press enter to continue or press x then enter to end the game.\n");
		choice = getchar();
		
	}
	endGame(roundnum);
}

void initialisePlayers()
{
	int i = 0;
	for (; i < p; i++)
	{
		printf("What is player number %d's name?\n", (i + 1));
		fflush(stdin);
		gets(players[i].name);
		players[i].balance = 1500;
		players[i].location = 0;
		players[i].jailStatus = 0;
		players[i].bankrupt = 0;
		players[i].finalworth = 0;
	}
	players[0].balance = 100;
	players[1].balance = 100;
}

void initialiseTiles()
{
	int i = 0;
	strcpy(tiles[0].name, "Go");
	tiles[0].price = 0;
	strcpy(tiles[1].name, "Old Long Walk");
	tiles[1].price = 100;
	strcpy(tiles[2].name, "Spanish Arch");
	tiles[2].price = 100;
	strcpy(tiles[3].name, "Shop Street");
	tiles[3].price = 100;
	strcpy(tiles[4].name, "Eyre Square");
	tiles[4].price = 100;

	strcpy(tiles[5].name, "Jail");
	tiles[5].price = 0;
	strcpy(tiles[6].name, "Uneeda Bookshop");
	tiles[6].price = 200;
	strcpy(tiles[7].name, "Uncle Larry's Desks");
	tiles[7].price = 200;
	strcpy(tiles[8].name, "Manganificent");
	tiles[8].price = 200;
	strcpy(tiles[9].name, "Byrne's Brilliant Bazaar");
	tiles[9].price = 200;

	strcpy(tiles[10].name, "Free Parking");
	tiles[10].price = 0;
	strcpy(tiles[11].name, "Menlo Park");
	tiles[11].price = 300;
	strcpy(tiles[12].name, "Redmond");
	tiles[12].price = 300;
	strcpy(tiles[13].name, "Cupertino");
	tiles[13].price = 300;
	strcpy(tiles[14].name, "Mountain View");
	tiles[14].price = 300;

	strcpy(tiles[15].name, "Go To Jail");
	tiles[15].price = 0;
	strcpy(tiles[16].name, "Engineering");
	tiles[16].price = 400;
	strcpy(tiles[17].name, "IT");
	tiles[17].price = 400;
	strcpy(tiles[18].name, "The Concourse");
	tiles[18].price = 400;
	strcpy(tiles[19].name, "The Hub");
	tiles[19].price = 400;

	for (; i < 20; i++)
	{
		tiles[i].ownedBy = -1;// owned by value -1 means nobody owns it
	}
}

void printStatus(int roundnum)
{
	int i = 0, j = 0;
	printf("\nStatus update at end of round %d\n", roundnum);
	printf("-----------------------------------------------------------------\n");
	for (; i < p; i++)
	{
		if (players[i].bankrupt != 0)
		{
			printf("%s is Bankrupt\n", players[i].name);
			continue;
		}
		printf("%s has %d cash!\n", players[i].name, players[i].balance);
		if (players[i].jailStatus != 0)
		{
			printf("However %s is in jail but will be released in %d turn(s)!\n", players[i].name, players[i].jailStatus);
		}
		j = 0;
		for (; j < 20; j++)
		{
			if (tiles[j].ownedBy == i)
			{
				printf("%s owns %s\n", players[i].name, tiles[j].name);
			}

		}
	}
	printf("-----------------------------------------------------------------\n");
}

int rollDice()
{
	int diceResult;
	srand(time(NULL)); //seeds with the time of day 
	diceResult = rand() % 6 + 1;
	return diceResult;
}

int turnManager(int playerNum, int roundnum)
{
	int location, dice;
	char enter;
	if (players[playerNum].bankrupt != 0)
	{
		printf("%s was declared bankrupt in round %d. Their game is over!\n", players[playerNum].name, players[playerNum].bankrupt);
		
		return 0;
	}
	printf("It is %s's turn!\n",players[playerNum].name);
	location = players[playerNum].location;
	if (players[playerNum].jailStatus > 0)
	{
		printf("%s is in Jail. They will be released in %d turn(s)!\n", players[playerNum].name, players[playerNum].jailStatus);
		players[playerNum].jailStatus--;
		return 0;
	}
	printf("%s, press enter to roll the dice!\n", players[playerNum].name);
	fflush(stdin);
	enter = getchar();//Should delay the player enough for the time to change and the srand seed to be different
	dice = rollDice();
	printf("%s rolled a %d\n", players[playerNum].name, dice);
	location = (location + dice) % 20;
	if (location < players[playerNum].location) passGo(playerNum);
	//if old location has a higher tile number than the new location, they've clearly passed Go
	players[playerNum].location = location;
	if (location % 5 == 0) specialTile( playerNum, location);
	else if (tiles[location].ownedBy == -1) buyProperty(playerNum, location);
	else payRent(playerNum, location, roundnum);
	return 1;
}

void specialTile(int playerNum, int location)
{
	if (location == 0)
	{
		printf("%s landed on GO!\n", players[playerNum].name);
	}
	else if (location == 5)
	{
		printf("%s landed on JAIL. Don't worry, you're only visiting!\n", players[playerNum].name);
	}
	else if (location == 10)
	{
		printf("%s landed on FREE PARKING. Enjoy your stay!\n", players[playerNum].name);
	}
	else if (location == 15)
	{
		printf("%s landed on GO TO JAIL. Go straight to jail!\n", players[playerNum].name);
		players[playerNum].location = 5;
		players[playerNum].jailStatus = 3;
	}
}

void buyProperty(int playerNum, int location)
{
	int choice = 0;
	printf("%s landed on %s!\n", players[playerNum].name, tiles[location].name);
	if (players[playerNum].balance >= tiles[location].price)
	{
		printf("Would you like to buy it for %d? (You have %d cash)\nEnter 1 for yes and 2 for no\n", tiles[location].price, players[playerNum].balance);
		scanf("%d", &choice);
		if (choice == 1)
		{
			printf("%s is the proud owner of %s\n", players[playerNum].name, tiles[location].name);
			players[playerNum].balance = players[playerNum].balance - tiles[location].price;
			tiles[location].ownedBy = playerNum;
			printf("Your new balance is %d\n", players[playerNum].balance);
		}
		else
		{
			printf("%s did not buy %s\n", players[playerNum].name, tiles[location].name);
		}
	}
	else
	{
		printf("%s has %d cash but %s costs %d\n", players[playerNum].name, players[playerNum].balance, tiles[location].name, tiles[location].price);
	}
}

int payRent(int playerNum, int location, int round)
{
	int owner = tiles[location].ownedBy, soldstatus = 0;
	int difference = 0;
	if (playerNum == owner)
	{
		printf("%s landed on %s!\n", players[playerNum].name, tiles[location].name);
		printf("You already own this property! Enjoy it!\n");
		return 0;
	}
	printf("%s landed on %s which is owned by %s!\n", players[playerNum].name, tiles[location].name, players[owner].name);
	int rent = (tiles[location].price / 4);
	if (players[playerNum].balance >= rent)
	{
		printf("%s paid %d rent to %s\n", players[playerNum].name, rent, players[owner].name);
		players[playerNum].balance = players[playerNum].balance - rent;
		players[owner].balance = players[owner].balance + rent;
		return 1;
	}
	else
	{
		printf("%s owes %d but only has %d in cash. Choose what to sell to pay your bill.\n", players[playerNum].name, rent, players[playerNum].balance);
		//difference = rent - players[playerNum].balance;
		soldstatus = sellProperty(playerNum, owner, rent, round);
		if (soldstatus == 1) printf("%s paid %d rent to %s\n", players[playerNum].name, rent, players[owner].name);
		return 1;
	}
}

int sellProperty(int playerNum ,int creditor, int bill, int round)
{
	while (players[playerNum].balance < bill)
	{
		int i = 0, j = 0, sell = 0;
		for (; i < 20; i++)
		{
			if (playerNum == tiles[i].ownedBy)
			{
				printf("%s, enter %d to sell %s for %d\n", players[playerNum].name, i, tiles[i].name, (tiles[i].price / 2));
				j++;//Counts how many properties are owned by this player
			}
		}
		if (j == 0)
		{
			printf("You don't have any more assets to sell\n");
			printf("%s has been declared bankrupt\n", players[playerNum].name);
			if (players[playerNum].balance != 0) printf("%s was given %s's remaining  %d cash\n", players[creditor].name, players[playerNum].name, players[playerNum].balance);
			players[creditor].balance = players[creditor].balance + players[playerNum].balance;
			players[playerNum].balance = 0;
			players[playerNum].bankrupt = round;
			return 0;
		}
		else
		{
			scanf("%d", &sell);
			if (tiles[sell].ownedBy == playerNum)
			{
				printf("%s sold %s for %d\n", players[playerNum].name, tiles[sell].name, (tiles[sell].price / 2));
				tiles[sell].ownedBy = -1;
				players[playerNum].balance = players[playerNum].balance + (tiles[sell].price / 2);
			}
			else
			{
				printf("%s does not own %s and therefore cannot sell it!\n", players[playerNum].name, tiles[sell].name);
			}
		}
	}
	//printf("%s paid %d rent to %s\n", players[playerNum].name, bill, players[creditor].name);
	players[playerNum].balance = players[playerNum].balance - bill;
	players[creditor].balance = players[creditor].balance + bill;
	return 1;
}
void passGo(int playerNum)
{
	printf("%s collected 100 in free cash at GO!\n", players[playerNum].name);
	players[playerNum].balance = players[playerNum].balance + 100;
}

void endGame(int round)
{
	int i = 0;
	int j = 0;
	int totalvalue = 0;
	for (; i < p; i++)
	{
		if (players[i].bankrupt != 0) players[i].finalworth = players[i].bankrupt - round - 1;
		//The earlier they were bankrupt, the lower their final worth. It will always be negative so to show they're bankrupt.
		else
		{
			players[i].finalworth = players[i].balance;
			for (; j < 20; j++)
			{
				if (tiles[j].ownedBy == i)
				{
					players[i].finalworth = players[i].finalworth + tiles[j].price;
				}
				
			}
			j = 0;
		}
	}
	//finds highest net worth; says this player is the winner then sets their networth = 0
	//then finds highest net worth; says this player is second place then sets their networth = 0 etc etc until all players are accounted for
	i = 0;
	j = 0;// resets counters so they can be used again
	int maxworth = players[0].finalworth;
	int leader = 0;
	for (; i < p; i++)
	{
		for (; j < p; j++)
		{
			if (players[j].finalworth > maxworth)
			{
				maxworth = players[j].finalworth;
				leader = j;

			}
		}
		if (players[leader].finalworth >= 0) printf("%s finishes in position %d with a net worth of %d\n", players[leader].name, (i + 1), players[leader].finalworth);
		else printf("%s finishes in position %d after going bankrupt in round %d\n", players[leader].name, (i + 1), players[leader].bankrupt);
		players[leader].finalworth = (-1)*round;//moves them to the bottom of the pile so they're not called out again.
		maxworth = (-1)*round;
		j = 0;//resets player counter
	}
}