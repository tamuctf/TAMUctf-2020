#include "stdio.h"
#include "stdlib.h"


int main() {
    system("echo Base64 is an encoding that represents binary data in ASCII string format.  ");
    printf("Each number from 0 to 63 is mapped to an ASCII character.  For example, 'z' is %ld\n", a64l("z"));
    printf("Base64 Decoder: Powered by a64l (0x%x)\n", a64l);
    printf("%s", "Enter your name!  \n");
    fflush(stdout);
    char name[32];
    fgets(name, sizeof(name), stdin);
    printf("Welcome, ");
    printf(name);
    printf("\n");
    fflush(stdout);
    while (1) {
        printf("Please enter input to be decoded: \n");
        char input[256];
        fgets(input, sizeof(input), stdin);
        long out = a64l(input);
        printf("%d\n", out);
        fflush(stdout);
    }
    return 0;
}