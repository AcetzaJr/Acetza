#include "Muza/RT/MidiEvent.h"

#include "Muza/Panic.h"

#include <stdlib.h>

MzMidiEventZ *MzMidiEventCreateF(MzMidiTypeE typeP, void *eventP) {
  switch (typeP) {
  case MzNoteOnEK:
  case MzNoteOffEK:
  case MzPedalOnEK:
  case MzPedalOffEK:
    break;
  default:
    MzPanicF(1, "MzMidiEventCreateF: type with code %d not recognized", typeP);
  }
  MzMidiEventZ *eventL = malloc(sizeof(MzMidiEventZ));
  if (eventL == NULL) {
    MzPanicF(1, "MzMidiEventCreateF failed");
  }
  eventL->eventM = eventP;
  eventL->typeM = typeP;
  return eventL;
}

MzMidiEventZ *MzNoteOnEventCreateF(u8T channelP, u8T keyP, u8T velocityP) {
  MzNoteOnEventZ *eventL = malloc(sizeof(MzNoteOnEventZ));
  if (eventL == NULL) {
    MzPanicF(1, "MzNoteOnEventCreateF failed");
  }
  eventL->channelM = channelP;
  eventL->keyM = keyP;
  eventL->velocityM = velocityP;
  return MzMidiEventCreateF(MzNoteOnEK, eventL);
}

MzMidiEventZ *MzNoteOffEventCreateF(u8T channelP, u8T keyP, u8T velocityP) {
  MzNoteOffEventZ *eventL = malloc(sizeof(MzNoteOffEventZ));
  if (eventL == NULL) {
    MzPanicF(1, "MzNoteOffventCreateF failed");
  }
  eventL->channelM = channelP;
  eventL->keyM = keyP;
  eventL->velocityM = velocityP;
  return MzMidiEventCreateF(MzNoteOffEK, eventL);
}

MzMidiEventZ *MzPedalOnEventCreateF(u8T channelP) {
  MzPedalOnEventZ *eventL = malloc(sizeof(MzPedalOnEventZ));
  if (eventL == NULL) {
    MzPanicF(1, "MzPedalOnEventCreateF failed");
  }
  eventL->channelM = channelP;
  return MzMidiEventCreateF(MzPedalOnEK, eventL);
}

MzMidiEventZ *MzPedalOffEventCreateF(u8T channelP) {
  MzPedalOffEventZ *eventL = malloc(sizeof(MzPedalOffEventZ));
  if (eventL == NULL) {
    MzPanicF(1, "MzPedalOnEventCreateF failed");
  }
  eventL->channelM = channelP;
  return MzMidiEventCreateF(MzPedalOffEK, eventL);
}

void MzMidiEventFreeF(MzMidiEventZ *eventP) {
  free(eventP->eventM);
  free(eventP);
}
