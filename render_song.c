#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "io.h"
#include "wave.h"

//int parse_file(FILE *, char[], double**);
//void free_mem(char[] , double**, int);
void parse_file(FILE *);

int main(int argc, char *argv[]){
  if (argc != 3){
    fatal_error("Incorrect number of files in command line arguments.");
  }
  FILE *input = fopen(argv[1], "r");
  int num_samples;
  fscanf(input, " %d", &num_samples);
  int samples_per_beat;
  fscanf(input, " %d", &samples_per_beat);
  printf(" %d %d", num_samples, samples_per_beat);
  
  /*char * directives;
  double **nums;
  int num_directives = parse_file(input, directives, nums);
  */

  
  //free_mem(directives, nums, num_directives);
  fclose(input);
}

void parse_file(FILE *input){
  char directive;
  int v;
  while (fscanf(input, " %c", directive) != EOF){
    
  }
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
