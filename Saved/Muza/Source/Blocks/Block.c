#include "Muza/Blocks/Block.h"

#include "Muza/Blocks/Basic.h"
#include "Muza/Blocks/Enveloper.h"
#include "Muza/Blocks/Harmonizer.h"
#include "Muza/Panic.h"
#include "Muza/Types.h"
#include "Muza/Wave.h"

MzBufferBlockZ MzBlockG = {.blockM = &MzBasicG, .typeM = MzBasicEK};

void MzBlockCopyF(MzBufferBlockZ *blockP, MzBufferBlockZ *fromP) {
  blockP->blockM = fromP->blockM;
  blockP->typeM = fromP->typeM;
}

void MzBlockTypeNotRecognizedPanicF(MzBlockTypeE typeP) {
  MzPanicF(1, "waver type with code '%d' not recognized", typeP);
}

void MzBlockWaveF(MzBufferBlockZ *blockP, MzWaveZ *waveP) {
  switch (blockP->typeM) {
  case MzBlockEK:
    MzBlockWaveF(blockP->blockM, waveP);
    return;
  case MzBasicEK:
    MzBasicWaveF(blockP->blockM, waveP);
    return;
  case MzEnveloperEK:
    MzEnveloperWaveF(blockP->blockM, waveP);
    return;
  case MzHarmonizerEK:
    MzHarmonizerWaveF(blockP->blockM, waveP);
    return;
  }
  MzBlockTypeNotRecognizedPanicF(blockP->typeM);
}

MzFrequencyT MzBlockFrequencyF(MzBufferBlockZ *blockP) {
  switch (blockP->typeM) {
  case MzBlockEK:
    return MzBlockFrequencyF(blockP->blockM);
  case MzBasicEK:
    return MzBasicFrequencyF(blockP->blockM);
  case MzEnveloperEK:
    return MzEnveloperFrequencyF(blockP->blockM);
  case MzHarmonizerEK:
    return MzHarmonizerFrequencyF(blockP->blockM);
  }
  MzBlockTypeNotRecognizedPanicF(blockP->typeM);
  return 0;
}

void MzBlockSetFrequencyF(MzBufferBlockZ *blockP, MzFrequencyT frequencyP) {
  switch (blockP->typeM) {
  case MzBlockEK:
    MzBlockSetFrequencyF(blockP->blockM, frequencyP);
    return;
  case MzBasicEK:
    MzBasicSetFrequencyF(blockP->blockM, frequencyP);
    return;
  case MzEnveloperEK:
    MzEnveloperSetFrequencyF(blockP->blockM, frequencyP);
    return;
  case MzHarmonizerEK:
    MzHarmonizerSetFrequencyF(blockP->blockM, frequencyP);
    return;
  }
  MzBlockTypeNotRecognizedPanicF(blockP->typeM);
}

void MzBlockSetDurationF(MzBufferBlockZ *blockP, MzDurationT durationP) {
  switch (blockP->typeM) {
  case MzBlockEK:
    MzBlockSetDurationF(blockP->blockM, durationP);
    return;
  case MzBasicEK:
    MzBasicSetDurationF(blockP->blockM, durationP);
    return;
  case MzEnveloperEK:
    MzEnveloperSetDurationF(blockP->blockM, durationP);
    return;
  case MzHarmonizerEK:
    MzHarmonizerSetDurationF(blockP->blockM, durationP);
    return;
  }
  MzBlockTypeNotRecognizedPanicF(blockP->typeM);
}
