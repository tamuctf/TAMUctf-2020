#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 64

int main() {
  char temp[BUF_SIZE];
  char buf[BUF_SIZE];
  puts("Howdy! First floor.");
  fgets(buf, sizeof(buf), stdin);
  strcpy(temp, "howdy\n");
  if (strcmp(buf, temp)) {
    puts("How 2%er of you.");
    exit(1);
  }
  puts("Thanks and...");
  fgets(buf, sizeof(buf), stdin);
  strcpy(temp, "gig 'em\n");
  if (strcmp(buf, temp)) {
    puts("How 2%er of you.");
    exit(1);
  }
  strcpy(temp, "whoop\n");
  *((void **)buf) = malloc(sizeof(temp));
  memcpy(*((void **)buf), temp, sizeof(temp));
  puts("What's our secret way of knowing when another one of us is in a crowd?");
  fgets(buf, sizeof(buf), stdin);
  if (strcmp(*((char **)buf), temp)) {
    puts("Begone, 2%er!");
    exit(1);
  }
  FILE * fd = fopen("flag.txt", "r");
  fgets(buf, sizeof(buf), fd);
  puts(buf);
  fclose(fd);
}
