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
  if (sscanf(argv[1], "%d", &voice) != 1 ||
  sscanf(argv[2], "%f", &frequency) != 1 ||
  sscanf(argv[3], "%f", &amplitude) != 1 ||
      sscanf(argv[4], "%d", &numsamples) != 1){
    fatal_error("Command line arguments are incorrectly formatted.\n");
  }
  
  FILE *fptr = fopen(argv[5], "wb");
  unsigned numstereo = 2 * numsamples;
  int16_t * buf = (int16_t *) calloc(numstereo, sizeof(int16_t));
  render_voice_stereo(buf, numstereo, frequency, amplitude, (unsigned int)voice);
  //FILE *test = fopen("test.txt", "w");
  //for (unsigned i = 0; i < numstereo; i+= 10){
  //  fprintf(test, "%d ", buf[i]);
  // }
  write_wave_header(fptr, numsamples);
  write_s16_buf(fptr, buf, (unsigned int)numstereo);
  free(buf);
  if (ferror(fptr)){
    fatal_error("Error while writing file.");
  }
  fclose(fptr);
  //fclose(test);
  return 0;
}
