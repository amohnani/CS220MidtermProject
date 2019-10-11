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
  if (fputc(val, out) == EOF) {
    fatal_error("error in writing byte");
  }
}

void write_bytes(FILE *out, const char data[], unsigned n) {
  for (int i = 0; i < (int)n; i++) {
    write_byte(out, data[i]);
  }
}

void write_u16(FILE *out, uint16_t value) {
  char first = value % 256;
  char second = (value / 256) % 256;
  if (fputc(first, out) == EOF) {
    fatal_error("error in writing first u16");
  }
  if (fputc(second, out) == EOF) {
    fatal_error("error in writing 2nd u16");
  }
}

void write_u32(FILE *out, uint32_t value) {
  unsigned char first = value % 256;
  char second = (value / 256) % 256;
  char third = (value / 65536) % 256;
  char fourth = (value / 16777216) % 256;
  if ((fputc(first, out) == EOF) ||
      (fputc(second, out) == EOF) ||
      (fputc(third, out) == EOF) ||
      (fputc(fourth, out) == EOF)) {
    fatal_error("error in writing u32");
  }
}

void write_s16(FILE *out, int16_t value) {
  char first = value % 256;
  char second = (value / 256) % 256;
  if ((fputc(first, out) == EOF) ||
      (fputc(second, out) == EOF)) {
    fatal_error("error in writing u32");
  }
}

void write_s16_buf(FILE *out, const int16_t buf[], unsigned n) {
  for (int i = 0; i < (int)n; i++) {
    write_s16(out, buf[i]);
  }
}


// these functions read some binary and reconstruct
// and returning the value to the address

void read_byte(FILE * in, char *val) {
  *val = fgetc(in);
  if (*val == EOF){
    fatal_error("error in reading byte");
  }
}

void read_bytes(FILE * in, char data[], unsigned n) {
  for (int i = 0; i < (int)n; i++){
    read_byte(in, (data+i));
  }
}

void read_u16(FILE *in, uint16_t *val) {
  char input[2];
  read_bytes(in, input, 2);
  *val = input[0] | (input[1] << 8);
}

void read_u32(FILE *in, uint32_t *val) {
  char input[4];
  read_bytes(in, input, 4);
  *val = ((input[0] | (input[1] << 8) | (input[2] << 16) | (input[3] << 24))) & (2147483647);
}

void read_s16(FILE *in, int16_t *val) {
  char input[2];
  read_bytes(in, input, 2); 
  *val = input[0] | (input[1] << 8);
}

void read_s16_buf(FILE *in, int16_t buf[], unsigned n){
  for (int i = 0; i < (int)n; i++) {
    read_s16(in, &buf[i]);
  }
}
