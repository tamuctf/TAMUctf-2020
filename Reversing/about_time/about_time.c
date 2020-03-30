#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<signal.h>
#include<unistd.h>
#define RANDBOOL (rand() % 2)

struct Decisions
{
	int value;
	char password[50];
} decision;

char flag[50];
char encrypted_flag[50];

void rot(char *string, int value){
	for(int x = 0; x < strlen(string); x = x + 3){
		if(string[x] >= 'a' && string[x] <= 'z'){
			string[x] = (((string[x]-'a')+13+value) % 26) + 'a';
		}
		if(string[x] >= 'A' && string[x] <= 'Z'){
			string[x] = (((string[x]-'A')+13+value) % 26) + 'A';
		}
	}
}

void shift(char *string, int value){
	char temp_pass[50];
	strncpy(temp_pass,string,50);
	int length = strlen(string);
	for(int x = 0; x < length; x++){
		string[x] = temp_pass[(x + value) % length];
	}
}

void add(char *string, int value){
	char temp;
	int length = strlen(string);
	for(int x = 0; x < length; x++){
		if(string[x] >= '0' && string[x] <= '9'){
			string[x] = string[x] + value;
		}
	}
}



void check_pass(char *pass, char *input){
	if(strcmp(pass,input) == 0){
		printf("Correct! Here you go: gigem{%s}\n",flag);
		fflush(stdout);
	}
	else{
		printf("Incorrect password! Try again.\n");
		fflush(stdout);
	}
}

void sigHandler(int sig_num){
	if(RANDBOOL) {
		flag[0] = '\0';
	}
	if(RANDBOOL) {
		decision.value = rand();
	}
	if(RANDBOOL) {
		decision.password[0] = '\0';
	}
	if(RANDBOOL) {
		encrypted_flag[0] = '\0';
	}
}

int main(){
	//signal handler
	signal(SIGALRM,sigHandler);
	alarm(5);

	//seed rand
	srand(time(0));

	//get time for decision value
	time_t start_time = time(NULL);
	struct tm *loc_time = localtime(&start_time);
	char time[5];
	char full_time[50];
	strftime(full_time,50,"%Y-%m-%dT%H:%M:%S%Z",loc_time);
	strftime(time,5,"%M",loc_time);
	decision.value = ((atoi(time) % 6) + 2);
	int value = decision.value;


	//get flag from file
	FILE *flag_file;
	if((flag_file = fopen("flag.txt","r")) != NULL){
		fgets(flag,50,flag_file);
		fclose(flag_file);
	} else {
		printf("Flag.txt not found. Exiting...\n");
		return 0;
	}
	for(int i = 0; i < strlen(flag); i++){
		if(flag[i] == '\n'){
			flag[i] = '\0';
		}
	}
	strncpy(encrypted_flag,flag,50);

	//setup function pointers
	void (*fun_ptr[])() = {rot,shift,add};

	//run encryption on flag
	(*fun_ptr[value % 3])(encrypted_flag,value);
	(*fun_ptr[(value + 1) % 3])(encrypted_flag,value);
	(*fun_ptr[(value + 2) % 3])(encrypted_flag,value);

	printf("%s> Encrypted password: %s\n",full_time,encrypted_flag);
	fflush(stdout);

	//get password from CLI user
	printf("Enter the password: ");
	fflush(stdout);
	fgets(decision.password,50,stdin);
	for(int i = 0; i < strlen(decision.password); i++){
		if(decision.password[i] == '\n'){
			decision.password[i] = '\0';
		}
	}

	//run encryption on input
	(*fun_ptr[value % 3])(decision.password,value);
	(*fun_ptr[(value + 1) % 3])(decision.password,value);
	(*fun_ptr[(value + 2) % 3])(decision.password,value);

	check_pass(encrypted_flag,decision.password);
	return 0;
}
