#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "element.h"
#include "refcount.h"

/* See the header file for the descriptions of each function. */
struct element {
  int num;
  char *value;
};

/** Create a new element, which holds the given number and string.
 *
 * Postcondition: the created element has its own copy of the string.
 */
struct element *element_new(int num, char *value) {
  struct element *e = rc_malloc(sizeof(*e));
  if(e == NULL) {
    /* out of memory? */
    return NULL;
  }
  e->num = num;
  e->value = strdup(value);
  return e;
}

/** Return current rc value*/ 
int  check_rc(void* p) {
  // get pointer to ref count from client pointer
  int* ref_count = p - 8;
  // increment ref count
  return *ref_count;
}

/** Delete an element, freeing the memory associated with it. */
void element_delete(struct element *e) {
  int rc = check_rc(e);
  if(rc == 1){
    free(e->value);
    rc_free_ref(e);
  } else {
    rc_free_ref(e);
  }
}

/** Get the stored number from an element.
 *
 */
int element_get_num(struct element *e) {
  return e->num;
}

/** Get the stored string from an element.
 *
 * Returns: a pointer to the string value, which is still owned by the element.
 * Do not free or modify the returned string; make a copy if you want to keep
 * it past the element's lifetime.
 */
char *element_get_value(struct element *e) {
  return e->value;
}

