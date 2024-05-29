#include "Muza/RT/MidiThread.h"

#include "Muza/Common.h"
#include "Muza/RT/Session.h"
#include "Muza/RT/Util.h"

#include <portmidi.h>

#include <stdio.h>
#include <threads.h>
#include <time.h>

void MzMidiFlushF(PortMidiStream *streamP) {
  PmEvent bufferL[MzMidiBufferSizeD];
  while (Pm_Read(streamP, bufferL, MzMidiBufferSizeD) > 0) {
  }
}

void MzMidiHandleEventF(PmEvent *eventP) {
  // printf("time: %d\n", eventP->timestamp);
  u8T bytesL[4];
  bytesL[0] = eventP->message;
  bytesL[1] = eventP->message >> 8;
  bytesL[2] = eventP->message >> 16;
  bytesL[3] = eventP->message >> 24;
  printf("{");
  for (int byteIndexL = 0; byteIndexL < 4; byteIndexL++) {
    printf(" [");
    printf(" Byte(%d) ", byteIndexL);
    printf("Dec(%3d) ", bytesL[byteIndexL]);
    printf("Hex(%02x) ", bytesL[byteIndexL]);
    printf("Bin(%08b) ", bytesL[byteIndexL]);
    printf("] ");
  }
  printf("}\n");
}

int MzMidiHandlerF(void *dataP) {
  struct timespec sleepTimeL = {.tv_nsec = 16'000'000};
  PortMidiStream *streamL = dataP;
  Pm_SetChannelMask(streamL, Pm_Channel(0));
  PmEvent bufferL[MzMidiBufferSizeD];
  int countL;
  while (MzSessionG.runningM) {
    while ((countL = Pm_Read(streamL, bufferL, MzMidiBufferSizeD) > 0)) {
      for (int indexL = 0; indexL < countL; indexL++) {
        MzMidiHandleEventF(&bufferL[indexL]);
      }
    }
    thrd_sleep(&sleepTimeL, NULL);
  }
  MzMidiFlushF(streamL);
  return 0;
}
