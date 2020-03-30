#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include <string>

class User{
	public:
        char username[32];
        char msg[100];

        User(char* user);
};

struct cmp_str
{
    bool operator()(char const *a, char const *b); 
};

extern std::map<char*, User*, cmp_str> current_users;

char* login(char* id, char* name, char* password);

char* logout(char* id, char* name);

char* sendEcho(char* id, char* name, char* message);

char* receiveEcho(char* id, char* name);

#endif
