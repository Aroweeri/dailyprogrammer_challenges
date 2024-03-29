#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CHUNK 16
#define SMORSECHUNK 100

char *letters[] = {".-\0","-...\0","-.-.\0","-..\0",".\0","..-.\0","--.\0","....\0","..\0",
                   ".---\0","-.-\0",".-..\0","--\0","-.\0","---\0",".--.\0","--.-\0",".-.\0",
                   "...\0","-\0","..-\0","...-\0",".--\0","-..-\0","-.--\0","--..\0"};

char* smorse(char* word);
void bonus1(char** sortedSmorse, char** allSmorse, int totalWords);
void bonus2(char** allSmorse, char** words, int totalWords);
void bonus3(char** words, char** allSmorse, int totalWords);
void bonus4(char** words, char** allSmorse, int totalWords);
void countDotsAndDashes(int* totalDots, int* totalDashes, int totalWords, char** allSmorse);
char* reverse (char* word);
char* readWord(FILE* fp);
int cmpstring(void const *p1, void const *p2);

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

void bonus1(char** sortedSmorse, char** allSmorse, int totalWords) {
	int i;
	int hits;
	int bestHits;
	int best;
	/* As long as the value doesn't change (sorted list) we're counting occurences of that word. */
	for(i=1;i<totalWords;i++) {
		if(strcmp(sortedSmorse[i], sortedSmorse[i-1]) == 0) {
			hits++;
		} else {
			hits = 1;
		}
		if(hits > bestHits) {
			best = i;
			bestHits = hits;
		}
	}
	printf("Best: %s with %d hits.\n", allSmorse[best], bestHits);
}

void bonus2(char** allSmorse, char** words, int totalWords) {
	int dashCount = 0;
	int bestDashCount = 0;
	int i;
	int j;
	for(i=0;i<totalWords;i++) {
		dashCount = 0;
		bestDashCount = 0;
		if(strlen(allSmorse[i]) < 15) {
			continue;
		}
		for(j=0;j<strlen(allSmorse[i]);j++) {
			if(allSmorse[i][j] == '-') {
				dashCount++;
			} else {
				if(dashCount > bestDashCount) {
					bestDashCount = dashCount;
				}
				dashCount = 0;
			}
		}
		if(bestDashCount >13 ) {
			printf("%s: %s: %d\n", words[i], allSmorse[i], bestDashCount);
		}
	}
}

void bonus3(char** words, char** allSmorse, int totalWords) {
	int i;
	int j;
	int dotCount = 0;
	int dashCount = 0;
	for(i=0;i<totalWords;i++) {
		if(strlen(words[i]) != 21) continue;
		dotCount=0;
		dashCount=0;
		for(j=0;j<strlen(allSmorse[i]);j++) {
			if(allSmorse[i][j] == '.')
				dotCount++;
			else
				dashCount++;
		}
		if(dotCount == dashCount) {
			printf("%s: %s\n", words[i], allSmorse[i]);
		}
	}
}

void bonus4(char** words, char** allSmorse, int totalWords) {
	int i;
	char* reversed;
	for(i=0;i<totalWords;i++) {
		if(strlen(words[i]) != 13) continue;
		reversed = reverse(allSmorse[i]);
		if(strcmp(reversed, allSmorse[i]) == 0) {
			printf("Found: %s\n%s\n%s\n", words[i], reversed, allSmorse[i]);
		}
		free(reversed);
		reversed = NULL;
	}
}

void countDotsAndDashes(int* totalDots, int* totalDashes, int totalWords, char** allSmorse) {
	int i;
	int j;
	char* smorseWord;
	for(i=0;i<totalWords;i++) {
		smorseWord = allSmorse[i];
		for(j=0;j<strlen(smorseWord);j++) {
			if(smorseWord[j] == '.') (*totalDots)++;
			else if(smorseWord[j] == '-') (*totalDashes)++;
			else printf("Something else.\n");
		}
	}
}

char* reverse (char* word) {
	char *r = calloc(1, sizeof(char)*(strlen(word)+1));
	int i;
	int j = 0;
	for(i=strlen(word)-1;i>=0;i--) {
		r[j] = word[i];
		j++;
	}
	r[j]='\0';
	return r;
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
			for(i=location+1;i<location+CHUNK;i++) {
				word[i] = 0;
			}
			letter = &(word[location-1]); /* get new address */

		}
		if(*letter == EOF) {
			free(word);
			return NULL;
		}
		if(*letter == '\n') {
			*letter = '\0'; /*delete newline and write terminator*/
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
	int totalWords = 0;
	char** words = calloc(1, sizeof(char*)*CHUNK);
	char** allSmorse = NULL;
	char** sortedSmorse = NULL;
	char* word = NULL;
	char done = 0;
	int i = 0;
	int totalDots = 0;
	int totalDashes = 0;

	/* read all words from file */
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
	totalWords = currentWord;

	/* create list of all words converted to smorse */
	allSmorse = malloc(sizeof(char*)*totalWords);
	for(i=0;i<totalWords;i++) {
		allSmorse[i] = smorse(words[i]);
	}

	/* sort smorse list */
	sortedSmorse = calloc(totalWords, sizeof(char*));
	for(i=0;i<totalWords;i++) {
		sortedSmorse[i] = malloc(sizeof(char*)*strlen(allSmorse[i]));
		strcpy(sortedSmorse[i], allSmorse[i]);
	}
	qsort(sortedSmorse, totalWords, sizeof(char*), cmpstring);

	countDotsAndDashes(&totalDots, &totalDashes, totalWords, allSmorse);
	printf("Dots: %d\n", totalDots);
	printf("Dashes: %d\n", totalDashes);

	bonus1(sortedSmorse, allSmorse, totalWords);
	bonus2(allSmorse, words, totalWords);
	bonus3(words, allSmorse, totalWords);
	bonus4(words, allSmorse, totalWords);

	/* free memory */
	for(i=0;i<totalWords;i++) {
		free(words[i]);
	}
	for(i=0;i<totalWords;i++) {
		free(sortedSmorse[i]);
	}
	for(i=0;i<totalWords;i++) {
		free(allSmorse[i]);
	}
	free(allSmorse);
	free(sortedSmorse);
	free(words);
	fclose(fp);

	return 0;
}
