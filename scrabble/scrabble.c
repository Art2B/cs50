#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string sanitize_input(string s);
int get_word_score(string s);
int get_char_score(char c);

int letter_score[26] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};

int main (void)
{
  string first = sanitize_input(get_string("Player 1:"));
  string second = sanitize_input(get_string("Player 2: "));

  int first_score = get_word_score(first);
  int second_score = get_word_score(second);

  if (first_score == second_score)
  {
    printf("Tie!\n");
  }
  else if (first_score > second_score)
  {
    printf("Player 1 wins!\n");
  }
  else {
    printf("Player 2 wins!\n");
  }
}

string sanitize_input(string s)
{
  for (int i=0, n=strlen(s); i<n; i++) {
    s[i] = tolower(s[i]);
  }

  return s;
}

int get_word_score(string s)
{
  int total = 0;

  for (int i=0, n=strlen(s); i<n; i++)
  {
    total += get_char_score(s[i]);
  }

  return total;
}

int get_char_score(char c)
{
  if (c >= 97 && c <= 122) {
    return letter_score[c - 97];
  }

  return 0;
}
