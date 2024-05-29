#pragma once

#include <portaudio.h>

int MzAudioCallbackF(const void *inputP, void *outputP,
                     unsigned long framesCountP,
                     const PaStreamCallbackTimeInfo *timeInfoP,
                     PaStreamCallbackFlags statusFlagsP, void *userDataP);
