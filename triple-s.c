#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "cs136-trace.h"

// my_strdup(s) makes a duplicate of s
// effects: allocates memory (caller must free)
// time: O(1)
char *my_strdup(const char *s) {
  assert(s);
  char *newstr = malloc((strlen(s) + 1) * sizeof(char));
  strcpy(newstr, s);
  return newstr;
}

struct llnode {
  char* item;
  //int index;
  struct llnode *next;
};

struct llist {
  struct llnode *front;
};

/*struct llist *list_create(void) {
  struct llist *lst = malloc(sizeof(struct llist));
  lst->front = NULL;
  return lst;
} */

struct triple_s {
  int length;
  struct llnode *front;
  struct llnode *back; // <--- NEW
};

// The following applies to all functions
// requires: all sss parameters are valid (not NULL)
//           all s parameters are valid (not NULL)
// time: (n) is the number of strings in the sss
//       (m) is the length of the string s

// sss_create() creates a new SSS ADT
// effects: allocates memory (you must call sss_destroy)
// time: O(1)
struct triple_s *sss_create(void) {
  struct triple_s *sss = malloc(sizeof(struct triple_s));
  sss->front = NULL;
  sss->back = NULL;
  sss->length = 0;
  return sss;
}

// sss_destroy(sss) destroys sss
// requires: sss is valid (not NULL)
// effects: sss is no longer valid
// time: O(n)
void sss_destroy(struct triple_s *sss) {
  assert(sss);
  struct llnode *curnode = sss->front;
  struct llnode *nextnode = NULL;
  while (curnode) {
    nextnode = curnode->next;
    free(curnode->item);
    free(curnode);
    curnode = nextnode;
  }
  free(sss);
}
//add_front(sss, s) inserts s to the front of the sss
//require: s lexicographically preceed all strings in sss
//effects: modifies sss
//time: O(1)
void add_front(struct triple_s *sss, char *s) {
  assert(sss);
  assert(s);
  struct llnode *newnode = malloc(sizeof(struct llnode));
  newnode->item = s;
  newnode->next = sss->front;
  //newnode->index = sss->length;
  sss->front = newnode;
  if (sss->length == 0) {
    sss->back = newnode;
  }
}
// sss_add_follows(sss, s) adds s to the "end" of the sss
// requires: s lexicographically follows all strings already in sss
// effects: modifies sss
// time: O(m)
void sss_add_follows(struct triple_s *sss, const char *s) {
  assert(sss);
  assert(s);
  char *m = my_strdup(s);
  if (sss->length > 0) {
    struct llnode *newnode = malloc(sizeof(struct llnode));
    struct llnode *finalnode = sss->back;
    trace_ptr(sss->back);
    newnode->item = m;
    trace_string(s);
    finalnode->next = newnode;
    newnode->next = NULL;
    sss->back = newnode;
  }
  else {
    add_front(sss, m);
  }
  sss->length++;
}

// sss_search(sss, s) finds the index of s in sss
// note: returns -1 if s does not appear in the sss
// time: O(nm) [MODIFIED FROM A8]
int sss_search(const struct triple_s *sss, const char *s) {
  assert(sss);
  assert(s);
  int index = 0;
  const struct llnode *node = sss->front;
  while (index < sss->length) {
    //trace_string(sss->front->item);
    if (strcmp(node->item, s) == 0) {
      return index;
    }
    node = node->next;
    index++;
  }
  return -1;
}

// sss_add(sss, s) adds s to sss in the correct index (lexicographically)
// notes: if s already exists, there is no effect
//        when s is added, the indices of words that lexicographically
//          follow s will be changed (+1) because s is added into the "middle"
// effects: may modify sss
// time: O(nm) [MODIFIED FROM A8]
void sss_add(struct triple_s *sss, const char *s){
  assert(s);
  assert(sss);
  trace_string(s);
  if (sss->length == 0) {
    char *m = my_strdup(s);
    add_front(sss, m);
    sss->length++;
  }
  else if (sss_search(sss, s) == -1) {
    char *m = my_strdup(s);
    if ((strcmp (m, sss->front->item)) < 0) {
      add_front(sss, m);
      sss->length++;
    }
    else {
      struct llnode *before = sss->front;
      while (before->next && ((strcmp(m, before->next->item)) > 0)) {
        before = before->next;
      }
      struct llnode *newnode = malloc(sizeof(struct llnode));
      newnode->item = m;
      newnode->next = before->next;
      before->next = newnode;
      sss->length++;
    }
  }
}

// sss_count(sss) gets the number of strings in sss
// time: O(1)
int sss_count(const struct triple_s *sss) {
  assert(sss);
  return sss->length;
}

// sss_remove(sss, s) removes s from sss (if it exists)
// notes: if s is removed, the indices of words that lexicographically
//          follow s will be changed (-1)
// effects: may modify sss
// time: O(nm) [MODIFIED FROM A8]
void sss_remove(struct triple_s *sss, const char *s) {
  assert(sss);
  assert(s);
  if(sss_search(sss, s) != -1) {
  struct llnode *before = sss->front;
  while (before->next && (!((strcmp(before->next->item, s)) == 0))) {
    before = before->next;
  }
  struct llnode *old_node = before->next;
  before->next = before->next->next;
  free(old_node->item);
  free(old_node);
  sss->length--;
  }
}
// sss_get(sss, idx) retrieves a pointer to the string in sss
//   at the given idx (index)
// requires: 0 <= idx < sss_count(sss)
// time: O(n) [MODIFIED FROM A8]
const char *sss_get(const struct triple_s *sss, int idx) {
  assert (sss);
  assert (idx >= 0);
  assert(idx < sss_count(sss));
  const struct llnode *node = sss->front;
  for (int i = 0; i < idx; i++) {
    node = node->next;
  }
  return node->item;
}
