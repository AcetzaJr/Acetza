#include "Muza/Wave.h"

#include "Muza/Common.h"
#include "Muza/Panic.h"

#include <sndfile-64.h>
#include <stddef.h>

void MzWaveSaveF(MzWaveZ *waveP, const char *pathP) {
  SF_INFO infoL;
  infoL.samplerate = (int)waveP->frameRateM;
  infoL.channels = (int)waveP->channelsM;
  infoL.format = SF_FORMAT_WAV | SF_FORMAT_DOUBLE;
  SNDFILE *fileL = sf_open(pathP, SFM_WRITE, &infoL);
  if (fileL == NULL) {
    MzPanicF(1, "file %s could not be opened", pathP);
  }
  u64T writtenL =
      sf_writef_double(fileL, waveP->samplesM, (sf_count_t)waveP->framesM);
  if (writtenL != waveP->framesM) {
    MzPanicF(1, "%ld frames written but %ld requested", writtenL,
             waveP->framesM);
  }
  sf_close(fileL);
}
