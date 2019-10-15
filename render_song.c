#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "io.h"
#include "wave.h"

int main(int argc, char *argv[]){
  if (argc != 3){
    fatal_error("Incorrect number of files in command line arguments.");
  }

  //opens files and reads from command line arguments
  FILE *input = fopen(argv[1], "rb");
  FILE *output = fopen(argv[2], "wb");
  int num_samples;
  fscanf(input, " %d", &num_samples);
  int samples_per_beat;
  fscanf(input, " %d", &samples_per_beat);

  //allocates memory for buffer array
  int num_stereo = 2*num_samples;
  int16_t *buf = calloc(num_stereo,sizeof(int16_t));
  
  char directive;
  unsigned voice = 0;
  float amplitude = 0.1;
  float length, freq_hz;
  int note = 0;
  int current = 0;

  //continues while there are more directives to perform
  while (fscanf(input, " %c", &directive) == 1){
    if (directive == 'N'){
      fscanf(input, " %f %d", &length, &note);
      //creates frequency according to MIDI note
      freq_hz = 440 * pow(2, (note-69.0)/12.0);
      //changes buffer array using new note
      render_voice_stereo((buf + current),2* length*samples_per_beat, freq_hz, amplitude, voice);
      //changes index in array
      current += length*samples_per_beat*2;
      
    }else if (directive == 'P'){
      fscanf(input, " %f", &length);
      //changes index to create a pause
      current += length*samples_per_beat*2;
    }else if (directive == 'C'){
      fscanf(input, " %f", &length);

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
      fscanf(input, " %u", &voice);
      if (voice >2){
	fatal_error("Malformed input\n");
      }
      
    }else if (directive == 'A'){
      //changes amplitude
      fscanf(input, " %f", &amplitude);
      if (amplitude < 0 || amplitude > 1){
	fatal_error("Malformed input\n");
      }
    }
  }
  
  write_wave_header(output, (unsigned)num_samples);
  write_s16_buf(output, buf, (unsigned)num_stereo);
  fclose(input);
  free(buf);
}

