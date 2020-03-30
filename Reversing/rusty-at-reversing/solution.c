#include "stdio.h"

void decrypt(char *flag) {
    char temp;
    char local_9 = 0xe4;
    for (int local_8 = 0; local_8 < 28; local_8++) {
        temp = flag[local_8];
        flag[local_8] = local_9 ^ flag[local_8];
        local_9 = temp;
    }
}

int main() {
    char flag [28];

    flag[0] = 0x83;
    flag[1] = 0xea;
    flag[2] = 0x8d;
    flag[3] = 0xe8;
    flag[4] = 0x85;
    flag[5] = 0xfe;
    flag[6] = 0x93;
    flag[7] = 0xe1;
    flag[8] = 0xbe;
    flag[9] = 0xcd;
    flag[10] = 0xb9;
    flag[11] = 0xd8;
    flag[12] = 0xaa;
    flag[13] = 0xc1;
    flag[14] = 0x9e;
    flag[15] = 0xf7;
    flag[16] = 0xa8;
    flag[17] = 0xce;
    flag[18] = 0xab;
    flag[19] = 0xce;
    flag[20] = 0xa2;
    flag[21] = 0xfd;
    flag[22] = 0x8f;
    flag[23] = 0xfa;
    flag[24] = 0x89;
    flag[25] = 0xfd;
    flag[26] = 0x84;
    flag[27] = 0xf9;

    decrypt(&flag);
    printf("%.28s\n", flag);
}
