
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "wave.h"
#include "io.h"


int  main(){
  FILE * out = fopen("out.wav", "wb");
  write_wave_header(out, 44100);
  fclose(out);

  FILE * in = fopen("out.wav", "rb");
  unsigned *samples = 0;
  read_wave_header(in, samples);
  fclose(in);
  return 0;
}
