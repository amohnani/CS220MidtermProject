#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "io.h"
#include "wave.h"

//int parse_file(FILE *, char[], double**);
//void free_mem(char[] , double**, int);

int main(int argc, char *argv[]){
  if (argc != 3){
    fatal_error("Incorrect number of files in command line arguments.");
  }
  FILE *input = fopen(argv[1], "rb");
  FILE *output = fopen(argv[2], "wb");
  int num_samples;
  fscanf(input, " %d", &num_samples);
  int samples_per_beat;
  fscanf(input, " %d", &samples_per_beat);
  printf(" %d %d", num_samples, samples_per_beat);
  int16_t buf[num_samples];
  /*char * directives;
  double **nums;
  int num_directives = parse_file(input, directives, nums);
  */
  char directive;
  unsigned voice = 0;
  float amplitude = 0.1;
  float length, freq_hz;
  int note = 0;
  int current = 0;
  while (fscanf(input, " %c", &directive) == 1){
    if (directive == 'N'){
      fscanf(input, " %f %d", &length, &note);
      freq_hz = 440 * pow(2, (note-69.0)/12.0);
      printf(" %0.4f ", freq_hz);
      render_voice_stereo((buf + current), length*samples_per_beat, freq_hz, amplitude, voice);
      current += length*samples_per_beat;
    }else if (directive == 'P'){
      fscanf(input, " %f", &length);
      current += length*samples_per_beat;
    }else if (directive == 'C'){
      fscanf(input, " %f", &length);
      while (fscanf(input, " %d", &note) == 1){
	if (note == 999){
	  break;
	}
	freq_hz = 440 * pow(2, (note-69.0)/12.0);
	printf(" %0.4f ", freq_hz);
	render_voice_stereo((buf + current), length*samples_per_beat, freq_hz, amplitude, voice);
      }
      current += length*samples_per_beat;
    }else if (directive == 'V'){
      fscanf(input, " %u", &voice);
      if (voice >2){
	fatal_error("Malformed input\n");
      }
    }else if (directive == 'A'){
      fscanf(input, " %f", &amplitude);
      if (amplitude < 0 || amplitude > 1){
	fatal_error("Malformed input\n");
      }
    }
  }
  
  write_wave_header(output, (unsigned)num_samples);
  write_s16_buf(output, buf, (unsigned)num_samples);
  //free_mem(directives, nums, num_directives);
  fclose(input);
}


/*
int parse_file(FILE *fptr, char* directives, double** nums){
  int count = 0;
  char direct;
  double num;
  int i = 0;
  directives = malloc(10*sizeof(char));
  nums = malloc(10*sizeof(double *));
  for (int j = count; j < 10; j++){
    nums[j] = malloc(4*sizeof(double));
  }
  while (fscanf(fptr, " %c", &direct) != EOF){
    if (count % 10 == 0 && count != 0){
      directives = realloc(directives, (count+10)*sizeof(char));
      nums = realloc(nums,(count+10)* sizeof(double*));
      for (int j = count; j < count +  10; j++){
	nums[j] = malloc(4*sizeof(double));
      }
      }
    directives[count] = direct;
    while (fscanf(fptr, " %lf", &num) == 1 && i < 4){
      nums[count][i] = num;
      i++;
    }
    i = 0;
    count++;
    }
  return count;
}

void free_mem(char* directives, double** nums, int count){
  for (int i = 0; i < count; i++){
    free(nums[i]);
    
  }
  free(nums);
  free(directives);
  }
*/
