//CS220 Midterm Project
//Abhi Mohnani and Alan Zhang
//amohnan1 and azhang42


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "io.h"
#include "wave.h"

int main(int argc, char *argv[]){
  if (argc != 3){
    fatal_error("Incorrect number of files in command line arguments.");
  }

  //opens files and checks that they are valid
  FILE *input = fopen(argv[1], "rb");
  FILE *output = fopen(argv[2], "wb");
  if (input == NULL || output == NULL || ferror(input) || ferror(output)){
    fatal_error("Error opening files.\n");
  }

  //gets information from command-line arguments
  int num_samples;
  int samples_per_beat;
  if (fscanf(input, " %d", &num_samples) != 1 ||  fscanf(input, " %d", &samples_per_beat) != 1){
    fatal_error("Incorrectly formatted input.\n");
  }
  
  //allocates memory for buffer array
  int num_stereo = 2*num_samples;
  int16_t *buf = calloc(num_stereo,sizeof(int16_t));

  //declares and initializes necessary variables
  char directive = ' ';
  unsigned voice = 0;
  float amplitude = 0.1;
  float length, freq_hz;
  int note = 0;
  int current = 0;

  //continues while there are more directives to perform
  while (fscanf(input, " %c", &directive) == 1){
    if (directive == 'N'){
      if (fscanf(input, " %f %d", &length, &note) != 2){
	fatal_error("Incorrectly formatted input.\n");
      }
      //creates frequency according to MIDI note
      freq_hz = 440 * pow(2, (note-69.0)/12.0);
      //changes buffer array using new note
      render_voice_stereo((buf + current),2* length*samples_per_beat, freq_hz, amplitude, voice);
      //changes index in array
      current += length*samples_per_beat*2;
      
    }else if (directive == 'P'){
      if (fscanf(input, " %f", &length) != 1){
	fatal_error("Incorrectly formatted input.\n");
      }
      //changes index to create a pause
      current += length*samples_per_beat*2;
    }else if (directive == 'C'){
      if (fscanf(input, " %f", &length) != 1){
	fatal_error("Incorrectly formatted input.\n");
      }

      //continues while there are more notes to be added
      while (fscanf(input, " %d", &note) == 1){
	if (note == 999){
	  break;
	}
	//calculates frequency and changes buffer array accordingly
	freq_hz = 440 * pow(2, (note-69.0)/12.0);
	render_voice_stereo((buf + current), 2*length*samples_per_beat, freq_hz, amplitude, voice);
      }
      //changes index
      current += length*samples_per_beat*2;
      
    }else if (directive == 'V'){
      //changes voice
      if (fscanf(input, " %u", &voice) != 1){
	fatal_error("Incorrectly formatted input.\n");
      }
      if (voice >2){
	fatal_error("Voice value is not valid.\n");
      }
      
    }else if (directive == 'A'){
      //changes amplitude
      if (fscanf(input, " %f", &amplitude) != 1){
	fatal_error("Incorrectly formatted input.\n");
      }
      if (amplitude < 0 || amplitude > 1){
	fatal_error("Amplitude value is not valid.\n");
      }
    }
  }

  //writes updated buffer array to output file
  write_wave_header(output, (unsigned)num_samples);
  write_s16_buf(output, buf, (unsigned)num_stereo);
  fclose(input);
  free(buf);
}

