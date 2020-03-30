#include <stdio.h>
#include <string.h>
#include <unistd.h> 

int subprocess(const char *cmd, int* to, int* from) {
    int input[2];
    int output[2];

    pipe(input);
    pipe(output);

    if(fork() == 0) {
        close(input[1]);
        dup2(input[0], 0);
        close(output[0]);
        dup2(output[1], 1);
        execl("/bin/sh", "sh", "-c", cmd, NULL);
    }
    *to = input[1];
    *from = output[0];
    close(output[1]);
    return 0; 
}

void gets_fd(char* buf, int fd) {
	int saved_stdin = dup(0);
    dup2(fd, 0);
    gets(buf);
    dup2(saved_stdin, 0);
}

void gunzip() {
    int to;
    int from;
    subprocess("gunzip", &to, &from);
    char filebuf[512];
    memset(filebuf,0,512);
    int length = read(0, filebuf, 512);
    write(to, filebuf, length);
    close(to);

    char buf[512];
    memset(buf, 0, 512);
    gets_fd(&buf, from);
    fwrite(buf, 1, 512, stdout);
}

int main() {
	gunzip();
    return 0;
}
