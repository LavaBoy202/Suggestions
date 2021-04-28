#include "triple-s.h"

extern const int SUGGEST_MAX_STRLEN;

// suggest(dict, word) creates a new SSS that contains suggestions
//   from the provided dict[ionary] for possible misspellings of word
// note: the word itself should not appear in the returned SSS
//       the returned SSS will be empty if no suggestions can be found
//         (the returned SSS must still be destroyed)
//       see assignment text for more details regarding
//         which words should be suggested
// requires: dict, word are valid (not NULL)
//           length of word <= SUGGEST_MAX_STRLEN
//           word only contains lowercase letters (or numbers) [not asserted]
// effects: allocates memory (an SSS) (you must call sss_destroy)
// time: ??? (provide this in your .c file)
struct triple_s *suggest(const struct triple_s *dict, const char *word);
