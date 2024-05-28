#include "Muza/RT/Session.h"

#include "Muza/Common.h"
#include "Muza/Panic.h"

#include <portmidi.h>
#include <porttime.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <time.h>

#define MzMidiBufferSizeD 512

int MzDefaultDeviceIDG = 3;
bool MzSessionRunningG;

void MzInitRT() {
  if (Pm_Initialize() != pmNoError) {
    MzPanicF(1, "Pm_Initialize failed");
  }
  if (Pt_Start(1, NULL, NULL) != ptNoError) {
    MzPanicF(1, "Pt_Start failed");
  };
}

void MzEndRT() {
  Pt_Stop();
  Pm_Terminate();
}

PortMidiStream *MzSelectMidiInput() {
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

PortMidiStream *MzOpenMidiInput(int deviceID) {
  PortMidiStream *streamL = NULL;
  if (Pm_OpenInput(&streamL, deviceID, NULL, MzMidiBufferSizeD, NULL, NULL)) {
    MzPanicF(1, "input device with id %d could not be opened\n", deviceID);
  }
  return streamL;
}

int MzMidiHandler(void *dataP) {
  PortMidiStream *streamL = dataP;
  // Pm_SetFilter(streamL, PM_FILT_NOTE);
  PmEvent bufferL[MzMidiBufferSizeD];
  while (MzSessionRunningG) {
    int countL = Pm_Read(streamL, bufferL, MzMidiBufferSizeD);
    if (countL <= 0) {
      continue;
    }
    printf("%d messages arrived\n", countL);
    for (int indexL = 0; indexL < countL; indexL++) {
      u8T bytesL[4];
      bytesL[0] = bufferL[indexL].message;
      bytesL[1] = bufferL[indexL].message >> 8;
      bytesL[2] = bufferL[indexL].message >> 16;
      bytesL[3] = bufferL[indexL].message >> 24;
      printf("[");
      for (int byteIndexL = 0; byteIndexL < 4; byteIndexL++) {
        printf("(%08b)", bytesL[byteIndexL]);
      }
      printf("]");
    }
    printf("\n");
  }
  return 0;
}

void MzSessionStart() {
  MzInitRT();
  PortMidiStream *streamL = MzOpenMidiInput(MzDefaultDeviceIDG);
  MzSessionRunningG = true;
  thrd_t threadL;
  thrd_create(&threadL, MzMidiHandler, streamL);
  printf("> Press enter to exit session...\n");
  while (getchar() != '\n') {
  }
  MzSessionRunningG = false;
  thrd_join(threadL, NULL);
  MzEndRT();
}
