#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "wave.h"
#include "io.h"

int main(int argc, char *argv[]){
  if (argc != 6){
    fatal_error("Incorrect number of inputs.");
  }
  int numsamples, voice;
  float frequency, amplitude; 
  sscanf(argv[1], "%d", &voice);
  sscanf(argv[2], "%f", &frequency);
  sscanf(argv[3], "%f", &amplitude);
  sscanf(argv[4], "%d", &numsamples);
  FILE *fptr = fopen(argv[5], "wb");
  int16_t buf[numsamples];
  render_voice_stereo(buf, numsamples, frequency, amplitude, (unsigned int)voice);
  FILE *test = fopen("test.txt", "w");
  for (int i = 0; i < numsamples; i+= 10){
    fprintf(test, "%d ", buf[i]);
  }
  write_wave_header(fptr, numsamples);
  write_s16_buf(fptr, buf, (unsigned int)numsamples);
  fclose(fptr);
  fclose(test);
}
