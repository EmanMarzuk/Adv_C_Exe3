#include "Queue.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

int QueueLen(Queue* q); // help func - counting the length of the Queue

/***************** Queue ADT Implementation *****************/

void initQueue(Queue* q)
{
	q->head = NULL;
	q->tail = NULL;
}

void destroyQueue(Queue* q)
{
	free(q->head);
	free(q->tail);
	q->head = NULL;
	q->tail = NULL;
}

void enqueue(Queue* q, unsigned int data)
{
	intNode* newnode = (intNode*)malloc(sizeof(intNode));
	if (!newnode) { puts("Allocation Failed!");	exit(0); }

	newnode->data = data;

	if (q->head == NULL) {     // the first element of the stack
		newnode->next = NULL;
		q->head = newnode;
		q->tail = newnode;
	}
	else {
		newnode->next = q->head;
		q->head = newnode;
	}
}

unsigned int dequeue(Queue* q)
{
	intNode* temp = (intNode*)malloc(sizeof(intNode));
	if (!temp) { puts("Allocation Failed!");	exit(0); }

	int tempint = q->tail->data;
	temp = q->head;

	if (q->head != q->tail) {
		while (temp->next != q->tail)
		{
			temp = temp->next;
		}
		temp->next = NULL;
		q->tail = temp;
	}
	else {                // there is 1 node in the queue
		q->head = NULL;
		q->tail = NULL;
	}
	return tempint;
}

int isEmptyQueue(const Queue* q)
{
	return(!q->head);
}

/***************** Functions using Queues - Implementation/definition **************************/

void rotateQueue(Queue* q)
{
	intNode* tempNode1 = (intNode*)malloc(sizeof(intNode));
	if (!tempNode1) { puts("Allocation Failed!");	exit(0); }
	intNode* tempNode2 = (intNode*)malloc(sizeof(intNode));
	if (!tempNode2) { puts("Allocation Failed!");	exit(0); }

	tempNode1 = q->head;

	while (tempNode1->next != NULL)
	{
		if (tempNode1->next == q->tail)      // finding the node before the tail
		{
			tempNode2 = q->tail;
			tempNode2->next = q->head;
			q->head = tempNode2;
			q->tail = tempNode1;
			tempNode1->next = NULL;
		}
		else
		{
			tempNode1 = tempNode1->next;
		}
	}
}

void cutAndReplace(Queue* q)
{
	int len = QueueLen(q);
	Queue* tempQueue1 = (Queue*)malloc(sizeof(Queue));
	if (!tempQueue1) { puts("Allocation Failed!");	exit(0); }
	initQueue(tempQueue1);
	Queue* tempQueue2 = (Queue*)malloc(sizeof(Queue));
	if (!tempQueue2) { puts("Allocation Failed!");	exit(0); }
	initQueue(tempQueue2);

	intNode* tempNode1 = (intNode*)malloc(sizeof(intNode));
	if (!tempNode1) { puts("Allocation Failed!");	exit(0); }
	tempNode1 = q->head;

	intNode* tempNode2 = (intNode*)malloc(sizeof(intNode));
	if (!tempNode2) { puts("Allocation Failed!");	exit(0); }

	if (len % 2 == 0)     // number of nodes is even
	{
		for (int i = 0; i < len / 2; i++)  // splitting first len/2 elements to new queue
		{
			enqueue(tempQueue1, q->tail->data);
			dequeue(q);
		}
		while (!isEmptyQueue(q))  // splitting remaining len/2 elements to new queue
		{
			enqueue(tempQueue2, q->tail->data);
			dequeue(q);
		}
		while (!isEmptyQueue(tempQueue2))  // return the remaining len/2 elements to q
		{
			enqueue(q, tempQueue2->tail->data);
			dequeue(tempQueue2);
		}
		while (!isEmptyQueue(tempQueue1))   // return the first len/2 elements to q
		{
			enqueue(q, tempQueue1->tail->data);
			dequeue(tempQueue1);
		}
	}
	else    // number of nodes is odd
	{
		int sum = 0;
		while (tempNode1 != NULL)
		{
			sum += tempNode1->data;
			tempNode1 = tempNode1->next;
		}
		sum = sum / len;

		tempNode2->data = sum;
		tempNode2->next = NULL;
		q->tail->next = tempNode2;
		q->tail = tempNode2;

		len++;
		for (int i = 0; i < len / 2; i++)    // splitting first len/2 elements to new queue
		{
			enqueue(tempQueue1, q->tail->data);
			dequeue(q);
		}
		while (!isEmptyQueue(q))  // splitting remaining len/2 elements to new queue
		{
			enqueue(tempQueue2, q->tail->data);
			dequeue(q);
		}
		while (!isEmptyQueue(tempQueue2))  // return the remaining len/2 elements to q
		{
			enqueue(q, tempQueue2->tail->data);
			dequeue(tempQueue2);
		}
		while (!isEmptyQueue(tempQueue1))  // return the first len/2 elements to q
		{
			enqueue(q, tempQueue1->tail->data);
			dequeue(tempQueue1);
		}
	}
}

void sortKidsFirst(Queue* q)
{
	Queue* tempQueue1 = (Queue*)malloc(sizeof(Queue));
	if (!tempQueue1) { puts("Allocation Failed!");	exit(0); }
	initQueue(tempQueue1);

	intNode* tempNode1 = (intNode*)malloc(sizeof(intNode));
	if (!tempNode1) { puts("Allocation Failed!");	exit(0); }
	intNode* tempNode2 = (intNode*)malloc(sizeof(intNode));
	if (!tempNode2) { puts("Allocation Failed!");	exit(0); }

	while (!isEmptyQueue(q))
	{
		if (tempQueue1->head == NULL) {          // the first node in queue
			enqueue(tempQueue1, q->tail->data);
			dequeue(q);
		}
		else {
			if (q->tail->data <= tempQueue1->head->data) {   // insert befor the queue head
				enqueue(tempQueue1, q->tail->data);
				dequeue(q);
			}
			else {
				if (q->tail->data > tempQueue1->tail->data) {   // insert after tail

					tempNode1 = q->tail;
					tempQueue1->tail->next = tempNode1;
					tempNode1->next = NULL;
					tempQueue1->tail = tempNode1;
					dequeue(q);
				}
				else {
					if (q->tail->data > tempQueue1->head->data && q->tail->data < tempQueue1->tail->data) {     // insert between head and tail
						tempNode1 = tempQueue1->head->next;
						tempNode2 = tempQueue1->head;
						while (tempNode1->data <= q->tail->data)
						{
							tempNode2 = tempNode1;
							tempNode1 = tempNode1->next;
						}
						tempNode2->next = q->tail;
						tempNode2 = tempNode2->next;
						tempNode2->next = tempNode1;
						dequeue(q);
					}
				}
			}
		}
	}
	while (!isEmptyQueue(tempQueue1)) {
		enqueue(q, tempQueue1->tail->data);
		dequeue(tempQueue1);
	}
}

int QueueLen(Queue* q) // help func - counting the length of the Queue
{
	Queue* temp = (Queue*)malloc(sizeof(Queue));
	intNode* tempNode = (intNode*)malloc(sizeof(intNode));
	initQueue(temp);
	int count = 1;
	if (!isEmptyQueue(q)) {
		temp = q;
		tempNode = temp->head;
		while (tempNode->next != NULL) {
			if (tempNode->next != NULL) {
				count++;
				tempNode = tempNode->next;
			}
		}
	}
	else {
		printf("The queue is empty!");
		return 0;
	}
	return count;
}