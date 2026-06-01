#include <stdio.h>
#include <cs50.h>
#include <math.h>

int get_quotient(int n, int v);

int main (void) {
  int change_owed;
  int coin_number;

  do {
    change_owed = get_int("Change owed: ");
    if (change_owed <= 0) {
      printf("Change must be > 0");
    }
  } while(change_owed<= 0);

  int nb_25 = get_quotient(change_owed, 25);
  coin_number += nb_25;
  change_owed -= nb_25 * 25;

  int nb_10 = get_quotient(change_owed, 10);
  coin_number += nb_10;
  change_owed -= nb_10 * 10;

  int nb_5 = get_quotient(change_owed, 5);
  coin_number += nb_5;
  change_owed -= nb_5 * 5;

  int nb_1 = get_quotient(change_owed, 1);
  coin_number += nb_1;
  change_owed -= nb_1 * 1;

  printf("%d\n", coin_number);
}

int get_quotient(int n, int v) {
  return floor(n / (float) v);
}
