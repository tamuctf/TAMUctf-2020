#include <stdio.h>

int main() {
  srand(0);
  for (int i = 0; i < 100; i++) {
    printf("%d\n", rand() % 100000 + 1);
  }
}
