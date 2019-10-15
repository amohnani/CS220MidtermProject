#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "wave.h"
#include "io.h"
#include <assert.h>

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
  unsigned numstereo = 2 * numsamples;
  int16_t buf[numstereo];
  render_voice_stereo(buf, numstereo, frequency, amplitude, (unsigned int)voice);
  FILE *test = fopen("test.txt", "w");
  for (unsigned i = 0; i < numstereo; i+= 10){
    fprintf(test, "%d ", buf[i]);
  }
  write_wave_header(fptr, numsamples);
  write_s16_buf(fptr, buf, (unsigned int)numstereo);
  fclose(fptr);
  fclose(test);
}
