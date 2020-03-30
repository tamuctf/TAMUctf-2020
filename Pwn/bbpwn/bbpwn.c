#include <stdio.h>

void read_flag(){
	FILE *fptr;
	fptr = fopen("flag.txt","r");
	if (fptr == NULL){
		printf("File Error: flag.txt does not exist.");
		fflush(stdout);
		exit(0);
	}
	char flag[50];
	fgets(flag,50,fptr);
	printf("Congratulations. Your string is not lame. Here you go: %s\n",flag);
	fflush(stdout);
}

int main(){
	struct {
		char buf[32];
		int hello;
	} locals;
	locals.hello = 0;
	printf("Enter a string: ");
	fflush(stdout);
	gets(locals.buf);
	if (locals.hello == 0x1337beef){
		read_flag();
	}
	else {
		printf("\nThe string \"%s\" is lame.\n",locals.buf);
		fflush(stdout);
	}
}
