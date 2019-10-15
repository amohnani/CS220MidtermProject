#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "io.h"
#include "wave.h"

int main(int argc, char *argv[]){
  if (argc != 5){
    fatal_error("Incorrect number of inputs.\n");
  }
  int delay;
  float amplitude;
  unsigned num_samples;
  sscanf(argv[3], "%d", &delay);
  sscanf(argv[4], "%f", &amplitude);
  FILE *input = fopen(argv[1], "rb");
  read_wave_header(input, &num_samples);
  int num_stereo = num_samples*2;
  FILE *output = fopen(argv[2], "wb");
  int16_t buf[num_stereo];
  int16_t bufcopy[num_stereo];
  read_s16_buf(input, buf, num_samples);

  //Echo Here to Buf
  for (int i = 0; i < num_stereo; i++){
    bufcopy[i] = buf[i];
  }
  for (int i = delay; i < num_stereo; i++){
    buf[i] += amplitude*bufcopy[i-delay];
  }

  write_wave_header(output, num_samples);
  write_s16_buf(output, buf, num_stereo);
  fclose(input);
  fclose(output);
  
}
