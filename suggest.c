#include "suggest.h"
#include <string.h>
#include <stdio.h>
#include "cs136-trace.h"
#include <assert.h>


/////////////////////////////////////////////////////////////////////////////
// do not modify this constants:
const int SUGGEST_MAX_STRLEN = 63;
/////////////////////////////////////////////////////////////////////////////

// strip(s) removes all whitespace in s
// note: as always, in this course whitespace is only ' ' and '\n'
// example: "shrink  me\nplease" => "shrinkmeplease"
// effect: s may be modified (shortened)
// time: O(n)
void strip(char *s) {
  assert(s);
  char *p = s;
  while (*s != '\0') {
    if (*s != ' ' && *s != '\n') {
      *p++ = *s;
    }
    s++;
  }
  *p = '\0';
}

// suggest(dict, word) creates a new SSS that contains suggestions
//   from the provided dict[ionary] for possible misspellings of word
// requires: dict, word are valid (not NULL)
//           length of word <= SUGGEST_MAX_STRLEN
//           word only contains lowercase letters (or numbers) [not asserted]
// effects: allocates memory (an SSS) (you must call sss_destroy)
// time: O(n)
struct triple_s *suggest(const struct triple_s *dict, const char *word) {
  assert(word);
  assert(dict);
  struct triple_s *sss = sss_create();
  //int idx = sss_search(dict, word);
  int length = strlen(word);
  assert(length <= 63);
  char modify[66] = {0};
  strcpy(modify, word);
  //Single swap for numbers
  for (int i = 0; i < length; i++) {
    if (modify[i] == '1' || modify[i] == '2' || modify[i] == '3' ||
        modify[i] == '4' || modify[i] == '5' || modify[i] == '6' ||
        modify[i] == '7' || modify[i] == '8' || modify[i] == '9' ||
        modify[i] == '0') {
      for (int j = 97; j < 123; j++) {
        modify[i] = j;
        if (sss_search(dict, modify) >= 0) {
          sss_add(sss, modify);
        }
      }
    }
    strcpy(modify, word);
  }
  //Single Swap for letters
  for (int n = 0; n < length; n++) {
    if (modify[n] >= 97 && modify[n] <= 122) {
      for (char m = 97; m < 123; m++) {
        modify[n] = m;
        if (sss_search(dict, modify) >= 0) {
          sss_add(sss, modify);
        }
        strcpy(modify, word);
      }
    }
  }
  //Single Deletion
  for (int k = 0; k < length; k++) {
    modify[k] = ' ';
    strip(modify);
    if (sss_search(dict,modify) >= 0) {
      sss_add(sss, modify);
    }
    strcpy(modify, word);
  }
  //Adjacent Swap
  for (int l = 0; l < length - 1; l++) {
    int letter_before = modify[l];
    int letter_after = modify[l + 1];
    modify[l] = letter_after;
    modify[l + 1] = letter_before;
    if (sss_search(dict,modify) >= 0) {
      sss_add(sss, modify);
    }
    strcpy(modify, word);
  }
  //Single Character Insertion Function
  for (int z = 0; z <= length + 1; z++) {
    char shift_holder = modify[z];
    for (int v = 97; v < 123; v++) {
      modify[z] = v;
      for (int s = length; s > z; s--) {
        modify[s] = modify[s - 1];
      }
      modify[z + 1] = shift_holder;

      modify[length + 1] = '\0';
      if (sss_search(dict,modify) >= 0) {
        sss_add(sss, modify);
      }
      strcpy(modify, word);
    }
    strcpy(modify, word);
  }
  if (sss_search(sss, word) >= 0) {
    sss_remove(sss, word);
  }
  return sss;
}
