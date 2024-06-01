#include "Muza/RT/MidiThread.h"

#include "Muza/Common.h"
#include "Muza/RT/MidiEvent.h"
#include "Muza/RT/Session.h"
#include "Muza/RT/Util.h"
#include "glib.h"

#include <portmidi.h>

#include <stdio.h>
#include <stdlib.h>

void MzMidiFlushF(PortMidiStream *streamP) {
  PmEvent bufferL[MzMidiBufferSizeD];
  while (Pm_Read(streamP, bufferL, MzMidiBufferSizeD) > 0) {
  }
}

void MzMidiPrintEventF(PmEvent *eventP) {
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

void MzMidiSendEventF(PmEvent *eventP) {
  // printf("time: %d\n", eventP->timestamp);
  u8T bytesL[4];
  bytesL[0] = eventP->message;
  bytesL[1] = eventP->message >> 8;
  bytesL[2] = eventP->message >> 16;
  // bytesL[3] = eventP->message >> 24;
  u8T halfByteL = bytesL[0] >> 4;
  switch (halfByteL) {
  case 9:
    g_async_queue_push(
        MzSessionG.midiQueueM,
        MzNoteOnEventCreateF(bytesL[0] & 0xf, bytesL[1], bytesL[2]));
    return;
  case 8:
    g_async_queue_push(
        MzSessionG.midiQueueM,
        MzNoteOffEventCreateF(bytesL[0] & 0xf, bytesL[1], bytesL[2]));
    return;
  case 11:
    if (bytesL[1] == 64) {
      if (bytesL[2] < 64) {
        g_async_queue_push(MzSessionG.midiQueueM,
                           MzPedalOffEventCreateF(bytesL[0] & 0xf));
      } else {
        g_async_queue_push(MzSessionG.midiQueueM,
                           MzPedalOnEventCreateF(bytesL[0] & 0xf));
      }
      return;
    }
  }
}

gpointer MzMidiDispatcherF(gpointer streamP) {
  PortMidiStream *streamL = streamP;
  Pm_SetChannelMask(streamL, Pm_Channel(0));
  PmEvent bufferL[MzMidiBufferSizeD];
  int countL;
  while (MzSessionG.runningM) {
    while ((countL = Pm_Read(streamL, bufferL, MzMidiBufferSizeD) > 0)) {
      for (int indexL = 0; indexL < countL; indexL++) {
        MzMidiSendEventF(&bufferL[indexL]);
      }
    }
    g_usleep(1'000);
  }
  MzMidiFlushF(streamL);
  return NULL;
}
