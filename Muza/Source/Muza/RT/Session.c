#include "Muza/RT/Session.h"

#include <portmidi.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void MzInitRT() { Pm_Initialize(); }

void MzEndRT() { Pm_Terminate(); }

PmDeviceID MzSelectDevice() {
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
    return choiceIndexL;
  continueLB:
    free(choiceStringL);
    printf("> Press enter to try again: ");
    while (getchar() != '\n') {
    }
  }
}
