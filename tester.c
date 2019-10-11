#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "wave.h"
#include "io.h"


int  main(){
  FILE * out = fopen("tester.wav", "wb");
  FILE * out2 = fopen("out.wav", "wb");
  char c = 'C';
  char cs[] = {'a','b','c','d'};
  int n  = 4;
  uint16_t a = 321;
  uint32_t b = 12341234;
  int16_t d = 543;
  int16_t e[] = {1234,6565,8,124};
  

  
  write_byte(out, c);
  write_bytes(out, cs, n);
  write_u16(out, a);
  write_u32(out, b);
  write_s16(out, d);
  write_s16_buf(out, e, n);

  write_wave_header(out2, 44100);
  //fatal_error("oh no");
  //printf("should not be printed");
  fclose(out);
  fclose(out2);
  return 0;
}
