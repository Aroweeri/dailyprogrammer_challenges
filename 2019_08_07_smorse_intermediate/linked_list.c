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
	for(i=0;i<index;i++) {
		if(n == NULL) {
			return;
		}
		if(n->next == NULL) {
			free(n);
			n = NULL;
			return;
		}
		prev = n;
		n = n->next;
	}
	prev->next = n->next;
	free(n);

}

void delete_list(struct Node **head) {
	
}
