#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

void add_node(struct Node **head, char* data) {
	struct Node *n = malloc(sizeof(struct Node));
	n->data = data;
	n->next = *head;
	*head = n;
}

char* get_index(int index, struct Node *head) {
	struct Node *n;
	char* data;
	int i;
	n = head;
	data = n->data;
	
	for(i=0;i<index;i++) {
		if(n == NULL) {
			return NULL;
		}
		n = n->next;
		data = n->data;
	}
	return data;
}

void delete_index(int index, struct Node **head) {
	struct Node *n;
	struct Node *prev;
	int i;

	n = *head;
	if(index == 0) {
		if(n == NULL) {
			return;
		} else if(n->next == NULL) {
			*head = n->next;
			free(n->data);
			free(n);
		} else {
			*head = n->next;
			free(n->data);
			free(n);
		}
		return;
	}

	for(i=0;i<index;i++) {
		if(n == NULL) {
			return;
		}
		if(n->next == NULL) {
			free(n->data);
			free(n);
			n = NULL;
			return;
		}
		prev = n;
		n = n->next;
	}
	prev->next = n->next;
	free(n->data);
	free(n);
	/* (0)->(1)->(2)->(3)-> */
}

void delete_list(struct Node *head) {
	struct Node* n;
	struct Node* prev;
	n = head;

	while(n != NULL) {
		prev = n;
		if(n->next == NULL) {
			if(n->data != NULL) {
				free(n->data);
			}
			free(n);
			return;
		}
		n = n->next;
		free(prev->data);
		free(prev);
	}
}

void print_list(struct Node *head) {
	struct Node* n;
	n = head;

	while(n != NULL) {
		printf("%s -> ", n->data);
		if(n->next != NULL) {
			n = n->next;
		} else {
			printf("\n");
			return;
		}
	}
	return;
}

int numNodes(struct Node *head) {
	struct Node* n = head;
	int nodes = 0;
	while (n != NULL) {
		n = n->next;
		nodes++;
	}
	return nodes;
}
