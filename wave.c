#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "io.h"
#include "wave.h"



// Creates sin wave for one channel using formula
void render_sine_wave(int16_t buf[], unsigned num_samples, unsigned channel, float freq_hz, float amplitude)
{
  for (unsigned i = channel; i <  num_samples; i+= 2){
    buf[i] += (int16_t) 32767* amplitude*sin(((float)i/SAMPLES_PER_SECOND)*freq_hz*PI);
  }
}

void render_sine_wave_stereo(int16_t buf[], unsigned num_samples, float freq_hz, float amplitude){
  render_sine_wave(buf, num_samples, 0, freq_hz, amplitude);
  render_sine_wave(buf, num_samples, 1, freq_hz, amplitude);
}

void render_square_wave(int16_t buf[], unsigned num_samples, unsigned channel,  float freq_hz, float amplitude){
  
  for (unsigned i = channel; i < num_samples; i+=2){
    if (amplitude*sin(((float)i/SAMPLES_PER_SECOND)*freq_hz*PI) > 0){
      buf[i] += amplitude*32767;
    }else{
      buf[i] +=  0 - amplitude*32767;
    }
  }
}

void render_square_wave_stereo(int16_t buf[], unsigned num_samples, float freq_hz, float amplitude){
  render_square_wave(buf, num_samples, 0, freq_hz, amplitude);
  render_square_wave(buf, num_samples, 1, freq_hz, amplitude);
}

void render_saw_wave(int16_t buf[], unsigned num_samples, unsigned channel, float freq_hz, float amplitude){
  double cycle_time = 1/freq_hz*44100;
  double slope = (2*amplitude)/cycle_time;
  for (int i = channel; i < (int)num_samples; i+= 2){
    buf[i] += -2*amplitude + (slope * (i % (int)cycle_time));
  }
}

void render_saw_wave_stereo(int16_t buf[], unsigned num_samples, float freq_hz, float amplitude){
  render_saw_wave(buf, num_samples, 0, freq_hz, amplitude);
  render_saw_wave(buf, num_samples, 1, freq_hz, amplitude);
}

void render_voice(int16_t buf[], unsigned num_samples, unsigned channel, float freq_hz, float amplitude, unsigned voice){
  if (voice == 0){
    render_sine_wave(buf, num_samples, channel, freq_hz, amplitude);
  }else if (voice == 1){
     render_square_wave(buf, num_samples, channel, freq_hz, amplitude);
  }else if (voice == 2){
    render_saw_wave(buf, num_samples, channel, freq_hz, amplitude);
  }
}

void render_voice_stereo(int16_t buf[], unsigned num_samples, float freq_hz, float amplitude, unsigned voice){
  if (voice == 0){
    render_sine_wave_stereo(buf, num_samples, freq_hz, amplitude);
  }else if (voice == 1){
    render_square_wave_stereo(buf, num_samples, freq_hz, amplitude);
  }else if (voice == 2){
    render_square_wave_stereo(buf, num_samples, freq_hz, amplitude);
  }

}

/*
 * Write a WAVE file header to given output stream.
 * Format is hard-coded as 44.1 KHz sample rate, 16 bit
 * signed samples, two channels.
 *
 * Parameters:
 *   out - the output stream
 *   num_samples - the number of (stereo) samples that will follow
 */
void write_wave_header(FILE *out, unsigned num_samples) {
  /*
   * See: http://soundfile.sapp.org/doc/WaveFormat/
   */

  uint32_t ChunkSize, Subchunk1Size, Subchunk2Size;
  uint16_t NumChannels = NUM_CHANNELS;
  uint32_t ByteRate = SAMPLES_PER_SECOND * NumChannels * (BITS_PER_SAMPLE/8u);
  uint16_t BlockAlign = NumChannels * (BITS_PER_SAMPLE/8u);

  /* Subchunk2Size is the total amount of sample data */
  Subchunk2Size = num_samples * NumChannels * (BITS_PER_SAMPLE/8u);
  Subchunk1Size = 16u;
  ChunkSize = 4u + (8u + Subchunk1Size) + (8u + Subchunk2Size);

  /* Write the RIFF chunk descriptor */
  write_bytes(out, "RIFF", 4u);
  write_u32(out, ChunkSize);
  write_bytes(out, "WAVE", 4u);

  /* Write the "fmt " sub-chunk */
  write_bytes(out, "fmt ", 4u);       /* Subchunk1ID */
  write_u32(out, Subchunk1Size);
  write_u16(out, 1u);                 /* PCM format */
  write_u16(out, NumChannels);
  write_u32(out, SAMPLES_PER_SECOND); /* SampleRate */
  write_u32(out, ByteRate);
  write_u16(out, BlockAlign);
  write_u16(out, BITS_PER_SAMPLE);

  /* Write the beginning of the "data" sub-chunk, but not the actual data */
  write_bytes(out, "data", 4);        /* Subchunk2ID */
  write_u32(out, Subchunk2Size);
}

/*
 * Read a WAVE header from given input stream.
 * Calls fatal_error if data can't be read, if the data
 * doesn't follow the WAVE format, or if the audio
 * parameters of the input WAVE aren't 44.1 KHz, 16 bit
 * signed samples, and two channels.
 *
 * Parameters:
 *   in - the input stream
 *   num_samples - pointer to an unsigned variable where the
 *      number of (stereo) samples following the header
 *      should be stored
 */ 

void read_wave_header(FILE *in, unsigned *num_samples) {
  char label_buf[4];
  uint32_t ChunkSize, Subchunk1Size, SampleRate, ByteRate, Subchunk2Size;
  uint16_t AudioFormat, NumChannels, BlockAlign, BitsPerSample;

  read_bytes(in, label_buf, 4u);
  if (memcmp(label_buf, "RIFF", 4u) != 0) {
    fatal_error("Bad wave header (no RIFF label)");
  }

  read_u32(in, &ChunkSize); /* ignore */


  read_bytes(in, label_buf, 4u);
  if (memcmp(label_buf, "WAVE", 4u) != 0) {
    fatal_error("Bad wave header (no WAVE label)");
  }

  read_bytes(in, label_buf, 4u);
  if (memcmp(label_buf, "fmt ", 4u) != 0) {
    fatal_error("Bad wave header (no 'fmt ' subchunk ID)");
  }

  read_u32(in, &Subchunk1Size);
  if (Subchunk1Size != 16u) {
    fatal_error("Bad wave header (Subchunk1Size was not 16)");
  }

  read_u16(in, &AudioFormat);
  if (AudioFormat != 1u) {
    fatal_error("Bad wave header (AudioFormat is not PCM)");
  }

  read_u16(in, &NumChannels);
  if (NumChannels != NUM_CHANNELS) {
    fatal_error("Bad wave header (NumChannels is not 2)");
  }

  read_u32(in, &SampleRate);
  if (SampleRate != SAMPLES_PER_SECOND) {
    fatal_error("Bad wave header (Unexpected sample rate)");
  }

  read_u32(in, &ByteRate); /* ignore */
  read_u16(in, &BlockAlign); /* ignore */

  read_u16(in, &BitsPerSample);
  if (BitsPerSample != BITS_PER_SAMPLE) {
    fatal_error("Bad wave header (Unexpected bits per sample)");
  }

  read_bytes(in, label_buf, 4u);
  if (memcmp(label_buf, "data", 4u) != 0) {
    fatal_error("Bad wave header (no 'data' subchunk ID)");
  }

  /* finally we're at the Subchunk2Size field, from which we can
   * determine the number of samples */


  read_u32(in, &Subchunk2Size);
  *num_samples = Subchunk2Size / NUM_CHANNELS / (BITS_PER_SAMPLE/8u);
}


/* TODO: add additional functions... */
