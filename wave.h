#ifndef WAVE_H
#define WAVE_H

#include <stdint.h>

#define PI                 3.14159265358979323846
#define SAMPLES_PER_SECOND 44100u
#define NUM_CHANNELS       2u
#define BITS_PER_SAMPLE    16u

/* voices */
#define SINE       0
#define SQUARE     1
#define SAW        2
#define NUM_VOICES 3 /* one greater than maximum legal voice */

void write_wave_header(FILE *out, unsigned num_samples);
void read_wave_header(FILE *in, unsigned *num_samples);

/* TODO: add declarations for additional functions */

#endif /* WAVE_H */
