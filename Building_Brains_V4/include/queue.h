/*
 * queue.h
 *
 * Created: 01.07.2019 16:01:05
 *  Author: Elias
 */ 


#ifndef QUEUE_H_
#define QUEUE_H_

typedef struct node {
	uint32_t val;
	struct node *next;
} node_t;

void enqueue(node_t **head, uint32_t val);

uint32_t dequeue(node_t **head);

uint32_t dequeue_top(node_t **head);

uint32_t read_end(node_t **head);

#endif /* QUEUE_H_ */