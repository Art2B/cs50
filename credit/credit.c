#include <cs50.h>
#include <math.h>
#include <stdio.h>

bool is_card_number_valid(long n);
string get_card_company(long n);
int get_digits_sum(int n);

int main (void) {
  long int cardNumber;

  do
  {
    cardNumber = get_long("Enter a valid card number: "); 
  }
  while (!is_card_number_valid(cardNumber));

  printf("%s\n", get_card_company(cardNumber));
}

bool is_card_number_valid(long n) {
  int counter = 1;
  int even_digits_sum = 0;
  int odd_digits_sum = 0;

  while(n > 0)
  {
    int s = n % 10;

    if (counter % 2 == 0)
    {
      even_digits_sum += get_digits_sum(s * 2);
    }
    else
    {
      odd_digits_sum += s;
    }

    n = n / 10;
    counter++;
  }

  if ((even_digits_sum + odd_digits_sum) % 10 == 0) {
    return true;
  }

  return false;
}

int get_digits_sum(int n) {
  int total = 0;

  while (n > 0) {
    total += n % 10;
    n = n / 10;
  }

  return total;
}

string get_card_company(long n) {
  int starting_digit_visa_short = n / (long) floor(pow(10, 13 - 1));
  int starting_digit_visa_long = n / (long) floor(pow(10, 16 - 1));
  int starting_digits_am = n / (long) floor(pow(10, 15 - 2));
  int starting_digits_mc = n / (long) floor(pow(10, 16 - 2));

  if (
      starting_digit_visa_long == 4 ||
      starting_digit_visa_short == 4
  )
  {
    return "VISA";
  }
  else if (
      starting_digits_am == 34 ||
      starting_digits_am == 37
  )
  {
    return "AMERICAN EXPRESS";
  }
  else if (
      starting_digits_mc >= 51 &&
      starting_digits_mc <= 55
  )
  {
    return "MASTERCARD";
  }

  return "INVALID";
}
