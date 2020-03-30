#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"


int main() {
    setvbuf(stdout,_IONBF,0,0);


	FILE* flagfile = fopen("flag.txt","r");
	char flag[24];
	if(flagfile != NULL) {
		fgets(flag, 25, flagfile);
	}
	while(1) {
		printf("Echo as a service (EaaS)\n");
		char input[24];
		gets(input);
		printf(input);
		printf("\n");
	}
}
