// Animals.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define A_MAX_SIZE     ((size_t) 20)
typedef enum aType {
	aUndefined=0,
	aDog,
	aCat
} AnType;



typedef struct Data {
	AnType type;
	char  name[A_MAX_SIZE];
	char  date1[A_MAX_SIZE];
	char  date2[A_MAX_SIZE];
	char  date3[A_MAX_SIZE];
} aData;

typedef struct Item {
	aData data;
	struct Item* next;
} lItem;

int ReadFile(FILE *fl, lItem **list);
void PrintData(lItem *list);
void DeleteList(lItem** list);
void SortByType(lItem* list);
void DeleteAdopted(lItem** list);
void SortByDate3(lItem* list);


char *menu[]={
		"Menu",
			"1. Sort list by animal type.",
			"2. Sort by adoption date.",
			"3. Delete adopted.",
			"4. Exit."
};

int print_menu()
{
	int mode=-1;
	printf ("\n%s\n",menu[0]);
	printf ("%s\n",menu[1]);
	printf ("%s\n",menu[2]);
	printf ("%s\n",menu[3]);
	printf ("%s\n",menu[4]);

	scanf("%d", &mode);
	return mode;
}

int main(int argc, char* argv[])
{
	FILE* f = fopen("Data.txt", "r");
	lItem* list=NULL;
	if (f != NULL)
	{
		int  mode;
		ReadFile(f,&list);
		PrintData(list);
		//some statistics do here....with menu
		do
		{
			mode = print_menu();
			fflush(stdin);
			switch(mode)
			{
			case 1:
				{
					SortByType(list);
					PrintData(list);
				}
				break;
			case 2:
				{
					SortByDate3(list);
					PrintData(list);
				}
				break;
			case 3:
				{
					DeleteAdopted(&list);
					PrintData(list);

				}
				break;
			default:
				printf("\nNevaliden izbor!\n");
			}
		}while(mode!=4);


		DeleteList(&list);
	}
	return 0;
}

int ReadFile(FILE *fl, lItem **list)
{

	lItem* temp_node = NULL;
	lItem* i = NULL;
	aData temp={aUndefined};


	for (; fscanf(fl, "%d\t ", &temp.type) != EOF; )
	{
		fscanf(fl, "%s\t", temp.name);
		fscanf(fl, "%s\t", temp.date1);
		fscanf(fl, "%s\t", temp.date2);
		fscanf(fl, "%s\n", temp.date3);

		//if(strcmp(temp.date1,"-")!=0 && strcmp(temp.date2,"-")!=0 && strcmp(temp.date3,"-")!=0)
		{
			temp_node = (lItem*)calloc(sizeof(lItem),1);
			temp_node->data.type = temp.type;
			strcpy(temp_node->data.name, temp.name);
			strcpy(temp_node->data.date1, temp.date1);
			strcpy(temp_node->data.date2, temp.date2);
			strcpy(temp_node->data.date3, temp.date3);

			temp_node->next = NULL;
		}
		if (*list == NULL)
		{
			i = *list = temp_node;
		}
		else
		{

			i = i->next = temp_node;
		}
	}

	return 0;
}

void PrintData(lItem *list)
{
	lItem* i = NULL;
	printf("======================================================================\n");
	printf("Name\t|Type\t|Receipt\t|Castration\t|Adoption\n");
	printf("======================================================================\n");

	for (i = list; i != NULL; i = i->next)
	{
		printf("%s\t", (i->data).name);
		switch((i->data).type)
		{
		case aDog:
			printf("Dog\t");
			break;
		case aCat:
			printf("Cat\t");
			break;
		default:
			printf("Undefined\t");
			break;
		}
		printf("%s\t%s\t%s\n", (i->data).date1,(i->data).date2,(i->data).date3);
	}
}

void DeleteList(lItem** list)
{
	lItem* i = NULL;


	for (i = *list; i != NULL; )
	{
		*list = (*list)->next;
		free(i);
		i = *list;
	}


	return ;
}


void SortByType(lItem* list)
{

  lItem* i = list;
  lItem* j = NULL;
  while (i->next!=NULL)
  {
	  j = i->next;
	  while(j!=NULL)
	  {
		  if (i->data.type>j->data.type)
		  {
			  aData temp = i->data;
			  i->data = j->data;
			  j->data = temp;
		  }
		  j = j->next;
	  }
	  i = i->next;
  }
}

void SortByDate3(lItem* list)
{

  lItem* i = list;
  lItem* j = NULL;
  while (i->next!=NULL)
  {
	  j = i->next;
	  while(j!=NULL)
	  {
		  if(strcmp(i->data.date3,"-")!=0 && strcmp(j->data.date3,"-")!=0)
		  {
			  //current node
			  char* dd=i->data.date3;

			  int D=atoi(dd);
			  char* mm=&i->data.date3[3];

			  int M=atoi(mm);
			  char* y=&i->data.date3[6];

			  int Y=atoi(y);

			  //next node
			  dd=j->data.date3;

			  int nD=atoi(dd);
			  mm=&j->data.date3[3];

			  int nM=atoi(mm);
			  y=&j->data.date3[6];

			  int nY=atoi(y);

			  if (Y>nY)
			  {
				  aData temp = i->data;
				  i->data = j->data;
				  j->data = temp;
			  }
			  else if(M>nM)
			  {
				  aData temp = i->data;
				  i->data = j->data;
				  j->data = temp;
			  }
			  else if(D>nD)
			  {
				  aData temp = i->data;
				  i->data = j->data;
				  j->data = temp;
			  }
		  }
		  j = j->next;
	  }
	  i = i->next;
  }
}

void DeleteAdopted(lItem** list)
{
	lItem* head=*list;
	lItem* curr=*list;
	lItem* next=(lItem*)curr->next;
	while(next!=NULL)
	{
		if(strcmp(next->data.date3,"-")!=0)
		{
			curr->next=next->next;
			free(next);
			next=curr->next;
		}
		else
		{
			curr=curr->next;
			next=next->next;
		}
	}

	if(strcmp(head->data.date3,"-")!=0)
	{
		*list=head->next;
		free(head);

	}
}
