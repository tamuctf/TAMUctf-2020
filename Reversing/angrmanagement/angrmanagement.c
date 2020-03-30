#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include <stdbool.h>
#include <math.h>


int intify(double a) {
  int newint = a;
  return a;
}

bool check_len(char* string) {
  return strlen(string) == 32;
}

bool check_0(char* string) { return (string[15] != 'h') && (string[25] != '|') && (string[27] >= 63); }
bool check_1(char* string) { return ((string[17] * 16 % 13) == 0) && (string[30] <= 96) && (string[0] >= 38); }
bool check_2(char* string) { return (string[4] != '{') && (string[17] <= 115) && ((string[23] * 65 % 89) == 19); }
bool check_3(char* string) { return (string[28] <= 105) && (string[18] >= 37) && (string[0] != '7'); }
bool check_4(char* string) { return (string[28] <= 75) && (string[18] >= 37) && (string[19] <= 92); }
bool check_5(char* string) { return (string[20] <= 100) && (string[25] >= 34) && (string[8] <= 92); }
bool check_6(char* string) { return (string[24] != '{') && ((string[9] * 68 % 74) == 46) && ((string[26] * 69 % 42) == 27); }
bool check_7(char* string) { return (string[27] != ':') && (string[27] != '8') && ((string[19] * 20 % 95) == 65); }
bool check_8(char* string) { return (string[12] != 'e') && ((string[10] * 58 % 63) == 9) && (string[1] <= 42); }
bool check_9(char* string) { return (string[14] != ',') && (string[15] <= 99) && (string[29] <= 72); }
bool check_10(char* string) { return (string[21] <= 80) && (string[22] <= 123) && ((string[16] * 69 % 92) == 0); }
bool check_11(char* string) { return ((string[7] * 82 % 81) == 28) && ((string[22] * 77 % 75) == 21) && (string[29] <= 79); }
bool check_12(char* string) { return (string[18] != 'C') && (string[3] != '|') && (string[14] <= 91); }
bool check_13(char* string) { return (string[16] != 'h') && ((string[12] * 7 % 81) == 47) && (string[11] <= 69); }
bool check_14(char* string) { return (string[10] <= 59) && (string[10] != 'R') && ((string[29] * 64 % 73) == 72); }
bool check_15(char* string) { return (string[5] <= 120) && (string[8] != 'o') && (string[1] >= 34); }
bool check_16(char* string) { return ((string[8] * 91 % 93) == 18) && (string[20] != 'K') && (string[6] >= 89); }
bool check_17(char* string) { return (string[2] <= 95) && (string[6] <= 126) && (string[21] <= 64); }
bool check_18(char* string) { return ((string[7] * 85 % 19) == 12) && (string[30] >= 40) && (string[16] != 'B'); }
bool check_19(char* string) { return ((string[19] * 21 % 53) == 40) && ((string[9] * 33 % 18) == 15) && (string[24] <= 105); }
bool check_20(char* string) { return (string[30] >= 33) && ((string[25] * 45 % 89) == 23) && ((string[9] * 36 % 37) == 20); }
bool check_21(char* string) { return (string[23] != 'Z') && ((string[1] * 21 % 27) == 6) && ((string[5] * 68 % 34) == 0); }
bool check_22(char* string) { return ((string[11] * 31 % 48) == 44) && ((string[7] * 28 % 72) == 28) && (string[4] >= 37); }
bool check_23(char* string) { return (string[13] != 'Q') && (string[6] != '2') && ((string[2] * 74 % 90) == 70); }
bool check_24(char* string) { return (string[23] != 'I') && (string[31] != '^') && (string[20] >= 47); }
bool check_25(char* string) { return (string[17] >= 90) && (string[2] >= 67) && ((string[13] * 47 % 44) == 18); }
bool check_26(char* string) { return (string[15] >= 69) && (string[12] != 'w') && ((string[5] * 87 % 71) == 0); }
bool check_27(char* string) { return (string[22] <= 126) && (string[31] >= 103) && (string[21] <= 104); }
bool check_28(char* string) { return ((string[0] * 57 % 30) == 0) && (string[28] >= 34) && (string[14] >= 41); }
bool check_29(char* string) { return ((string[4] * 79 % 15) == 11) && ((string[3] * 98 % 35) == 0) && (string[26] != '?'); }
bool check_30(char* string) { return (string[3] >= 35) && (string[13] != 'l') && ((string[11] * 61 % 86) == 20); }
bool check_31(char* string) { return (string[26] >= 36) && (string[24] >= 72) && ((string[31] * 53 % 59) == 13); }

int main() {
  setvbuf(stdout,_IONBF,0,0);



  char input[33];
  printf("Enter the password:\n");
  fgets(input, 33, stdin);
  bool correct = check_len(input) && check_0(input) && check_1(input) && check_2(input) && check_3(input) && check_4(input) && check_5(input) && check_6(input) && check_7(input) && check_8(input) && check_9(input) && check_10(input) && check_11(input) && check_12(input) && check_13(input) && check_14(input) && check_15(input) && check_16(input) && check_17(input) && check_18(input) && check_19(input) && check_20(input) && check_21(input) && check_22(input) && check_23(input) && check_24(input) && check_25(input) && check_26(input) && check_27(input) && check_28(input) && check_29(input) && check_30(input) && check_31(input);

  if(correct) {
    printf("Correct!\n");
    FILE* flagfile = fopen("flag.txt","r");
    char flag[25];
    if(flagfile != NULL) {
      fgets(flag, 25, flagfile);
      printf("%s", flag);
    }
  } else {
    printf("Incorrect.\n");
  }

}
