#include "permutation_generator.h"
#include "smorse.h"
#include "linked_list.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	char* random_alphabet;
	char* smorse_alphabet;
	char* solution;
	char* letter;

	struct Node* n = malloc(sizeof(struct Node));
	letter = malloc(sizeof(char));
	*letter = 'v';
	add_node(&n, letter);
	printf("%c\n", *(get_index(0, n))); 

	random_alphabet = generate_random_permutation();
	smorse_alphabet = smorse(random_alphabet);
	printf("%s\n", random_alphabet);
	printf("%s\n", smorse_alphabet);

	solution = malloc(sizeof(char)*PERMUTATION_LENGTH);

	free(random_alphabet);
	free(smorse_alphabet);
	return 0;
}
