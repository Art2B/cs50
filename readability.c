#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int get_nb_words(string s);
int get_nb_letters(string s);
int get_nb_sentences(string s);
bool is_char_word_stop(char c);
bool is_char_sentence_stop(char c);

int main (void) {
  string text = get_string("Text: ");
  int nb_letters = get_nb_letters(text);
  int nb_sentences = get_nb_sentences(text);
  int nb_words = get_nb_words(text);

  float L = (nb_letters / (float) nb_words) * 100.0;
  float S = (nb_sentences / (float) nb_words) * 100.0;
  float index = 0.0588 * L - 0.296 * S - 15.8;

  if (index < 1)
  {
    printf("Before Grade 1\n");
  }
  else if (index >= 16)
  {
    printf("Grade 16+\n");
  }
  else
  {
    printf("Grade %i\n", (int)round(index));
  }
}

int get_nb_letters(string s)
{
  int letters = 0;

  for (int i=0; i<strlen(s); i++)
  {
    if (isalpha(s[i]))
    {
      letters++;
    }
  }

  return letters;
}

int get_nb_sentences(string s)
{
  int nb_sentences = 0;

  for (int i=0; i<strlen(s); i++)
  {
    if(is_char_sentence_stop(s[i]))
    {
      nb_sentences++;
    }
  }

  return nb_sentences;
}

int get_nb_words(string s)
{
  int nb_words = 0;
  int current = 0;

  while (current < strlen(s)) {
    if (!is_char_word_stop(s[current])) {
      nb_words++;
      current++;
    }

    current ++;
  }

  return nb_words;
}

bool is_char_word_stop(char c)
{
    return (c == 32 || is_char_sentence_stop(c)); 
}

bool is_char_sentence_stop(char c)
{
  return (c == 33 || c == 63 || c == 46 || c == 0); 
}
