#include <stdio.h>
#include "Stack.h"
#include "Queue.h"
#include <stdlib.h>

void main()
{
	// ************************************************* STACK ******************************************************
	Stack* s = (Stack*)malloc(sizeof(Stack));
	if (!s) { puts("Allocation Failed!");	exit(0); }
	int res;
	initStack(s);

	push(s, 'a');
	push(s, 'b');
	push(s, 'c');
	push(s, 'd');
	push(s, 'e');
	push(s, 'f');

	pop(s);
	pop(s);

	flipBetweenHashes("Remem#reb# thi#carp s#tice");
	printf("\n");

	if (isPalindrome(s))		printf("The stack is Polindrome\n");
	else       printf("The stack is not Polindrome\n");

	rotateStack(s, 2);

	destroyStack(s);

	// ************************************************* QUEUE ******************************************************

	Queue* q = (Queue*)malloc(sizeof(Queue));
	if (!q) { puts("Allocation Failed!");	exit(0); }
	initQueue(q);

	enqueue(q, 4);
	enqueue(q, 1);
	enqueue(q, 2);
	enqueue(q, 7);
	enqueue(q, 5);
	enqueue(q, 0);

	dequeue(q);
	dequeue(q);

	rotateQueue(q);

	sortKidsFirst(q);

	cutAndReplace(q);

	destroyQueue(q);
}