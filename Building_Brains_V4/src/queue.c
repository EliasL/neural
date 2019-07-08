/*
 * queue.c
 *
 * Created: 01.07.2019 09:35:26
 * Author: Elias
 * https://stackoverflow.com/questions/4184954/are-there-standard-queue-implementations-for-c
 */ 
#include <stdio.h>
#include <stdlib.h>
#include "include/queue.h"

void enqueue(node_t **head, uint32_t val) {
	// remember, head is at the very BACK of the queue (The element that will wait the longest until dequeued)
	
	// we create a new empty node
	node_t *new_node = malloc(sizeof(node_t));
	// Not quite sure what happens here, but it seems to be some sort of error handling, except you never know if there has been an error :/
	if (!new_node) return;

	// we configure our node
	new_node->val = val;
	new_node->next = *head;

	// and lastly, we change the pointer pointing to the previous head node, to point to our new node instead
	*head = new_node;
}

uint32_t dequeue(node_t **head) {
	// We prepare some variables
	node_t *current, *prev = NULL;
	uint32_t retval = 0;

	// If the queue we have been given is empty, we return an error
	// (0 is usually not an error, but it is probably the best option)
	if (*head == NULL) return 0;

	// Now we iterate through the queue until we reach the end
	current = *head;
	while (current->next != NULL) {
		prev = current;
		current = current->next;
	}

	// We retrieve the value we needed
	retval = current->val;
	// and remove the last element of the queue from the queue
	free(current);
	
	// Now we update the previous node so that it becomes the front of the queue
	// In case the queue only had one element, the prev will be null (false)
	if (prev){
	prev->next = NULL;}
	else{
	*head = NULL;}

	return retval;
}

// Here we remove the element of the queue that was added last (first in, last out)
uint32_t dequeue_top(node_t **head){
	// Prepare some variables
	node_t *newHead;
	node_t *oldHead;
	uint32_t retval = 0;
	
	// If the queue we have been given is empty, we return an error
	// (0 is usually not an error, but it is probably the best option)
	if (*head == NULL) return 0;
	
	oldHead = *head;
	// We then set the new head to be the second last in the queue
	newHead = oldHead->next;
	
	// We retrieve the heads value
	retval = oldHead->val;
	
	// We free the memory that was used to store the old head
	free(oldHead);
	
	//And then we overwrite the value of head to be the second last
	*head = newHead;
	
	return retval;
	
}

uint32_t read_end(node_t **head){
	// We prepare some variables
	node_t *current, *prev = NULL;
	uint32_t retval = 0;

	// If the queue we have been given is empty, we return an error
	// (0 is usually not an error, but it is probably the best option)
	if (*head == NULL) return 0;

	// Now we iterate through the queue until we reach the end
	current = *head;
	while (current->next != NULL) {
		prev = current;
		current = current->next;
	}

	// We retrieve the value we needed
	retval = current->val;
	
	return retval;
	
}