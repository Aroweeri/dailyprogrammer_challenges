#include "permutation_generator.h"
#include <sys/queue.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

char* generate_random_permutation() {
	SLIST_HEAD(slisthead, entry) head = SLIST_HEAD_INITIALIZER(head);
	int i = 0;
	int j = 0;
	char* random_alphabet;
	struct entry* cur;

	struct entry {
		SLIST_ENTRY(entry) entries;
		char value;
	} *node;

	srand(time(NULL));

	SLIST_INIT(&head);

	for(i='z';i>='a';i--) {
		node = malloc(sizeof(struct entry));
		node->value = i;
		SLIST_INSERT_HEAD(&head, node, entries);
	}

	random_alphabet = malloc(sizeof(char)*26);
	for(i=0;i<26;i++) {
		j=rand()%(26-i);
		cur = SLIST_FIRST(&head);
		while(j > 0) {
			cur = SLIST_NEXT(cur, entries);
			j--;
		}
		random_alphabet[i] = cur->value;
		SLIST_REMOVE(&head, cur, entry, entries);
		free(cur);
	}

	return random_alphabet;
}
