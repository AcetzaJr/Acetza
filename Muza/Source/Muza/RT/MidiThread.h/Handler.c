#include "Muza/RT/MidiThread.h"

#include "Muza/RT/MidiEvent.h"
#include "Muza/RT/Session.h"

#include <stdio.h>

void MzSendNoteOnF(MzNoteOnEventZ *eventP) {
  MzSessionG.synthM->noteOnM(NULL, MzSessionG.synthM->synthM, eventP->channelM,
                             eventP->keyM, eventP->velocityM);
}

void MzSendNoteOffF(MzNoteOffEventZ *eventP) {
  MzSessionG.synthM->noteOffM(NULL, MzSessionG.synthM->synthM, eventP->channelM,
                              eventP->keyM, eventP->velocityM);
}

void MzSendPedalOnF(MzPedalOnEventZ *eventP) {
  MzSessionG.synthM->pedalOnM(NULL, MzSessionG.synthM->synthM,
                              eventP->channelM);
}

void MzSendPedalOffF(MzPedalOffEventZ *eventP) {
  MzSessionG.synthM->pedalOffM(NULL, MzSessionG.synthM->synthM,
                               eventP->channelM);
}

gpointer MzMidiHandlerF(gpointer /*dataP*/) {
  while (MzSessionG.runningM) {
    MzMidiEventZ *eventL =
        g_async_queue_timeout_pop(MzSessionG.midiQueueM, 100'000);
    if (eventL == NULL) {
      continue;
    }
    switch (eventL->typeM) {
    case MzNoteOnEK:
      printf("MzNoteOnEK\n");
      MzSendNoteOnF(eventL->eventM);
      break;
    case MzNoteOffEK:
      printf("MzNoteOffEK\n");
      MzSendNoteOffF(eventL->eventM);
      break;
    case MzPedalOnEK:
      printf("MzPedalOnEK\n");
      MzSendPedalOnF(eventL->eventM);
      break;
    case MzPedalOffEK:
      printf("MzPedalOffEK\n");
      MzSendPedalOffF(eventL->eventM);
      break;
    }
    MzMidiEventFreeF(eventL);
    // printf("block processed\n");
  }
  return NULL;
}
