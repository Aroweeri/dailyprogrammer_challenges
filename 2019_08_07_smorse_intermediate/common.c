const char* letters[] = {".-\0","-...\0","-.-.\0","-..\0",".\0","..-.\0","--.\0","....\0","..\0",
                         ".---\0","-.-\0",".-..\0","--\0","-.\0","---\0",".--.\0","--.-\0",".-.\0",
                         "...\0","-\0","..-\0","...-\0",".--\0","-..-\0","-.--\0","--..\0"};

const char fourLetters[]  = {'b','c','f','h','j','l','p','q','v','x','y','z'};
const char threeLetters[] = {'d','g','k','o','r','s','u','w'};
const char twoLetters[]   = {'a','i','m','n'};
const char oneLetters[]   = {'e','t'};

const char numFourLetters = sizeof(fourLetters)/sizeof(fourLetters[0]);
const char numThreeLetters = sizeof(threeLetters)/sizeof(fourLetters[0]);
const char numTwoLetters = sizeof(twoLetters)/sizeof(fourLetters[0]);
const char numOneLetters = sizeof(oneLetters)/sizeof(fourLetters[0]);
