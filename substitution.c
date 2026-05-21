#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int key_length = 26;

string substitution_encrypt(string s, char key[key_length]);
string substitution_decrypt(string s, char key[key_length]);
bool is_key_valid(string s);

int main (int argc, string argv[])
{
  if (argc != 2) {
    printf("Usage: ./substitution key\n");
    return 1;
  }

  string key = argv[1];
  if (strlen(key) != key_length) {
    printf("Usage ./substitution key\nKey must be key_length characters longs.\n");
    return 1;
  }

  if (!is_key_valid(key)) {
    printf("Key is invalid. Must be key_length unique alphabetic characters\n");
    return 1;
  }

  int choice;
  do {
    choice = get_int("Do you want to:\n1. Encrypt\n2. Decrypt\nChoice: ");
  } while(choice != 1 && choice != 2);

  if (choice == 1) {
    string plain_text = get_string("Plain text: ");
    string cypher_text = substitution_encrypt(plain_text, key);
    printf("Cypher text: %s\n", cypher_text);
  } else {
    string cypher_text = get_string("Cypher text: ");
    string plain_text = substitution_decrypt(cypher_text, key);
    printf("Plain text: %s\n", plain_text);
  }

  return 0;
}

string substitution_encrypt(string s, char key[key_length]) {
  for (int i=0; i<strlen(s); i++) {
    if (s[i] >= 65 && s[i] <= 90) {
      s[i] = toupper(key[s[i] - 65]);
    } else if (s[i] >= 97 && s[i] <= 122) {
      s[i] = tolower(key[s[i] - 97]);
    }
  }

  return s;
}

string substitution_decrypt(string s, char key[key_length]) {
  char reversed_keys[key_length];

  for (int i=0; i<key_length; i++) {
    reversed_keys[key[i] - 65] = i + 65;
  }

  for (int i=0; i<strlen(s); i++) {
    if (s[i] >= 65 && s[i] <= 90) {
      s[i] = toupper(reversed_keys[s[i] - 65]);
    } else if (s[i] >= 97 && s[i] <= 122) {
      s[i] = tolower(reversed_keys[s[i] - 97]);
    }
  }

  return s;
}

bool is_key_valid(string s) {
  // 351 is the result of the arithmetic serie from 1 to key_length
  int total = 351;
  int key_total;

  for(int i=0; i<strlen(s); i++) {
    if (s[i] >= 65 && s[i] <= 90) {
      key_total += s[i] - 65 + 1;
    }
    else if (s[i] >= 97 && s[i] <= 122) {
      key_total += s[i] - 97 + 1;
    }
  }

  return (total == key_total);
}
