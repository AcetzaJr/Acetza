#pragma once

#include "Muza/Blocks/Block.h"

typedef void (*MzNoteOnT)(void *dataP);

typedef void (*MzNoteOffT)(void *dataP);

typedef void (*MzProcessBlockT)(void *dataP, MzBufferBlockZ *blockP);
