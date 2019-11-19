#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CHUNK 16
#define SMORSECHUNK 100

/*char *letters[] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--",
                   "-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--",
                   "--.."};*/

char *letters[] = {".-\0","-...\0","-.-.\0","-..\0",".\0","..-.\0","--.\0","....\0","..\0",
                   ".---\0","-.-\0",".-..\0","--\0","-.\0","---\0",".--.\0","--.-\0",".-.\0",
                   "...\0","-\0","..-\0","...-\0",".--\0","-..-\0","-.--\0","--..\0"};

char* smorse(char* word) {
	int i;
	char* builder;

	builder = calloc(1, sizeof(char*)*strlen(word)*4);

	for(i=0;i<strlen(word);i++) {
		/* convert 'a' which is 97 in char to 0 to be used with letters array. */
		strcat(builder, letters[word[i]-97]); 
	}
	return builder;
}

char* readWord(FILE* fp) {
	int location = 0;
	char* letter = NULL;
	char* word = calloc(1, sizeof(char)*CHUNK);
	int i = 0;

	/* initialize memory to null */
	for(i=0;i<CHUNK;i++) {
		word[i] = 0;
	}

	while( 1 ) {
		letter = &(word[location]);
		*letter = fgetc(fp);
		location++;
		if((location % 16) == 0) {
			word = realloc(word, sizeof(char)*location+CHUNK);

			/* initialize new memory to NULL */
			for(i=location;i<location+CHUNK;i++) {
				word[i] = 0;
			}

			letter = &(word[location]);
		}
		if(*letter == EOF) {
			free(word);
			return NULL;
		}
		if(*letter == '\n') {
			word[location-1] = '\0'; /*delete newline and write terminator*/
			return word;
		}
	}
}

int cmpstring(void const *p1, void const *p2) {
	return strcmp(*(char**)p1, *(char**)p2);
}

int main() {
	FILE *fp = fopen("enable1.txt", "r");
	int currentWord = 0;
	char** words = calloc(1, sizeof(char*)*CHUNK);
	char** allSmorse = NULL;
	char** sortedSmorse = NULL;
	char* word = NULL;
	char done = 0;
	int i = 0;
	int j = 0;
	int hits = 1; /* there's always at least 1 instance of each smorse. */
	int bestHits = 0;
	char* smorseWord;
	int totalDots = 0;
	int totalDashes = 0;
	int best = 0;

	while (done == 0) {
		word = readWord(fp);
		if(word == NULL) {
			done = 1;
			continue;
		}
		words[currentWord] = word;
		currentWord++;
		if(currentWord % CHUNK == 0 && currentWord != 0) {
			words = realloc(words, (sizeof(char*)*currentWord+sizeof(char*)*CHUNK));
		}
	}

	allSmorse = malloc(sizeof(char*)*currentWord);
	for(i=0;i<currentWord;i++) {
		allSmorse[i] = smorse(words[i]);
	}
	sortedSmorse = calloc(currentWord, sizeof(char*));
	for(i=0;i<currentWord;i++) {
		sortedSmorse[i] = malloc(sizeof(char*)*strlen(allSmorse[i]));
		strcpy(sortedSmorse[i], allSmorse[i]);
	}
	/*qsort(sortedSmorse, currentWord, sizeof(char*), cmpstring);*/
	qsort(allSmorse, currentWord, sizeof(char*), cmpstring);


	/* start count dots and dashes */
	/*for(i=0;i<currentWord;i++) {
		smorseWord = smorse(words[i]);
		for(j=0;j<strlen(smorseWord);j++) {
			if(smorseWord[j] == '.') totalDots++;
			else if(smorseWord[j] == '-') totalDashes++;
			else printf("Something else.\n");
		}
	}
	printf("Dots: %d\n", totalDots);
	printf("Dashes: %d\n", totalDashes);*/
	/* end */

	/* start bonus 1 */
	/*for(i=1;i<currentWord;i++) {
		if(strcmp(allSmorse[i], allSmorse[i-1]) == 0) {
			hits++;
		} else {
			hits = 1;
		}
		if(hits > bestHits) {
			best = i;
			bestHits = hits;
		}
	}
	printf("Best: %s with %d hits.\n", allSmorse[best], bestHits);*/
	/* end */

	/* start bonus 2 */
	
	/* end */

	/* free memory */
	for(i=0;i<currentWord;i++) {
		free(words[i]);
	}
	for(i=0;i<currentWord;i++) {
		free(sortedSmorse[i]);
	}
	for(i=0;i<currentWord;i++) {
		free(allSmorse[i]);
	}
	free(allSmorse);
	free(sortedSmorse);
	free(words);
	fclose(fp);

	return 0;
}
