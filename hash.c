#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ITERATION_COUNT 1

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
  char* str = calloc(sizeof(char), length + 1);
  memset(str, '\0', sizeof(char) * (length + 1));
  for(int i = 0;;i++) {
    int tmp = i;
    for(int j = 0;j < length;j++) {
      str[j] = letters[tmp % lettersLength];
      tmp /= lettersLength;
    }
    if(tmp > 0)
      // This indicates that we tried all the possibilities.
      return NULL;
    if(hash(str, length) == target)
      return str;
  }
}

int main() {
  setup();

  // Does hash work?  Should be 680131659347.
  long hashed = hash("leepadg", 7);
  if(hashed != 680131659347L)
    printf("%ld should be 680131659347\n", hashed);
  else
    printf("Successful hash.\n");

  // Does unhash work?  Should be "leepadg".
  char* unhashed = unhash(680131659347L, 7);
  if(strcmp(unhashed, "leepadg"))
    printf("%s should be leepadg\n", unhashed);
  else
    printf("Successful unhash.\n");

  // Start timing
  clock_t cstart = clock();

  for(int i = 0;i < ITERATION_COUNT;i++)
    unhash(680131659347L, 7);

  // Print total time
  printf("%.3f seconds\n", ((double)clock() - (double)cstart) / ITERATION_COUNT * 1.0e-6);
}
