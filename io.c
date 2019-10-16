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
  unsigned uval = (unsigned) val;
  if (fputc(uval, out) == EOF) {
    fatal_error("error in writing byte");
  }
}

//writes multiple bytes
void write_bytes(FILE *out, const char data[], unsigned n) {
  for (int i = 0; i < (int)n; i++) {
    write_byte(out, data[i]);
  }
}

//writes uint16_t values
void write_u16(FILE *out, uint16_t value) {
  unsigned first = value % 256;
  unsigned second = (value / 256) % 256;
  if (fputc(first, out) == EOF) {
    fatal_error("error in writing first u16");
  }
  if (fputc(second, out) == EOF) {
    fatal_error("error in writing 2nd u16");
  }
}

//writes uint32_t values
void write_u32(FILE *out, uint32_t value) {
  unsigned first = value % 256;
  unsigned second = (value / 256) % 256;
  unsigned third = (value / 65536) % 256;
  unsigned fourth = (value / 16777216) % 256;
  if ((fputc(first, out) == EOF) ||
      (fputc(second, out) == EOF) ||
      (fputc(third, out) == EOF) ||
      (fputc(fourth, out) == EOF)) {
    fatal_error("error in writing u32");
  }
}

//writes int16_t values
void write_s16(FILE *out, int16_t value) {
  unsigned uval = (unsigned) value;
  unsigned first = uval % 256;
  unsigned second = (uval / 256) % 256;
  if ((fputc(first, out) == EOF) ||
      (fputc(second, out) == EOF)) {
    fatal_error("error in writing u32");
  }
}

//writes an array of int16_t values
void write_s16_buf(FILE *out, const int16_t buf[], unsigned n) {
  for (int i = 0; i < (int)n; i++) {
    write_s16(out, buf[i]);
  }
}


// these functions read some binary and reconstruct
// and returning the value to the address

void read_byte(FILE * in, char *val) {
  int input = fgetc(in);
  if (input == EOF){
    fatal_error("error in reading byte");
  }
  *val = input;
}

//reads multiple bytes
void read_bytes(FILE * in, char data[], unsigned n) {
  for (int i = 0; i < (int)n; i++){
    read_byte(in, (data+i));
  }
}

//reads unsigned int16_ts
void read_u16(FILE *in, uint16_t *val) {
  char input[2];
  read_bytes(in, input, 2);
  unsigned char * usign = (unsigned char *) input;
  *val = usign[0] | (usign[1] << 8);
}

//reads uint32_t
void read_u32(FILE *in, uint32_t *val) {
  char input[4];
  read_bytes(in, input, 4);
  unsigned char usign[4];
  for (int i = 0; i < 4; i++) {
    usign[i] = (unsigned) input[i];
  }
  *val = (usign[0] | (usign[1] << 8) | (usign[2] << 16) | (usign[3] << 24));
}

//reads int16_t
void read_s16(FILE *in, int16_t *val) {
  char input[2];
  read_bytes(in, input, 2);
  unsigned char uinput[2];
  for (int i = 0; i < 2; i++) {
    uinput[i] = (unsigned) input[i];
  }
  *val = uinput[0] | (uinput[1] << 8);
}

//reads an array of int16_t values
void read_s16_buf(FILE *in, int16_t buf[], unsigned n){
  for (unsigned i = 0; i < n; i++) {
    read_s16(in, &buf[i]);
  }
}
