#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "permutation_generator.h"
#include "smorse.h"
#include "linked_list.h"
#include "common.h"

int main() {
	char* random_alphabet;
	char* smorse_alphabet;
	char* solution;
	char* letterData;
	struct Node* fourLetterHead = NULL;
	int i;

	random_alphabet = generate_random_permutation();
	smorse_alphabet = smorse(random_alphabet);
	printf("%s\n", random_alphabet);
	printf("%s\n", smorse_alphabet);

	solution = malloc(sizeof(char)*PERMUTATION_LENGTH+1); /* +1 for null */
	strcpy(solution, smorse_alphabet);

	for(i=0;i<numFourLetters;i++) {
		letterData = malloc(sizeof(char)*5); /* +1 for null term */
		strcpy(letterData,letters[fourLetters[i]-97]);
		add_node(&fourLetterHead, letterData);
	}

	print_list(fourLetterHead);
	delete_list(fourLetterHead);

	free(solution);
	free(random_alphabet);
	free(smorse_alphabet);
	return 0;
}
