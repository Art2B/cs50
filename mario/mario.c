#include <cs50.h>
#include <stdio.h>

int main(void) {
  int size;
  const int gap = 2;
  const int MIN = 1;
  const int MAX = 8;

  do  {
    size = get_int("What size should the pyramid be? ");
    if (size<MIN || size>MAX) {
      printf("The pyramid size should be between 1 and 8\n");
    }
  } while (size<MIN || size>MAX);

  for(int i=1; i<=size; i++) {
    for(int j=1; j<=size; j++) {
      if (j+i> size) {
        printf("#");
      } else {
        printf(" ");
      }
    }
    for(int j=0; j<gap; j++) {
      printf(" ");
    }
    for(int j=1; j<=size; j++) {
      if (j<=i) {
        printf("#");
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
}
