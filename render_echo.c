//CS220 Midterm Project
//Abhi Mohnani and Alan Zhang
//amohnan1 and azhang42


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "io.h"
#include "wave.h"

int main(int argc, char *argv[]){
  // makes sure there are a valid amount of arguments
  if (argc != 5){
    fatal_error("Incorrect number of inputs.\n");
  }

  //checks that all input arguments are validly formatted
  int delay;
  float amplitude;
  unsigned num_samples;
  if (sscanf(argv[3], "%d", &delay) != 1 ||  sscanf(argv[4], "%f", &amplitude) != 1){
    fatal_error("Malformed command-line arguments.\n");
  }

  //opens file and checks that it is valid
  FILE *input = fopen(argv[1], "rb");
  if (input == NULL){
    fatal_error("Input file does not exist.\n");
  }

  // reads the samples in the file
  read_wave_header(input, &num_samples);
  int num_stereo = num_samples*2;

  FILE *output = fopen(argv[2], "wb");

  // buf is to read, and then bufcopy is what will be added for the echo
  int16_t * buf = (int16_t *)calloc(num_stereo, sizeof(int16_t)); 
  int16_t * bufcopy = (int16_t *)calloc(num_stereo, sizeof(int16_t));

  read_s16_buf(input, buf, num_stereo);
  
  //copies original signal to copy array
  for (int i = 0; i < num_stereo; i++){
    bufcopy[i] = buf[i];
  }

  //copies sound after the delay to create the echo effect
  for (int i = 2 * delay; i < num_stereo; i++){
    float val = buf[i] + amplitude*bufcopy[i- 2 * delay];
    // checks for clipping
    if (val > 32767) {
      val = 32767;
    } else if (val < -32767) {
      val = -32767;
    }
    buf[i] = (int16_t)val;
  }

  //writes buffer array to output file
  write_wave_header(output, num_samples);
  write_s16_buf(output, buf, num_stereo);

  // free allocated 
  free(buf);
  free(bufcopy);

  //checks that files were written properly
  if (ferror(input) || ferror(output)){
    fatal_error("Error reading or writing files.\n");
  }

  // close opened files
  fclose(input);
  fclose(output);
  
}
