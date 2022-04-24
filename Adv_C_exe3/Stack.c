#include "Stack.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

int StackLen(Stack* s); // help func - counting the length of the stack

/***************** Stack ADT Implementation *****************/

void initStack(Stack* s) // intializing the stack
{
	s->head = NULL;
}

void destroyStack(Stack* s) // clears the stack
{
	free(s->head);
	s->head = NULL;
}

void push(Stack* s, char data) // insert item to stack
{
	charNode* newnode = (charNode*)malloc(sizeof(charNode));

	if (!newnode) { puts("Allocation Failed!");	exit(0); }

	if (s->head == NULL) {     // the first element of the stack
		newnode->data = data;
		newnode->next = NULL;
		s->head = newnode;
	}
	else {
		newnode->data = data;
		newnode->next = s->head;
		s->head = newnode;
	}
}

char pop(Stack* s) // eject item from the stack
{
	charNode* temp = (charNode*)malloc(sizeof(charNode));
	if (!temp) { puts("Allocation Failed!");	exit(0); }
	char tempc;

	temp = s->head;
	tempc = temp->data;
	s->head = temp->next;
	temp->next = NULL;
	return tempc;
}


int isEmptyStack(const Stack* s) // checking if the stack is empty
{
	return(!s->head);
}

/*************** Functions using stacks - Implementation/definition **************************/

void flipBetweenHashes(const char* sentence) // flips the term between ##
{
	Stack* flipStack = (Stack*)malloc(sizeof(Stack));
	if (!flipStack) { puts("Allocation Failed!");	exit(0); }
	initStack(flipStack);
	charNode* fliptemp = (charNode*)malloc(sizeof(charNode));
	if (!fliptemp) { puts("Allocation Failed!");	exit(0); }

	if (sentence == "") { puts("NO WORDS FOUND!"); return; }

	printf("The flippes sentence is: ");

	while (*sentence != '\0')
	{
		if (*sentence != '#')
		{
			printf("%c", *sentence);
			sentence++;
		}
		else
		{
			sentence++;
			while (*sentence != '#')
			{
				push(flipStack, *sentence);
				sentence++;
			}

			//fliptemp = flipStack->head;
			while (!isEmptyStack(flipStack))
			{
				printf("%c", flipStack->head->data);
				pop(flipStack);
				//fliptemp = fliptemp->next;
			}
			sentence++;
		}
	}
}

int isPalindrome(Stack* s)
{
	if (s->head != NULL) {
		Stack* tempStack = (Stack*)malloc(sizeof(Stack));
		if (!tempStack) { puts("Allocation Failed!");	exit(0); }
		initStack(tempStack);
		charNode* tempNode1 = (charNode*)malloc(sizeof(charNode));
		if (!tempNode1) { puts("Allocation Failed!");	exit(0); }
		charNode* tempNode2 = (charNode*)malloc(sizeof(charNode));
		if (!tempNode2) { puts("Allocation Failed!");	exit(0); }
		tempNode1 = s->head;

		while (tempNode1 != NULL) {
			push(tempStack, tempNode1->data);
			tempNode1 = tempNode1->next;
		}

		tempNode2 = s->head;

		while (!isEmptyStack(tempStack))
		{
			if (tempNode2->data != tempStack->head->data)
			{
				return 0;
			}
			tempNode2 = tempNode2->next;
			pop(tempStack);
		}
		return 1;
	}
	else
	{
		puts("The Stack is empty!");
		return;
	}
}

void rotateStack(Stack* s, int n) // reverse n items  
{
	Stack* tempStack1 = (Stack*)malloc(sizeof(Stack));
	if (!tempStack1) { puts("Allocation Failed!");	exit(0); }
	initStack(tempStack1);
	Stack* tempStack2 = (Stack*)malloc(sizeof(Stack));
	if (!tempStack2) { puts("Allocation Failed!");	exit(0); }
	initStack(tempStack2);

	charNode* tempNode = (charNode*)malloc(sizeof(charNode));
	if (!tempNode) { puts("Allocation Failed!");	exit(0); }

	int size = StackLen(s);

	tempNode = s->head;
	if (n > 0 || n < size)
	{
		for (int i = 0; i < size - n - 1; i++) { // insert size - n items to tempStack1
			push(tempStack1, tempNode->data);
			tempNode = tempNode->next;
			pop(s);
		}

		while (!isEmptyStack(s)) {             // insert n items to tempStack2
			push(tempStack2, tempNode->data);
			tempNode = tempNode->next;
			pop(s);
		}

		while (!isEmptyStack(tempStack1)) {  // return items to s from tempstack1
			push(s, pop(tempStack1));
		}

		while (!isEmptyStack(tempStack2)) {  // return items to s from tempstack2
			push(s, pop(tempStack2));
		}
	}
	else
	{
		puts("The number n is negative or bigger than the stack variables!");
		return;
	}
}

int StackLen(Stack* s) // help func - counting the length of the stack
{
	Stack* temp = (Stack*)malloc(sizeof(Stack));
	if (!temp) { puts("Allocation Failed!");	exit(0); }
	charNode* tempNode = (charNode*)malloc(sizeof(charNode));
	if (!tempNode) { puts("Allocation Failed!");	exit(0); }
	initStack(temp);
	int count = 1;
	if (!isEmptyStack(s)) {
		temp = s;
		tempNode = temp->head;
		while (tempNode->next != NULL) {
			if (tempNode->next != NULL) {
				count++;
				tempNode = tempNode->next;
			}
		}
	}
	else {
		printf("The stack is empty!");
		return 0;
	}
	return count;
}

