#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "io.h"
#include <math.h>
/* TODO: define the functions declared in io.h... */


// fatal_error exits the program if there is an unrecoverable error
// printing the message first
void fatal_error(const char *message) {
  fprintf(stderr, "Error: %s", message);
  exit(0);
}

// the next few write functions write a single data value
// of various types in little-endian format
void write_byte(FILE *out, char val) {
  fputc((char)val, out);
}

void write_bytes(FILE *out, const char data[], unsigned n) {
  for (int i = 0; i < (int)n; i++) {
    write_byte(out, data[i]);
  }
}

void write_u16(FILE *out, uint16_t value) {
  int first = value % 256;
  int second = (value / 256) % 256;
  fputc(first, out);
  fputc(second, out);
}

void write_u32(FILE *out, uint32_t value) {
  int first = value % 256;
  int second = (value / 256) % 256;
  int third = (value / 65536) % 256;
  fputc(first, out);
  fputc(second, out);
  fputc(third, out);
}

void write_s16(FILE *out, int16_t value) {
  int first = value % 256;
  int second = (value / 256) % 256;
  fputc(first, out);
  fputc(second, out);
}

void write_s16_buf(FILE *out, const int16_t buf[], unsigned n) {
  for (int i = 0; i < (int)n; i++) {
    write_s16(out, buf[i]);
  }
}
