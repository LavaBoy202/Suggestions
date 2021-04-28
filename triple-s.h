// This module provides a "Sorted Set of Strings" ADT (aka SSS / "Triple S")

// SEASHELL_READONLY

/*
  Sorted Set of Strings
  ^      ^      ^
  |      |      +--------- this ADT stores strings
  |      +---------------- this is a "set", so there are no duplicates
  +----------------------- the items are sorted (in ascending order)

  To create a new SSS:
    struct triple_s *sss = sss_create();

  To add a string:
      sss_add(sss, "apple");

  A copy of the string is added to the SSS, so if a client modifies the
  contents of the original string that was added, the SSS is not affected
      char str[] = "cat";
      sss_add(sss, str);
      str[0] = 'b';          // sss still contains "cat", not "bat"

  If a duplicate string is added, then it is ignored:
      sss_add(sss, "apple");
      sss_add(sss, "apple");    // NO EFFECT

  Two strings are duplicates only if every character is identical.
      sss_add(sss, "apple");
      sss_add(sss, "APPLE");      // ADDED (different string)
      sss_add(sss, " apple");     // ADDED (different string)

  If you want to add a string that lexicographically follows all other
  strings in sss (which means it also does not already appear in the sss)
  it is more efficient to use:
      sss_add_follows(sss, "zebra");

  To determine how many strings are in sss, call:
      int count = sss_count(sss);

  To search for a string in sss:
      int idx = sss_search(sss, "needle");

  sss_search returns either the "index" of the string you are searching
  for or -1 if it does not exist.

  The strings in an SSS are SORTED, so:
  * the string with index 0 lexicographically precedes all other strings
  * the string with index [sss_count(...) - 1] follows all other strings

  To retrieve a pointer to the string with a given index, use sss_get:
      printf("%s\n", sss_get(sss, idx));

  To remove a string:
      sss_remove(sss, "string_to_remove");
  If the string does not exist, then there is no effect

  To destroy the SSS (which is required)
      sss_destroy(sss);
*/


struct triple_s;

// The following applies to all functions
// requires: all sss parameters are valid (not NULL)
//           all s parameters are valid (not NULL)
// time: (n) is the number of strings in the sss
//       (m) is the length of the string s

// sss_create() creates a new SSS ADT
// effects: allocates memory (you must call sss_destroy)
// time: O(1)
struct triple_s *sss_create(void);

// sss_destroy(sss) destroys sss
// requires: sss is valid (not NULL)
// effects: sss is no longer valid
// time: O(n)
void sss_destroy(struct triple_s *sss);

// sss_add(sss, s) adds s to sss in the correct index (lexicographically)
// notes: if s already exists, there is no effect
//        when s is added, the indices of words that lexicographically
//          follow s will be changed (+1) because s is added into the "middle"
// effects: may modify sss
// time: O(nm) [MODIFIED FROM A8]
void sss_add(struct triple_s *sss, const char *s);

// sss_add_follows(sss, s) adds s to the "end" of the sss
// requires: s lexicographically follows all strings already in sss
// effects: modifies sss
// time: O(m)
void sss_add_follows(struct triple_s *sss, const char *s);

// sss_remove(sss, s) removes s from sss (if it exists)
// notes: if s is removed, the indices of words that lexicographically
//          follow s will be changed (-1)
// effects: may modify sss
// time: O(nm) [MODIFIED FROM A8]
void sss_remove(struct triple_s *sss, const char *s);

// sss_count(sss) gets the number of strings in sss
// time: O(1)
int sss_count(const struct triple_s *sss);

// sss_search(sss, s) finds the index of s in sss
// note: returns -1 if s does not appear in the sss
// time: O(nm) [MODIFIED FROM A8]
int sss_search(const struct triple_s *sss, const char *s);

// sss_get(sss, idx) retrieves a pointer to the string in sss
//   at the given idx (index)
// requires: 0 <= idx < sss_count(sss)
// time: O(n) [MODIFIED FROM A8]
const char *sss_get(const struct triple_s *sss, int idx);
