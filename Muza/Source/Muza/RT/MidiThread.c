#include "Muza/RT/MidiThread.h"

#include "Muza/Common.h"
#include "Muza/RT/Session.h"
#include "Muza/RT/Util.h"

#include <portmidi.h>

#include <stdio.h>

int MzMidiHandler(void *dataP) {
  PortMidiStream *streamL = dataP;
  Pm_SetChannelMask(streamL, Pm_Channel(0));
  PmEvent bufferL[MzMidiBufferSizeD];
  while (MzSessionG.runningM) {
    int countL = Pm_Read(streamL, bufferL, MzMidiBufferSizeD);
    if (countL <= 0) {
      continue;
    }
    printf("%d messages arrived\n", countL);
    for (int indexL = 0; indexL < countL; indexL++) {
      printf("time: %d\n", bufferL[indexL].timestamp);
      u8T bytesL[4];
      bytesL[0] = bufferL[indexL].message;
      bytesL[1] = bufferL[indexL].message >> 8;
      bytesL[2] = bufferL[indexL].message >> 16;
      bytesL[3] = bufferL[indexL].message >> 24;
      printf("{");
      for (int byteIndexL = 0; byteIndexL < 4; byteIndexL++) {
        printf(" [");
        printf(" Byte(%d) ", byteIndexL);
        printf("Dec(%3d) ", bytesL[byteIndexL]);
        printf("Hex(%02x) ", bytesL[byteIndexL]);
        printf("Bin(%08b) ", bytesL[byteIndexL]);
        printf("] ");
      }
      printf("}");
    }
    printf("\n");
  }
  return 0;
}
