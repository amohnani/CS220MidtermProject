#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "io.h"

/* TODO: define the functions declared in io.h... */


//fatal_error exits the program if there is an unrecoverable error
// printing the message first

void fatal_error(const char *message) {
  pfrintf(stderr, "Error: %s", message);
}
