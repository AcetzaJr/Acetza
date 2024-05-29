#include "Muza/RT/Util.h"

#include "Muza/Panic.h"

#include <portaudio.h>
#include <portmidi.h>
#include <porttime.h>

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void MzInitRTF() {
  if (Pm_Initialize() != pmNoError) {
    MzPanicF(1, "Pm_Initialize failed");
  }
  if (Pt_Start(1, NULL, NULL) != ptNoError) {
    MzPanicF(1, "Pt_Start failed");
  };
  if (Pa_Initialize() != paNoError) {
    MzPanicF(1, "Pa_Initialize failed");
  }
}

void MzEndRTF() {
  if (Pa_Terminate() != paNoError) {
    MzPanicF(1, "Pa_Terminate failed");
  }
  if (Pt_Stop() != ptNoError) {
    MzPanicF(1, "Pt_Stop failed");
  }
  if (Pm_Terminate() != pmNoError) {
    MzPanicF(1, "Pm_Terminate failed");
  }
}

PortMidiStream *MzSelectMidiInputF() {
  while (true) {
    for (int indexL = 0; indexL < Pm_CountDevices(); indexL++) {
      const PmDeviceInfo *infoL = Pm_GetDeviceInfo(indexL);
      if (infoL->input) {
        printf("> Device index: %d\n", indexL);
        printf("    name: %s\n", infoL->name);
        printf("    API: %s\n", infoL->interf);
        printf("\n");
      }
    }
    char *choiceStringL = NULL;
    size_t lenL;
    printf("Select by index: ");
    int readL = getline(&choiceStringL, &lenL, stdin);
    if (readL == -1) {
      printf("> Could not read user input");
      goto continueLB;
    }
    choiceStringL[readL - 1] = '\0';
    char *checkL = NULL;
    long choiceIndexL = strtol(choiceStringL, &checkL, 10);
    if (checkL == choiceStringL) {
      printf("> Input must be an integer\n");
      goto continueLB;
    }
    PortMidiStream *streamL = NULL;
    if (Pm_OpenInput(&streamL, choiceIndexL, NULL, MzMidiBufferSizeD, NULL,
                     NULL)) {
      printf("> Input device with id %ld could not be opened\n", choiceIndexL);
      goto continueLB;
    }
    return streamL;
  continueLB:
    free(choiceStringL);
    printf("> Press enter to try again...");
    while (getchar() != '\n') {
    }
    printf("\n");
  }
}

PortMidiStream *MzOpenMidiInputF(int deviceIDP) {
  PortMidiStream *streamL = NULL;
  if (Pm_OpenInput(&streamL, deviceIDP, NULL, MzMidiBufferSizeD, NULL, NULL)) {
    MzPanicF(1, "input device with id %d could not be opened\n", deviceIDP);
  }
  return streamL;
}
