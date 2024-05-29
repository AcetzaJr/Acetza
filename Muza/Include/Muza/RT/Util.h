#pragma once

#include <portmidi.h>

#define MzMidiBufferSizeD 512

void MzInitRTF();

void MzEndRTF();

PortMidiStream *MzSelectMidiInputF();

PortMidiStream *MzOpenMidiInputF(int deviceID);
