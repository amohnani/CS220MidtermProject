#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "io.h"

/* TODO: define the functions declared in io.h... */


// fatal_error exits the program if there is an unrecoverable error
// printing the message first
void fatal_error(const char *message) {
  pfrintf(stderr, "Error: %s", message);
}

// the next few write functions write a single data value
// of various types in little-endian format
void write_byte(FILE *out, char val) {
  if (fopen(out, "w") == NULL) {
    fatal_error("Cannot open file");
  }
  fputc((int) val, out);
}

void write_bytes(FILE *out, const char data[], unsigned n) {
  for (int i = 0; i < n; i++) {
    write_byte(out, data[i]);
  }
}
