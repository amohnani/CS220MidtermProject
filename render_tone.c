#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "wave.h"
#include "io.h"

int main(int argc, char *argc[]){
  if (argc != 7){
    fatal_error("Incorrect number of inputs.");
  }
  int numsamples, voice;
  float frequency, amplitude; 
  sscanf(argc[1], "%d", &voice);
  sscanf(argc[2], "%f", &frequency);
  sscanf(argc[3], "%f", &amplitude);
  sscanf(argc[4], "%d", &numsamples);
  FILE *fptr = fopen(argc[5], "wb");
  int16_t buf[numsamples];
  render_voice_stereo(buf, num_samples, frequency, amplitude, (unsigned int)voice);
  write_wave_header(fptr, numsamples);
  write_s16_buf(fptr, buf, (unsigned int)numsamples);
  fclose(ptr);

}
