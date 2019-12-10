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

void generateLists(struct LetterLists* lists) {
	int i;
	char* letterData;      /* temp variable used when filling the linked lists. */

	delete_list(lists->fourLetterHead);
	delete_list(lists->threeLetterHead);
	delete_list(lists->twoLetterHead);
	delete_list(lists->oneLetterHead);
	lists->fourLetterHead = NULL;
	lists->threeLetterHead = NULL;
	lists->twoLetterHead = NULL;
	lists->oneLetterHead = NULL;

	for(i=0;i<numFourLetters;i++) {
		letterData = malloc(sizeof(char)*5); /* +1 for null term */
		strcpy(letterData,letters[fourLetters[i]-'a']);
		add_node(&(lists->fourLetterHead), letterData);
	}

	for(i=0;i<numThreeLetters;i++) {
		letterData = malloc(sizeof(char)*4); /* +1 for null term */
		strcpy(letterData,letters[threeLetters[i]-'a']);
		add_node(&(lists->threeLetterHead), letterData);
	}

	for(i=0;i<numTwoLetters;i++) {
		letterData = malloc(sizeof(char)*3); /* +1 for null term */
		strcpy(letterData,letters[twoLetters[i]-'a']);
		add_node(&(lists->twoLetterHead), letterData);
	}

	for(i=0;i<numOneLetters;i++) {
		letterData = malloc(sizeof(char)*2); /* +1 for null term */
		strcpy(letterData,letters[oneLetters[i]-'a']);
		add_node(&(lists->oneLetterHead), letterData);
	}
}

char lookupFromMorse(char* morse) {
	int i;
	char returnThis;
	for(i=0;i<26;i++) {
		if(strcmp(morse, letters[i]) == 0) {
			returnThis = i+'a';
		}
	}
	return returnThis;
}

char* decodeSmorse(char* smorse_alphabet, struct LetterLists* lists) {

	char *randomLetter = NULL; /* smorse of a random letter from whichever linked list we're working with. */
	char randomLetterIndex = 0;/* the index of the random letter that was taken of the linked list. */
	char randomLocation = 0;  /* random location to start searching in the smorse_alphabet. */
	char *foundLocation = NULL; /* return value from strstr */
	char *solution = NULL;
	char* searchPortion = NULL; /* part of the smorse alphabet. Choose random index, copy everything after. */

	int j;
	int lengthOfMorse = 4;


	solution = malloc(sizeof(char)*PERMUTATION_LENGTH+1); /* +1 for null */
	strcpy(solution, smorse_alphabet);
	randomLetter = malloc(sizeof(char)*5); /* four letters */
	searchPortion = NULL;

	while(numNodes(lists->fourLetterHead)>0) {
		/* printf("\nCurrent Progress:   %s\n", solution); */
		randomLocation = rand()%PERMUTATION_LENGTH;

		randomLetterIndex = rand()%numNodes(lists->fourLetterHead);
		strcpy(randomLetter,get_index(randomLetterIndex, lists->fourLetterHead));
		delete_index(randomLetterIndex, &(lists->fourLetterHead));
		/* printf("Searching for: %s / %c\n", randomLetter, lookupFromMorse(randomLetter)); */

		searchPortion = solution+randomLocation;

		foundLocation = strstr(searchPortion, randomLetter);
		if(foundLocation == NULL) {
			/* printf("Not found in searchPortion, trying whole alphabet\n"); */
			foundLocation = strstr(solution, randomLetter);
			if(foundLocation == NULL) { /* exhausted possibilities, need to start over */
				/* printf("Failed, starting over.\n"); */
				free(randomLetter);
				free(solution);
				return NULL;
			} else {
				*foundLocation = lookupFromMorse(randomLetter);
				for(j=1;j<lengthOfMorse;j++) {
					*(foundLocation+j) = ' ';
				}
			}
		} else {
			*foundLocation = lookupFromMorse(randomLetter);
			for(j=1;j<lengthOfMorse;j++) {
				*(foundLocation+j) = ' ';
			}
		}

	}
	free(randomLetter);
	return solution;
}

int main() {
	char* random_alphabet; /* contains output from generate_random_permutation() */
	char* smorse_alphabet; /* smorse version of random_alphabet */
	char* solution;        /* will contain the alphabet that is solved from the random smorse alphabet. */
	int decodeAttempts = 0;

	struct LetterLists *lists;

	srand(time(NULL));
	random_alphabet = generate_random_permutation();
	smorse_alphabet = smorse(random_alphabet);
	printf("%s\n", random_alphabet);
	printf("%s\n", smorse_alphabet);

	lists = malloc(sizeof(struct LetterLists));
	lists->fourLetterHead = NULL;
	lists->threeLetterHead = NULL;
	lists->twoLetterHead = NULL;
	lists->oneLetterHead = NULL;
	generateLists(lists);

	/* keep trying until successful */
	solution = NULL;
	while(solution == NULL) {
		decodeAttempts++;
		solution = decodeSmorse(smorse_alphabet, lists);
		generateLists(lists);
	}

	printf("Decode attempts:    %d\n", decodeAttempts);
	printf("Original alphabet:  %s\n", random_alphabet);
	printf("Original:           %s\n", smorse_alphabet);
	printf("Completed solution: %s\n", solution);

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


