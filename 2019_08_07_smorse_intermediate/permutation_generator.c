#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "permutation_generator.h"
#include "linked_list.h"

char* generate_random_permutation() {
	struct Node* head; /* head of linked list */
	struct Node* n; /* linked list iterator */
	struct Node* new;
	char* newData;
	int i = 0;
	int j = 0;
	int nexts = 0;
	char* random_alphabet;

	srand(time(NULL));
	head = NULL;

	/* generate linked list of the alphabet */
	for(i='z';i>='a';i--) {
		newData = malloc(sizeof(char));
		*newData = i;
		add_node(&head, newData);
	}

	random_alphabet = malloc(sizeof(char)*26);
	for(i=0;i<26;i++) {
		nexts = 0;
		j=rand()%(26-i);
		n = head;
		while(j > 0) {
			n = n->next;
			nexts++;
			j--;
		}
		random_alphabet[i] = *(n->data);
		delete_index(nexts, &head);
	}

	delete_list(head);
	return random_alphabet;
}
