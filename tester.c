
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "wave.h"
#include "io.h"


int  main(){
  FILE * in = fopen("c70_sq.wav", "rb");
  //write_wave_header(out, 44100);
  //fclose(out);

  //FILE * in = fopen("out.wav", "rb");
  unsigned samples;
  read_wave_header(in, &samples);
  printf("%u", samples);
  fclose(in);
  return 0;
}
