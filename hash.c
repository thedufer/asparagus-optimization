#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ITERATION_COUNT 20

static char* letters = "acdegilmnoprstuw";
static int lettersLength = 16;

void setup() {
}

int getPosition(char c) {
  for(int i = 0;i < lettersLength;i++) {
    if(c == letters[i])
      return i;
  }
  printf("Something has gone horribly wrong.\n");
  return -1;
}

long hash(char* str, int length) {
  long h = 7;
  for(int i = 0;i < length;i++) {
    h = h * 37 + getPosition(str[i]);
  }
  return h;
}

char* unhash(long target, int length) {
  return "";
}

int main() {
  setup();

  // Does hash work?  Should be 680131659347.
  long hashed = hash("leepadg", 7);
  if(hashed != 680131659347L)
    printf("%ld should be 680131659347\n", hashed);
  else
    printf("Succesful hash.\n");

  // Does unhash work?  Should be "leepadg".
  char* unhashed = unhash(680131659347L, 7);
  if(strcmp(unhashed, "leepadg"))
    printf("%s should be leepadg\n", unhashed);
  else
    printf("Succesful unhash.\n");

  // Start timing
  clock_t cstart = clock();

  for(int i = 0;i < ITERATION_COUNT;i++)
    unhash(680131659347L, 7);

  // Print total time
  printf("%.3f seconds\n", ((double)clock() - (double)cstart) / ITERATION_COUNT * 1.0e-6);
}
