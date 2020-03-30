
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* deobfuscate(char* text) {
	int len = strlen(text);
	for(int i = 0; i < len; i += 2) {
		char temp = text[i];
		text[i] = text[i+1];
		text[i+1] = temp;
	}
	for(int i = 0; i < len; i += 1) {
		text[i] -= 15;
	}
	for(int i = 0; i < len; i += 1) {
		text[i] ^= 43;
	}
	for(int i = len; i > 0; i -= 1) {
		text[i-1] ^= text[i % len];
	}

	return text;
}

int main() {
	char* flag = malloc(26);
	strcpy(flag, "4428/L9~x:x{\x1fL\x83T()\x84\x84x\x85r/gv");
	deobfuscate(flag);
	char* input = malloc(27);
	printf("%s", "Enter password: ");
	fgets(input, 27, stdin);
	if(strcmp(flag, input) == 0) {
		printf("Correct!  That's the password!\n");
	} else {
		printf("Sorry, that isn't the right password.\n");
	}
}