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

	/* bonus 2 */
	int dashCount = 0;
	int bestDashCount = 0;

	/* bonus 3 vars */
	int dotCount = 0;

	/* bonus 4 */
	char* reversed;

	/* bonus 5 */
	char** bonus5List;
	int bonus5ListCounter;
	char comparePattern[13];
	char bonus5ListFound;

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
	qsort(sortedSmorse, currentWord, sizeof(char*), cmpstring);
	/*qsort(allSmorse, currentWord, sizeof(char*), cmpstring);*/


	/* start count dots and dashes */
	for(i=0;i<currentWord;i++) {
		smorseWord = allSmorse[i];
		for(j=0;j<strlen(smorseWord);j++) {
			if(smorseWord[j] == '.') totalDots++;
			else if(smorseWord[j] == '-') totalDashes++;
			else printf("Something else.\n");
		}
	}
	printf("Dots: %d\n", totalDots);
	printf("Dashes: %d\n", totalDashes);
	/* end */

	/* start bonus 1 */
	for(i=1;i<currentWord;i++) {
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
	/* end */

	/* start bonus 2 */
	for(i=0;i<currentWord;i++) {
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
	/* end */

	/* start bonus 3 */
	for(i=0;i<currentWord;i++) {
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
	
	/* end */

	/* start bonus 4 */
	for(i=0;i<currentWord;i++) {
		if(strlen(words[i]) != 13) continue;
		reversed = reverse(allSmorse[i]);
		if(strcmp(reversed, allSmorse[i]) == 0) {
			printf("Found: %s\n%s\n%s\n", words[i], reversed, allSmorse[i]);
		}
		free(reversed);
		reversed = NULL;
	}
	/* end */

	/* start bonus 5 */

	/* make list of all smorses that have 13 characters */
	bonus5List = calloc(currentWord, sizeof(char*));
	bonus5ListCounter = 0;
	for(i=0;i<currentWord;i++) {
		if(strlen(allSmorse[i]) == 13) {
			bonus5List[bonus5ListCounter] = allSmorse[i];
			bonus5ListCounter++;
		}
	}
	bonus5List = realloc(bonus5List, sizeof(char*)*(bonus5ListCounter-1));

	for(i=0;i<8191;i++) {
		bonus5ListFound=0;
		comparePattern[0] =  ((i & 0x0001) == 0x0001) ? '.' : '-';
		comparePattern[1] =  ((i & 0x0002) == 0x0002) ? '.' : '-';
		comparePattern[2] =  ((i & 0x0004) == 0x0004) ? '.' : '-';
		comparePattern[3] =  ((i & 0x0008) == 0x0008) ? '.' : '-';
		comparePattern[4] =  ((i & 0x0010) == 0x0010) ? '.' : '-';
		comparePattern[5] =  ((i & 0x0020) == 0x0020) ? '.' : '-';
		comparePattern[6] =  ((i & 0x0040) == 0x0040) ? '.' : '-';
		comparePattern[7] =  ((i & 0x0080) == 0x0080) ? '.' : '-';
		comparePattern[8] =  ((i & 0x0100) == 0x0100) ? '.' : '-';
		comparePattern[9] =  ((i & 0x0200) == 0x0200) ? '.' : '-';
		comparePattern[10] = ((i & 0x0400) == 0x0400) ? '.' : '-';
		comparePattern[11] = ((i & 0x0800) == 0x0800) ? '.' : '-';
		comparePattern[12] = ((i & 0x1000) == 0x1000) ? '.' : '-';
		printf("%d\n", bonus5ListCounter);
		for(j=0;j<bonus5ListCounter;j++) {
			/*printf("%s\n", bonus5List[j]);
			printf("%s\n", comparePattern);*/
			if(strcmp(comparePattern, bonus5List[j]) == 0) {
				bonus5ListFound=1;
			}
		}
		if(bonus5ListFound == 1) {
			printf("%s\n", comparePattern);
		}
	}
	free(bonus5List);

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
