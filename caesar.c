#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

string caesar_encrypt(string s, int k);
string caesar_decrypt(string s, int k);
int parse_number(string s);

int main (int argc, string argv[])
{
  int parsed_number = argc == 2 ? parse_number(argv[1]) : -1;

  if (parsed_number < 0)
  {
    printf("Usage: ./caesar key\n");
    return 1;
  }

  int choice;
  do {
    choice = get_int("Do you want to\n1. Encrypt\n2. Decrypt\n ?");
    printf("%d\n", choice);
  } while (choice != 1 && choice != 2);

  if (choice == 1)
  {
    string plain_text = get_string("Plain text:  ");
    string cypher_text = caesar_encrypt(plain_text, parsed_number);

    printf("Cypher text: %s\n", cypher_text);
  }
  else
  {
    string cypher_text = get_string("Cypher text: ");
    string plain_text = caesar_decrypt(cypher_text, parsed_number);

    printf("Plain text: %s\n", plain_text);
  }

  return 0;
}

string caesar_encrypt(string s, int k)
{
  int shift = k % 26;

  for(int i=0; i<strlen(s); i++)
  {
    // Handle latin uppercase
    if (s[i] >= 65 && s[i] <= 90)
    {
      s[i] = (((s[i] - 65) + shift) % 26) + 65;
    }
    // Handle latin lowercase
    else if (s[i] >= 97 && s[i] <= 122)
    {
      s[i] = (((s[i] - 97) + shift) % 26) + 97;
    }
  }

  return s;
}

string caesar_decrypt(string s, int k)
{
  int shift = k % 26;

  for(int i=0; i<strlen(s); i++)
  {
    // Handle latin uppercase
    if (s[i] >= 65 && s[i] <= 90)
    {
      s[i] = (((s[i] - 65) - shift + 26) % 26) + 65;
    }
    // Handle latin lowercase
    else if (s[i] >= 97 && s[i] <= 122)
    {
      s[i] = (((s[i] - 97) - shift + 26) % 26) + 97;
    }
  }

  return s;
}

int parse_number(string s)
{
  int n = 0;
  int s_length = strlen(s);

  for (int i=0; i<s_length; i++)
  {
    if (s[i] < 48 || s[i] > 57)
    {
      return -1;
    }

    n += (s[i] - 48) * pow(10, s_length - i - 1);
  }

  return n;
}
