#include "Muza/Blocks/Block.h"

#include "Muza/Blocks/Basic.h"
#include "Muza/Blocks/Enveloper.h"
#include "Muza/Blocks/Harmonizer.h"
#include "Muza/Panic.h"
#include "Muza/Types.h"
#include "Muza/Wave.h"

MzBlockZ MzBlockR = {.block = &MzBasicR, .type = MzBasicK};

void MzBlockCopy(MzBlockZ *block, MzBlockZ *from) {
  block->block = from->block;
  block->type = from->type;
}

void MzBlockTypeNotRecognizedPanic(MzBlockTypeE type) {
  MzPanic(1, "waver type with code '%d' not recognized", type);
}

void MzBlockWave(MzBlockZ *block, MzWaveZ *wave) {
  switch (block->type) {
  case MzBlockK:
    MzBlockWave(block->block, wave);
    return;
  case MzBasicK:
    MzBasicWave(block->block, wave);
    return;
  case MzEnveloperK:
    MzEnveloperWave(block->block, wave);
    return;
  case MzHarmonizerK:
    MzHarmonizerWave(block->block, wave);
    return;
  }
  MzBlockTypeNotRecognizedPanic(block->type);
}

MzFrequencyT MzBlockFrequency(MzBlockZ *block) {
  switch (block->type) {
  case MzBlockK:
    return MzBlockFrequency(block->block);
  case MzBasicK:
    return MzBasicFrequency(block->block);
  case MzEnveloperK:
    return MzEnveloperFrequency(block->block);
  case MzHarmonizerK:
    return MzHarmonizerFrequency(block->block);
  }
  MzBlockTypeNotRecognizedPanic(block->type);
  return 0;
}

void MzBlockSetFrequency(MzBlockZ *block, MzFrequencyT frequency) {
  switch (block->type) {
  case MzBlockK:
    MzBlockSetFrequency(block->block, frequency);
    return;
  case MzBasicK:
    MzBasicSetFrequency(block->block, frequency);
    return;
  case MzEnveloperK:
    MzEnveloperSetFrequency(block->block, frequency);
    return;
  case MzHarmonizerK:
    MzHarmonizerSetFrequency(block->block, frequency);
    return;
  }
  MzBlockTypeNotRecognizedPanic(block->type);
}

void MzBlockSetDuration(MzBlockZ *block, MzDurationT duration) {
  switch (block->type) {
  case MzBlockK:
    MzBlockSetDuration(block->block, duration);
    return;
  case MzBasicK:
    MzBasicSetDuration(block->block, duration);
    return;
  case MzEnveloperK:
    MzEnveloperSetDuration(block->block, duration);
    return;
  case MzHarmonizerK:
    MzHarmonizerSetDuration(block->block, duration);
    return;
  }
  MzBlockTypeNotRecognizedPanic(block->type);
}
