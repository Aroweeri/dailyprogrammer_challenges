#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "permutation_generator.h"
#include "smorse.h"
#include "linked_list.h"
#include "common.h"

struct LetterLists {
	struct Node* fourLetterHead;
	struct Node* threeLetterHead;
	struct Node* twoLetterHead;
	struct Node* oneLetterHead;
};

char* decodeSmorse(char* smorse_alphabet, struct LetterLists* lists) {

	char *randomLetter = NULL; /* smorse of a random letter from whichever linked list we're working with. */
	char randomLetterIndex = 0;/* the index of the random letter that was taken of the linked list. */
	char randomLocation = 0;  /* random location to start searching in the smorse_alphabet. */
	char *foundLocation = NULL; /* return value from strstr */
	char *solution = NULL;
	char* searchPortion = NULL; /* part of the smorse alphabet. Choose random index, copy everything after. */

	int i;
	int j;

	solution = malloc(sizeof(char)*PERMUTATION_LENGTH+1); /* +1 for null */
	strcpy(solution, smorse_alphabet);
	srand(time(NULL));
	randomLetter = malloc(sizeof(char)*5); /* four letters */
	searchPortion = malloc(sizeof(char)*(strlen(smorse_alphabet)+1));

	for(i=0;i<numFourLetters;i++) {
		randomLocation = rand()%PERMUTATION_LENGTH;

		randomLetterIndex = rand()%numNodes(lists->fourLetterHead);
		strcpy(randomLetter,get_index(randomLetterIndex, lists->fourLetterHead));
		delete_index(randomLetterIndex, &(lists->fourLetterHead));
		printf("randomLetter: %s\n", randomLetter);

		strcpy(searchPortion, smorse_alphabet);

		/* just mask out the parts that we aren't searching for right now. */
		for(j=0;j<randomLocation;j++) {
			searchPortion[j] = '!';
		}

		foundLocation = strstr(searchPortion, randomLetter);
		if(foundLocation == NULL) {
			printf("Not found in searchPortion, trying whole alphabet\n");
			foundLocation = strstr(smorse_alphabet, randomLetter);
			if(foundLocation == NULL) { /* exhausted possibilities, need to start over */
				free(searchPortion);
				free(randomLetter);
				return NULL;
			}
		}

		printf("search portion: %s\n", searchPortion);
		printf("Found at: %s\n", foundLocation);
	}
	free(searchPortion);
	free(randomLetter);
	return solution;
}

int main() {
	char* random_alphabet; /* contains output from generate_random_permutation() */
	char* smorse_alphabet; /* smorse version of random_alphabet */
	char* solution;        /* will contain the alphabet that is solved from the random smorse alphabet. */
	char* letterData;      /* temp variable used when filling the linked lists. */

	struct Node* fourLetterHead = NULL;
	struct Node* threeLetterHead = NULL;
	struct Node* twoLetterHead = NULL;
	struct Node* oneLetterHead = NULL;

	struct LetterLists *lists;

	int i;

	random_alphabet = generate_random_permutation();
	smorse_alphabet = smorse(random_alphabet);
	printf("%s\n", random_alphabet);
	printf("%s\n", smorse_alphabet);

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

	lists = malloc(sizeof(struct LetterLists));
	lists->fourLetterHead = fourLetterHead;
	lists->threeLetterHead = threeLetterHead;
	lists->twoLetterHead = twoLetterHead;
	lists->oneLetterHead = oneLetterHead;

	/* keep trying until successful */
	solution = NULL;
	while((solution = decodeSmorse(smorse_alphabet, lists)) == NULL);

	delete_list(lists->fourLetterHead);
	delete_list(lists->threeLetterHead);
	delete_list(lists->twoLetterHead);
	delete_list(lists->oneLetterHead);
	free(lists);
	free(solution);
	free(random_alphabet);
	free(smorse_alphabet);
	return 0;
}
