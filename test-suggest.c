#include <assert.h>
#include <stdio.h>
#include "words.h"
#include "suggest.h"

int main(void) {
  struct triple_s *dict = words_create();
  char word[64] = "";
  while (scanf("%s", word) == 1) {
    printf("%s:", word);
    int dict_index = sss_search(dict, word);
    if (dict_index == -1) {
      struct triple_s *suggestions = suggest(dict, word);
      if (sss_count(suggestions)) {
        for (int i = 0; i < sss_count(suggestions); ++i) {
          printf(" %s", sss_get(suggestions, i));
        }
      } else {
        printf(" NONE");
      }
      sss_destroy(suggestions);
    } else {
      printf(" OK");
    }
    printf("\n");
  }
  sss_destroy(dict);
}
