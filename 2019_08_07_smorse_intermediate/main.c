#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "permutation_generator.h"
#include "smorse.h"
#include "linked_list.h"
#include "common.h"

int main() {
	char* random_alphabet; /* contains output from generate_random_permutation() */
	char* smorse_alphabet; /* smorse version of random_alphabet */
	char* solution;        /* will contain the alphabet that is solved from the random smorse alphabet. */
	char* searchPortion = NULL; /* part of the smorse alphabet. Choose random index, copy everything after. */
	char* letterData;      /* temp variable used when filling the linked lists. */

	/* linked lists for each classification of letter */
	struct Node* fourLetterHead = NULL;
	struct Node* threeLetterHead = NULL;
	struct Node* twoLetterHead = NULL;
	struct Node* oneLetterHead = NULL;

	char *randomLetter = NULL; /* smorse of a random letter from whichever linked list we're working with. */
	char randomLocation = 0;  /* random location to start searching in the smorse_alphabet. */

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

	for(i=0;i<numThreeLetters;i++) {
		letterData = malloc(sizeof(char)*4); /* +1 for null term */
		strcpy(letterData,letters[threeLetters[i]-97]);
		add_node(&threeLetterHead, letterData);
	}

	for(i=0;i<numTwoLetters;i++) {
		letterData = malloc(sizeof(char)*3); /* +1 for null term */
		strcpy(letterData,letters[twoLetters[i]-97]);
		add_node(&twoLetterHead, letterData);
	}

	for(i=0;i<numOneLetters;i++) {
		letterData = malloc(sizeof(char)*2); /* +1 for null term */
		strcpy(letterData,letters[oneLetters[i]-97]);
		add_node(&oneLetterHead, letterData);
	}

	print_list(fourLetterHead);
	print_list(threeLetterHead);
	print_list(twoLetterHead);
	print_list(oneLetterHead);

	srand(time(NULL));
	randomLocation = rand()%PERMUTATION_LENGTH;

	randomLetter = malloc(sizeof(char)*5); /* four letters */
	strcpy(randomLetter,get_index(rand()%numNodes(fourLetterHead), fourLetterHead));
	printf("randomLetter: %s\n", randomLetter);

	searchPortion = malloc(sizeof(char)*(strlen(smorse_alphabet)+1));
	strcpy(searchPortion, smorse_alphabet);

	/* just mask out the parts that we aren't searching for right now. */
	for(i=0;i<randomLocation;i++) {
		searchPortion[i] = '!';
	}

	printf("search portion: %s\n", searchPortion);
	printf("Found at: %s\n", strstr(searchPortion, randomLetter));

	delete_list(fourLetterHead);
	delete_list(threeLetterHead);
	delete_list(twoLetterHead);
	delete_list(oneLetterHead);
	free(searchPortion);
	free(randomLetter);
	free(solution);
	free(random_alphabet);
	free(smorse_alphabet);
	return 0;
}
