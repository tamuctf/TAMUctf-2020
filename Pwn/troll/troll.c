#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  setvbuf(stdout,_IONBF,0,0);

  time_t seed = time(NULL);
  int i, number, response;
  char name[32], flag[64];
  FILE *flagfile;
  
  printf("Who goes there?\n");

  gets(name);
  
  printf("Welcome to my challenge, %s. No one has ever succeeded before. Will you be the first?\n", name);

  srand(seed);
  for (i = 0; i < 100; i++) {
    number = rand() % 100000 + 1;
    printf("I am thinking of a number from 1-100000. What is it?\n");
    scanf("%d", &response);

    if (response == number) {
      printf("Impressive.\n");
    } else {
      printf("You have failed. Goodbye.\n");
      return 0;
    }
  }

  printf("You've guessed all of my numbers. Here is your reward.\n");

  flagfile = fopen("flag.txt","r");
  if(flagfile != NULL) {
    fgets(flag, 64, flagfile);
    printf("%s\n", flag);
  }

  printf("Goodbye.\n");
}
