#include <ctime>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <map>
#include <string.h>
#include "server.h"

#define PASSWORD_LEN 50
#define USERNAME_LEN 32
#define MESSAGE_LEN 50

User::User(char* user){
    strcpy(username,user);
    strcpy(msg,"No Queries Submitted");
}

bool cmp_str::operator()(char const *a, char const *b)
{
    std::cout << "Comparing " << a << " to " << b << std::endl;
    return (strcmp(a,b) < 0);
}

std::map<char*, User*, cmp_str> current_users;

void encrypt(char* key, char* message){
    char xored_value;
    int message_length = strlen(message);
    for( int i = 0; i < message_length; i++){
        message[i] = (char) (message[i] ^ key[i%strlen(key)]);
    }
}

void decrypt(char* key, char* message){
    encrypt(key,message);
}

char* getPassword(char* filename){
    char* password = (char*) malloc(50);
    FILE *fptr = fopen(filename,"r");
    fgets(password,50,fptr);
    fclose(fptr);
    std::cout << "password: " << password << std::endl;
    return password;
}

bool isValidUsername(char* username){
    std::cout << "Length: " << (strlen(username) < USERNAME_LEN) << std::endl;
    std::cout << "flag: " << (strstr(username,"flag") == NULL) << std::endl;
    std::cout << "current user: " << (current_users.find(username) != current_users.end()) << std::endl;
    return strlen(username) < USERNAME_LEN && strstr(username,"flag") == NULL && current_users.find(username) != current_users.end();
}

char* login(char* id, char* name, char* password){
    char username[USERNAME_LEN];
    char* returnVal = (char*) malloc(100);
    strncpy(username,id,USERNAME_LEN);
    strncat(username,name,USERNAME_LEN);
    if (strstr(username,"flag") != NULL){
        strcpy(returnVal,"Invalid username.");
        std::cout << "Invalid user: " << username << std::endl;
        return returnVal;
    }
    std::map<char*, User*>::iterator it = current_users.find(username);
    if (it == current_users.end()){
        char* new_username = (char*) malloc(USERNAME_LEN);
        strcpy(new_username,username);
        current_users[new_username] = new User(new_username);
        std::cout << "creating new user" << std::endl;
    }
    FILE* fptr = fopen(username,"w");
    fputs(password,fptr);
    fclose(fptr);
    snprintf(returnVal,100,"User %s logged in.",username);
    std::cout << "Logging in user: " << username << std::endl;
    return returnVal;
}

char* logout(char* id, char* name){
    char username[USERNAME_LEN];
    strncpy(username,id,USERNAME_LEN);
    strncat(username,name,USERNAME_LEN);
    if (isValidUsername(username)){
        std::map<char*, User*>::iterator it = current_users.find(username);
        delete it->second;
        free(it->first);
        current_users.erase(it);
        std::cout << "Logging out user: " << username << std::endl;
        return (char*) "Logged Out.";
    }
    std::cout << "Invalid user: " << username << std::endl;
    return (char*) "Invalid Username.";
}

char* sendEcho(char* id, char* name, char* message){
    char username[USERNAME_LEN];
    strncpy(username,id,USERNAME_LEN);
    strncat(username,name,USERNAME_LEN);
    if (isValidUsername(username)){
        char* key = getPassword(username);
        decrypt(key,message);
        free(key);
        strcpy(current_users[username]->msg,message);
        std::cout << "Message received: " << message << std::endl;
        return (char*) "Message Received.";
    }
    return (char*) "Invalid Username.";
}

char* receiveEcho(char* id, char* name){
    char username[USERNAME_LEN];
    char message[MESSAGE_LEN];
    char* return_message = (char*) malloc(MESSAGE_LEN);
    strncpy(username,id,USERNAME_LEN);
    strncat(username,name,USERNAME_LEN);
    if(!isValidUsername(username)){
        strcpy(return_message,"Invalid Username.");
        return return_message;
    }
    if (strlen(current_users.at(username)->msg) < MESSAGE_LEN){
        usleep(100000);
        strcpy(message,current_users.at(username)->msg);
    }
    else{
        strcpy(return_message,"Invalid message length!");
        return return_message;
    }
    char* key = getPassword(username);

    //this is where i use the key to xor "encrypt" the communication.
    //If they overflowed and read from flag.txt, all they have to do is undo the xor.
    std::cout << "Decrypted Message: " << message << std::endl;
    encrypt(key,message);
    free(key);
    strncpy(return_message,message,MESSAGE_LEN);
    return return_message;
}
