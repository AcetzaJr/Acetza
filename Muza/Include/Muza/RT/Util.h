#pragma once

#include <portmidi.h>

#define MzMidiBufferSizeD 512

void MzInitRT();

void MzEndRT();

PortMidiStream *MzSelectMidiInput();

PortMidiStream *MzOpenMidiInput(int deviceID);
