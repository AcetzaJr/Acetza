#include "Muza/Wave.h"

#include "Muza/Common.h"
#include "Muza/Panic.h"

#include <sndfile-64.h>
#include <stddef.h>

void MzWaveSaveF(MzWaveZ *wave, const char *path) {
  SF_INFO info;
  info.samplerate = (int)wave->frameRateM;
  info.channels = (int)wave->channelsM;
  info.format = SF_FORMAT_WAV | SF_FORMAT_DOUBLE;
  SNDFILE *file = sf_open(path, SFM_WRITE, &info);
  if (file == NULL) {
    MzPanicF(1, "file %s could not be opened", path);
  }
  u64T written =
      sf_writef_double(file, wave->samples, (sf_count_t)wave->frames);
  if (written != wave->frames) {
    MzPanicF(1, "%ld frames written but %ld requested", written, wave->frames);
  }
  sf_close(file);
}
