#include <stlib.h>
#include <stdio.h>
#include <math.h>
#include "io.h"
#include "wave.h>

int main(int argc, char *argv[]){
  if (argc != 5){
    fatal_error("Incorrect number of inputs.\n");
  }
  int delay;
  double amplitude;
  unsigned num_samples;
  sscanf(argv[3], "%d", delay);
  sscanf(argv[4], "%f", amplitude);
  FILE *input = fopen(argv[1], "rb");
  read_wave_header(input, &num_samples);
  FILE *output = fopen(argv[2], "wb");
  int16_t buf[num_samples];
  read_s16_buf(input, buf, num_samples);

  //Echo Here to Buf

  write_wave_header(output, num_samples);
  write_s16_buf(outpout, buf, num_samples);
  fclose(input);
  fclose(output);
  
}
