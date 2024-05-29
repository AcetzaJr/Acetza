#include "Muza/RT/MidiEvent.h"
#include "Muza/RT/MidiThread.h"

#include "Muza/RT/Session.h"
#include <stdio.h>

int MzMidiHandlerF(void * /*dataP*/) {
  while (MzSessionG.runningM) {
    MzMidiEventZ *eventL =
        g_async_queue_timeout_pop(MzSessionG.midiQueueM, 100'000);
    if (eventL == NULL) {
      continue;
    }
    switch (eventL->typeM) {
    case MzNoteOnEK:
      printf("MzNoteOnEK\n");
      break;
    case MzNoteOffEK:
      printf("MzNoteOffEK\n");
      break;
    case MzPedalOnEK:
      printf("MzPedalOnEK\n");
      break;
    case MzPedalOffEK:
      printf("MzPedalOffEK\n");
      break;
    }
    MzMidiEventFreeF(eventL);
    // printf("block processed\n");
  }
  return 0;
}
