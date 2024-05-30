#pragma once

#include "Muza/RT/BufferBlock.h"

typedef void (*MzNoteOnT)(void *dataP, void *synthP, u8T channelP, u8T keyP,
                          u8T velocityP);

typedef void (*MzNoteOffT)(void *dataP, void *synthP, u8T channelP, u8T keyP,
                           u8T velocityP);

typedef void (*MzPedalOnT)(void *dataP, void *synthP, u8T channelP);

typedef void (*MzPedalOffT)(void *dataP, void *synthP, u8T channelP);

typedef void (*MzProcessBlockT)(void *dataP, void *synthP,
                                MzBufferBlockZ *blockP);

typedef void (*MzEndProcessBlockT)(void *dataP, void *synthP,
                                   MzBufferBlockZ *blockP);

typedef void (*MzFreeSynthT)(void *dataP, void *synthP);
