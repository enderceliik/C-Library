#https://github.com/Enderceliik
#Ender CELIK

// Reverse and Merge process on doubly linked list.
#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedList1{

    int data;
    struct LinkedList1 *next;
    struct LinkedList1 *prev;

}ll1;

typedef struct LinkedList2{

    int data;
    struct LinkedList2 *next;
    struct LinkedList2 *prev;

}ll2;

ll1 *first = NULL;
ll2 *first2 = NULL;

void memoryAllocater(int linkedListSize)
{
    for(int i = 0; i < linkedListSize; i++)
    {
        ll1 *new_node1 = (ll1*)malloc(sizeof(ll1));
        ll2 *new_node2 = (ll2*)malloc(sizeof(ll2));
        addFunction(new_node1, new_node2);
    }
}
void addFunction(ll1 *new_node1, ll2 *new_node2)
{
    if(first == NULL)
    {
        first = new_node1;
        new_node1 -> data = rand() % 100 + 1;
        new_node1 -> next = NULL;
        new_node1 -> prev = NULL;

        first2 = new_node2;
        new_node2 -> data = rand() % 100 + 1;
        new_node2 -> next = NULL;
        new_node2 -> prev = NULL;
    }
    else
    {
        ll1 *temp = first;
        while(temp->next != NULL)
        {
            temp = temp -> next;
        }

        temp->next = new_node1;
        new_node1 -> data = rand() % 90 + 10;  // create random data for node.
        new_node1 -> prev = temp;
        new_node1 -> next = NULL;

        ll2 *temp2 = first2;
        while(temp2->next != NULL)
        {
            temp2 = temp2 -> next;
        }
        temp2->next = new_node2;
        new_node2 -> data = rand() % 90 + 10;
        new_node2 -> prev = temp2;
        new_node2 -> next = NULL;
    }
}
void totalList()
{
    ll1 *temp = first;
    while(temp)
    {
        printf("     %d --- %d\n",temp->data, temp);
        temp = temp -> next;
    }
    printf("\n\n");
}
void listener()
{
     if(first == NULL)
     {
         printf("There is no list to show...\n");
     }
     else
     {
         ll1 *temp = first;
         while(temp)
         {
             printf("list 1: %d -- %d\n",temp->data, temp);
             temp = temp ->next;
         }
         printf("\n\n");
     }
 }
void listener2()
{
     if(first2 == NULL)
     {
         printf("There is no list to show...\n");
     }

     else
     {
         ll2 *temp = first2;
         while(temp)
         {
             printf("list 2: %d -- %d\n",temp->data, temp);
             temp = temp->next;
         }
         printf("\n\n");
     }
 }
void twiceListener()
{
     if(first == NULL)
     {
         printf("There is no list to show...\n");
     }
     else
     {
         printf("\n 1.liste:     2.liste: \n");
         ll1 *temp = first;
         ll2 *temp2 = first2;
         while(temp)
         {
             printf("       %d ---- %d \n",temp->data, temp2->data);
             printf("  %d ---- %d\n\n",temp,temp2);
             temp = temp ->next;
             temp2 = temp2->next;
         }
        printf("\n\n");
     }
 }
void unifyingFunc()
{
    ll1 *temp = first;
    ll2 *save = first2;
    ll2 *temp2 =save;

    while(temp2 != NULL)
    {
        if(first == NULL)
            return 0;
        else
        {
            temp2 -> prev = temp;

            if(temp->next == NULL)
            {
                save = temp2 -> next;
                temp2 -> next = NULL;
            }
            else
            {
                save = temp2 -> next;
                temp2 -> next = temp -> next;
                temp -> next -> prev = temp2;
            }
            temp -> next = temp2;

            temp = temp -> next -> next;
            temp2 = save;
        }
    }
}
void reverseFunc(int linkedListSize) // reverse process
{
    ll1 *temp = first;
    ll1 *tempFromEnd = first;
    ll1 *swapper = NULL;
    int counter = linkedListSize;

	if (counter == 1) // if we have two node at final situation. Just change location the these.
    {
        temp -> prev = tempFromEnd;
        tempFromEnd -> next = temp;
        first = tempFromEnd;
        tempFromEnd -> prev = NULL;
        temp -> next = NULL;
        return;
    }
	
    while(tempFromEnd -> next != NULL) // will progress from end. : tempFromEnd
    {
        tempFromEnd = tempFromEnd -> next; 
    }

    
    while(counter > 0) // change process up to our list size: for example: 1 2 3 4 -> 4 2 3 1 -> 4 3 2 1
    {
        if(temp -> prev == NULL)
        {
            temp -> next -> prev = tempFromEnd;
            tempFromEnd -> prev -> next = temp;
            tempFromEnd -> next = temp -> next;
            temp -> prev = tempFromEnd -> prev;
            tempFromEnd -> prev = NULL;
            temp -> next = NULL;
            first = tempFromEnd;

            swapper = tempFromEnd ->next;
            tempFromEnd = temp -> prev;
            temp = swapper;
            counter--;
            continue;
        }
        if(temp -> next == tempFromEnd)
        {
            temp -> prev -> next = tempFromEnd;
            tempFromEnd -> next -> prev = temp;

            swapper = temp ->next;
            temp -> next = tempFromEnd ->next;
            tempFromEnd ->next = temp;

            swapper = temp ->prev;
            temp ->prev = tempFromEnd;
            tempFromEnd ->prev = swapper;

            swapper = tempFromEnd ->next;
            tempFromEnd = temp -> prev;
            temp = swapper;
            counter--;
            continue;
        }
        else
        {
            temp -> prev -> next = tempFromEnd;
            tempFromEnd -> next -> prev = temp;

            swapper = temp ->next;
            temp -> next = tempFromEnd ->next;
            tempFromEnd ->next = swapper;

            swapper = temp ->prev;
            temp ->prev = tempFromEnd->prev;
            tempFromEnd ->prev = swapper;

            tempFromEnd -> next -> prev = tempFromEnd;
            temp -> prev -> next = temp;

            swapper = tempFromEnd ->next;
            tempFromEnd = temp -> prev;
            temp = swapper;
            counter--;
            continue;
        }
    }
}
int main()
{
    int sizeOfLinkedList;
    printf("Enter size of linked lists: ");
    scanf("%d",&sizeOfLinkedList);

    memoryAllocater(sizeOfLinkedList); // the function that creates our two lists separately.
    twiceListener(); // lists and addresses.
    //listener();
    //listener2();

    unifyingFunc(); //  this function combining lists.
    printf("After the merge process:\n\n");
    totalList(); // lists and addresses after the merge process.

    reverseFunc(sizeOfLinkedList); // let's reverse the list.
    printf("After the reverse process:\n\n");
    totalList(); // final situation.
    return 0;
}
