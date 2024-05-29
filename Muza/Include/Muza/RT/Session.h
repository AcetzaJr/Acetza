#pragma once

typedef struct {
  bool runningM;
} MzSessionZ;

extern MzSessionZ MzSessionG;

void MzSessionStartF();
