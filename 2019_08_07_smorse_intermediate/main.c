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

struct Node** findHeadToUse(struct LetterLists* lists) {
	struct Node** returnThis = NULL;
	if(numNodes(lists->fourLetterHead) > 0) {
		returnThis = &(lists->fourLetterHead);
	}
	else if(numNodes(lists->threeLetterHead) > 0) {
		returnThis = &(lists->threeLetterHead);
	}
	else if(numNodes(lists->twoLetterHead) > 0) {
		returnThis = &(lists->twoLetterHead);
	}
	else {
		returnThis = &(lists->oneLetterHead);
	}
	return returnThis;
}

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
	struct Node** headToUse = NULL;

	int j;
	int lengthOfMorse = 0;
	int remainingNodes = 0;


	solution = malloc(sizeof(char)*PERMUTATION_LENGTH+1); /* +1 for null */
	strcpy(solution, smorse_alphabet);
	randomLetter = malloc(sizeof(char)*5); /* four letters */
	searchPortion = NULL;

	remainingNodes+=numNodes(lists->fourLetterHead);
	remainingNodes+=numNodes(lists->threeLetterHead);
	remainingNodes+=numNodes(lists->twoLetterHead);
	remainingNodes+=numNodes(lists->oneLetterHead);


	while(remainingNodes > 0) {
		/*printf("Remaining Nodes: %d\n", remainingNodes);*/
		/*printf("\nCurrent Progress:   %s\n", solution);*/
		randomLocation = rand()%PERMUTATION_LENGTH;
		headToUse = findHeadToUse(lists);
		/*headToUse = &(lists->fourLetterHead);*/

		if(*headToUse == lists->fourLetterHead) {
			lengthOfMorse = 4;
		} else if(*headToUse == lists->threeLetterHead) {
			lengthOfMorse = 3;
		} else if(*headToUse == lists->twoLetterHead) {
			lengthOfMorse = 2;
		} else if(*headToUse == lists->oneLetterHead) {
			lengthOfMorse = 1;
		}

		randomLetterIndex = rand()%numNodes(*headToUse);
		strcpy(randomLetter,get_index(randomLetterIndex, *headToUse));
		/*printf("search for: %s\n", randomLetter);*/
		delete_index(randomLetterIndex, headToUse);
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
				remainingNodes--;
			}
		} else {
			*foundLocation = lookupFromMorse(randomLetter);
			for(j=1;j<lengthOfMorse;j++) {
				*(foundLocation+j) = ' ';
			}
			remainingNodes--;
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


