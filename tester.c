#include <stdlib.h>
#include <stdio.h>
#include <math.h>
//include "wave.c"
#include "io.c"
int  main(){
  FILE * out = fopen("tester.wav", "wb");
  char c = 'C';
  char cs[] = {'a','b','c','d'};
  //int sixteen = 321;

  //write_u16(out, sixteen);
  write_byte(out, c);
  write_bytes(out, cs, 4);
  //fatal_error("oh no");
  //printf("should not be printed");
  fclose(out);
  return 0;
}
