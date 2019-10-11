#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "io.h"
#include "wave.h"

int parse_file(File *fptr, char[] directives, double[][4] nums);
void free_mem(char[] directives, double[][4] nums, int count);

int main(int argc, char *argv[]){
  if (argc != 2){
    fatal_error("Incorrect number of files in command line arguments.");
  }
  File *input = fopen(argv[0], "r");
  int num_samples;
  fscanf(input, " %d", &num_samples);
  int samples_per_beat;
  fscanf(input, " &d", &samples_per_beat);
  
  char directives[];
  double nums[][];
  int num_directives = parse_file(input, directives, nums);

  free_mem(directives, nums, num_directives);
  fclose(input);
}

int parse_file(File *fptr, char[] directives, double[][4] nums){
  int count = 0;
  char direct;
  double num;
  int i = 0;
  directives = malloc(10*sizeof(char));
  nums = malloc(10*sizeof(double *));
  for (int j = count; j < 10; j++){
    nums[j] = malloc(4*sizeof(double));
  }
  while (fscanf(fptr, " %c", &direct) == 1){
    if (count % 10 == 0 && count != 0){
      directives = realloc(count, sizeof(char));
      nums = realloc(count, sizeof(double*));
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

void free_mem(char[] directives, double[][4] nums, int count){
  for (int i = 0; i < count; i++){
    nums[i];
  }
  free(nums);
  free(directives);
}
