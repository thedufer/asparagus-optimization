#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ITERATION_COUNT 20

static char* letters = "acdegilmnoprstuw";
static int lettersLength = 16;

void setup() {
}

static long hash(char* str, int length) {
  long h = 7;
  for(int i = 0;i < length;i++) {
    h = h * 37 + str[i];
  }
  return h;
}

static char* unhash(long target, int length) {
  char* str = calloc(sizeof(char), length + 1);
  memset(str, 0, sizeof(char) * length);
  str[length] = '\0';
  while(1) {
    int i = 0;
    str[i]++;
    while(str[i] == lettersLength) {
      str[i] = 0;
      i++;
      str[i]++;
    }
    if(hash(str, length) == target) {
      for(int j = 0;j < length;j++) {
        str[j] = letters[str[j]];
      }
      return str;
    }
  }
}

int main() {
  setup();

  // Does hash work?  Should be 680131659347.
  // Input is now "\x06\x03\x03\x0a\x00\x02\x04"
  long hashed = hash("\x06\x03\x03\x0a\x00\x02\x04", 7);
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
