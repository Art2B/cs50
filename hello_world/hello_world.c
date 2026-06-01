#include <cs50.h>
#include <stdio.h>

int main(void) {
  string answer = get_string("What's your name cutie? ");
  printf("hello, %s. Welcome to the C world.\n", answer);
}
