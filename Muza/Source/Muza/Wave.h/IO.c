#include "Muza/Wave.h"

#include "Muza/Common.h"
#include "Muza/Panic.h"

#include <sndfile-64.h>
#include <stddef.h>

void MzWaveSave(MzWaveZ *wave, const char *path) {
  SF_INFO info;
  info.samplerate = (int)wave->frameRate;
  info.channels = (int)wave->channels;
  info.format = SF_FORMAT_WAV | SF_FORMAT_DOUBLE;
  SNDFILE *file = sf_open(path, SFM_WRITE, &info);
  if (file == NULL) {
    MzPanic(1, "file %s could not be opened", path);
  }
  u64 written = sf_writef_double(file, wave->samples, (sf_count_t)wave->frames);
  if (written != wave->frames) {
    MzPanic(1, "%ld frames written but %ld requested", written, wave->frames);
  }
  sf_close(file);
}
