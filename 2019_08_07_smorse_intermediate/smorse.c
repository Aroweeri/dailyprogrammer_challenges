#include <stdlib.h>
#include <string.h>
#include "smorse.h"
#include "common.h"

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
