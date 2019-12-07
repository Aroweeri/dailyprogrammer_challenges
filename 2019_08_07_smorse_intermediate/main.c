#include <stdio.h>
#include <stdlib.h>
#include "permutation_generator.h"
#include "smorse.h"
#include "linked_list.h"
#include "common.h"

int main() {
	char* random_alphabet;
	char* smorse_alphabet;
	char* solution;

	random_alphabet = generate_random_permutation();
	smorse_alphabet = smorse(random_alphabet);
	printf("%s\n", random_alphabet);
	printf("%s\n", smorse_alphabet);

	solution = malloc(sizeof(char)*PERMUTATION_LENGTH);

	free(solution);
	free(random_alphabet);
	free(smorse_alphabet);
	return 0;
}
