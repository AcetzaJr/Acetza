#pragma once

#include "Muza/Common.h"

typedef enum {
  MzNoteOnEK,
  MzNoteOffEK,
  MzPedalOnEK,
  MzPedalOffEK,
} MzMidiTypeE;

typedef struct {
  void *eventM;
  MzMidiTypeE typeM;
} MzMidiEventZ;

typedef struct {
  u8T channelM;
  u8T keyM;
  u8T velocityM;
} MzNoteOnEventZ;

typedef struct {
  u8T channelM;
  u8T keyM;
  u8T velocityM;
} MzNoteOffEventZ;

typedef struct {
  u8T channelM;
} MzPedalOnEventZ;

typedef struct {
  u8T channelM;
} MzPedalOffEventZ;

MzMidiEventZ *MzMidiEventCreateF(MzMidiTypeE typeP, void *eventP);

MzMidiEventZ *MzNoteOnEventCreateF(u8T channelP, u8T keyP, u8T velocityP);

MzMidiEventZ *MzNoteOffEventCreateF(u8T channelP, u8T keyP, u8T velocityP);

MzMidiEventZ *MzPedalOnEventCreateF(u8T channelP);

MzMidiEventZ *MzPedalOffEventCreateF(u8T channelP);

void MzMidiEventFreeF(MzMidiEventZ *eventP);
