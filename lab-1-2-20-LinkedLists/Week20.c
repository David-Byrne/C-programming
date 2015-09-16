#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

struct node
{
	int ID;
	char name[20];
	struct node *next;
};
struct node *first = NULL, *current = NULL; *next = NULL;

void addNode();
void deleteNode();
void displayList();
void searchNodes();
void freeAll();

void main()
{
	//current = first

	first = current = NULL;
	

	int choice = 0;
	while (choice != 5)
	{
		printf("Press 1 to add a node\nPress 2 to Delete a node\nPress 3 to display the list\nPress 4 to search for a node\nPress 5 to quit\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			addNode();
			break;
		case 2:
			deleteNode();
			break;
		case 3:
			displayList();
			break;
		case 4:
			searchNodes();
			break;
		case 5:
			break;
		default:
			printf("Input not recognised!\n");
		}
	}
	freeAll();
}

void addNode()
{
	int id = 0;
	if (first == NULL)
	{
		first = (struct node *)malloc(sizeof(struct node));
		
		printf("Enter the node ID\n");
		scanf("%d", &id);
		first->ID = id;
		printf("Enter the node's name\n");
		fflush(stdin);
		gets(first->name);
		first->next = NULL;
		current = first;
	}
	else
	{
		current = first;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = (struct node *)malloc(sizeof(struct node));
		current = current->next;
		printf("Enter the node ID\n");
		scanf("%d", &id);
		current->ID = id;
		printf("Enter the node's name\n");
		fflush(stdin);
		gets(current->name);
		current->next = NULL;
	}
}

void deleteNode()
{
	int id = 0;
	printf("Enter the id of the node you want to delete\n");
	scanf("%d", &id);
	current = first;
	if (current == NULL)
	{
		printf("There are no nodes...\n");
		return;
	}
	if (first->ID == id)
	{
		printf("Found\n");
		first = first->next;
		free(current);
		return;
	}
	while (current != NULL)
	{
		if (id == (current->next)->ID)
		{
			printf("Found\n");
			struct node *deleted = current->next;
			current->next = (current->next)->next;//this pointer points over the "deleted" link
			free(deleted);
			return;
		}
		else
		{
			current = current->next;
		}
	}
	printf("It wasn't found...\n");
}

void displayList()
{
	current = first;
	if (first == NULL)
	{
		printf("There are no nodes...\n");
		return;
	}
	else while (current != NULL)
	{
		printf("--------------------------------------\n");
		printf("The node's ID is %d\n", current->ID);
		printf("The node's name is %s\n", current->name);
		current = current->next;
	}
	printf("--------------------------------------\n");

}

void searchNodes()
{
	int id = 0;
	printf("Enter the id of the node you want to search for\n");
	scanf("%d", &id);
	current = first;
	while (current != NULL)
	{
		if (id == current->ID)
		{
			printf("Found\n");
			printf("The name is %s\n", current->name);
			return;
		}
		else
		{
			current = current->next;
		}
	}
	printf("It wasn't found...\n");
}

void freeAll()
{
	current = first;
	struct node *nextnode = first;
	while (nextnode != NULL)
	{
		current = nextnode;
		nextnode = nextnode->next;
		free(current);
	}
	//free(first);
	//free(next);
}