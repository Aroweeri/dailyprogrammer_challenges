#include <stdio.h>
#include <stdlib.h>

void add_node(struct Node **head, int data) {
	struct Node *n = (struct Node*)malloc(sizeof(struct Node));
	n->data = data;
	n->next = *head;
	*head = n;
}

int get_index(int index, struct Node *head) {
	struct Node *n = (struct Node*)malloc(sizeof(struct Node));
	int data;
	int i;
	n = head;
	data = n->data;
	
	for(i=0;i<index;i++) {
		if(n == NULL) {
			return -1;
		}
		n = n->next;
		data = n->data;
	}
	return data;
}
