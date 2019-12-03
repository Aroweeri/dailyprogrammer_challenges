#include "permutation_generator.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	char* random_alphabet;
	random_alphabet = generate_random_permutation();
	printf("%s\n", random_alphabet);
	free(random_alphabet);
	return 0;
}
