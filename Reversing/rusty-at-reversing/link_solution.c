#include "stdio.h"

long * get_flag(long * param_1, char * param_2, size_t * param_3, long param_4, size_t param_5);

int main() {
    char flag[28];
    get_flag((long *) flag, NULL, NULL, 0, 0);
    printf("%.28s\n", flag);
}