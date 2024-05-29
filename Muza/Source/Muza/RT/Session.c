#include "Muza/RT/Session.h"

#include "Muza/RT/MidiThread.h"
#include "Muza/RT/Util.h"

#include <portmidi.h>

#include <stddef.h>
#include <stdio.h>
#include <threads.h>

int MzDefaultDeviceIDG = 3;
MzSessionZ MzSessionG = {.runningM = false};

void MzSessionStart() {
  MzInitRT();
  PortMidiStream *streamL = MzOpenMidiInput(MzDefaultDeviceIDG);
  MzSessionG.runningM = true;
  thrd_t threadL;
  thrd_create(&threadL, MzMidiHandler, streamL);
  printf("> Press enter to exit session...\n");
  while (getchar() != '\n') {
  }
  MzSessionG.runningM = false;
  thrd_join(threadL, NULL);
  MzEndRT();
}
