#include "permutation_generator.h"
#include "smorse.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	char* random_alphabet;
	char* smorse_alphabet;
	random_alphabet = generate_random_permutation();
	smorse_alphabet = smorse(random_alphabet);
	printf("%s\n", random_alphabet);
	printf("%s\n", smorse_alphabet);
	free(random_alphabet);
	free(smorse_alphabet);
	return 0;
}
