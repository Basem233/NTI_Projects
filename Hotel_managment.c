#include <stdio.h>
#include <stdlib.h>
#include "STD_TYPES.h"
#define password 1234

/*Make a struct that contain */
struct hotel
{
	u16 Res_N;
	u16 Room_N;
	//u8 age;
	u16 name[10];
	u8 period;
	struct hotel * nextptr;
};

struct hotel *head=NULL;
struct hotel *tail=NULL;

struct hotel * idsearch(u16 key);


//Add new client as a node in the list function
void AddNode (void);
//Displaying the Node Function
void DisplayNode (void);
//Edit user information
void EditNode (void);

void deleteClientData(char RN_search);

void main (void)
{
	u8 x,i,a,choice,choice1;
	u16 kk,uv,aa,bb,pass,key,key1;
	printf("To Enter Admin Mode Enter : 1\n");
	printf("To Enter User Mode Enter : 2\n");
	printf("---------------------------------------\n");
	printf("Your Choise: ");
	scanf("%d",&x);
	switch (x)
	{
		case 1:
		printf("Welcome Admin \n");
		printf("Please Enter Your Password :");
	    scanf("%d",&pass);
		if (pass==password)
		{
			while (1)
			{
			    printf("To Add New Client Enter 1 \n");
				printf("To Display client File Enter 2 \n");
				printf("To Edit Clinet Infromation Enter 3 \n");
				printf("To Check Out Press 4");
				printf("To Exit Enter 6 \n");
				scanf("%d",&a);
				switch (a)
				{
					case 1 :
					AddNode();
					break;
					case 2:
					DisplayNode();
					break;
					case 3:
					printf("Please Enter The Reservation Number: \n");
					EditNode();
					break;
					case 4:
					printf("Please Enter The Reservation Number: \n");
					u16 R_N ;
					scanf("%d",&R_N);//Take the variable for the user
					deleteClientData(R_N);
					break;
				}
				if(a==6)
				{
					printf("Thank You :)");
					break;
				}
			}
		}
		else if (pass!=password)//in case of wrong pass
		{
			for (i=0;i<3;i++)
			{
				printf("Please Enter Password Again : ");
				scanf("%d",&pass);
				if (pass==password)// in case he enter correct passs in trial
				{
					while (1)
					{
						printf("To Add New Client Enter 1 \n");
						printf("To Display client File Enter 2 \n");
						printf("To Edit Clinet Infromation Enter 3 \n");
						printf("To Check Out Press 4");
						printf("To Exit Enter 6 \n");
						printf("_______________________________\n");
						scanf("%d",&a);
						switch (a)
						{
							case 1 :
							AddNode();
							break;
							case 2:
							DisplayNode();
							break;
							case 3:
							printf("Please Enter The Reservation Number: \n");
							EditNode();
							break;
							case 4:
							printf("Please Enter The Reservation Number: \n");
							u16 R_N ;
							scanf("%d",&R_N);//Take the variable for the user
							deleteClientData(R_N);
							break;
						}
						if(a==6)
						{
							printf("Thank You :)");
							break;
						}
					}
				}
			}
			//to test the condition after the for loop
			if (pass!=password)
			{
			    printf("Incorrect password for 3 times : No more tries :(");
			}
		}
		
		//for case 1 as an admin
		break;
		//User Part
	    case 2:
		printf("Welcome You Entered As A User :) \n");
		while(1)
		{
			printf("/t/tWelcome to Our Hotel\n");
			printf("/t/t_______________________________\n");
		    printf("To Show Your Data Please Enter your Reservation number press 1\n");
			printf("To Exit Enter : 2\n");
			scanf("%d",&bb);
			switch(bb)
			{
				case 1:
				DisplayNode();
				break;
			}
			 if (bb==2)
			{
				printf("Thank You For Come back any time :) ");
				break;
			}
		}
	}	
}


struct hotel * search(u16 R_N)
{
	struct hotel * ptr;
	ptr=head;
	while (ptr!= NULL)
	{
		if (ptr->Res_N==R_N)
		{
			return ptr;
		}
		ptr=ptr->nextptr;
	}
	return NULL;
}

void AddNode()
{
	/*Make a local pointer to struct called ptr and store dynamicaly with the size of the struct*/
	struct hotel * ptr;
	u8 i;
	ptr=(struct hotel *)malloc(sizeof(struct hotel));
	/*Check if the pointer is equal to null (empty list or not)*/
	if (ptr!=NULL)
	{
		printf("Please Enter Client Name :");
		for (i=0;i<8;i++)
		{
			scanf("%c",&(ptr->name[i]));
		}
		
		printf("Please Enter The Planned Period to Stay: ");
		scanf("%d",&(ptr->period));
		printf("Please Enter Room Number ");
		scanf("%d",&(ptr->Room_N));
		printf("Please Enter Reservation number and give it to the user: ");
		scanf(" %d",&(ptr->Res_N));
		printf("__________________________________\n\n");
		printf("Thank You Enjoy Your Stay :D\n");
		printf("__________________________________\n\n");
		
		//here i will think in reservation case
		if(head==NULL)
		{
			head = ptr;
			tail = ptr;
			ptr->nextptr=NULL;
		}
		else
		{
			tail->nextptr=ptr;
			tail=ptr;
			tail->nextptr=NULL;
		}
	}
}

void DisplayNode()
{
	/*Make a local pointer to struct called ptr*/
	struct hotel * ptr;
	u16 R_N;u8 i;
	printf("__________________________________________________________\n");
	printf("To Display Client File Please Enter The Reservation Number : ");
	scanf("%d",&R_N);
	if (search(R_N)!=NULL)
	{
		ptr=search(R_N);
		printf("The Client Name is : ");
		for(i=0;i<10;i++)
		{
			printf("%c",(ptr->name[i]));
		}
		printf("\n");
		
		printf("The Stay Period : %d Days\n",(ptr->period));
		printf("The Room Number : %d\n",(ptr->Room_N));
	}
	else if (search(R_N)==NULL)
	{
		printf("__________________________________________________________\n");
		printf("This Client Is Not In The System -_- \n");
		printf("__________________________________________________________\n");
	}
	
}

void EditNode(void)
{
	/*Make a pointer to struct*/
	struct hotel * ptr;
	u16 R_N ; u8 i;
	scanf("%d",&R_N);//Take the variable for the user
	//Check null pointer
	if(search(R_N)!=NULL)
	{
		//to make ptr hold the user pointer
		ptr=search(R_N);
		printf("The Client New name : ");
		for (i=0;i<6;i++)
		{
			scanf("%c",&(ptr->name[i]));
		}
		printf("\n");
		printf("The Client New Stay Period : ");
		scanf("%d",&(ptr->period));
		printf("The hotel New Room Number : ");
		scanf(" %d",&(ptr->Room_N));
		printf("__________________________________\n\n");
		printf("Thank You :D\n");
		printf("__________________________________\n\n");
	}
	else if (search(R_N)==NULL)
	{
		printf("This Client Is Not Registered -_-\n");
	}
}


void deleteClientData(char RN_search)
{
	/*Make a pointer to struct*/
	struct hotel * ptr;
	if(search(RN_search)==NULL)
	{
		printf("Hotel is Empty!!\n");
	}
	else
	{
		
		struct hotel *prev = NULL; // Pointer to the previous node
		struct hotel *current = head; // Pointer to the current node

		// Search for the node with RN_search
		while (current != NULL)
		{
			if (current->Res_N == RN_search)
			{
				// Node found, unlink it
				if (prev != NULL)
				{
					// Skip the current node
					prev->nextptr = current->nextptr;
				} else
				{
					// Update the head if the first node is the one to be deleted
					head = current->nextptr;
				}

				free(current); // Free the memory of the deleted node
				return; // Exit the function
			}

			prev = current;
			current = current->nextptr;
		}
	}
}