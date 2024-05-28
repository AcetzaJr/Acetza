
#include "Muza/Measure.h"
#include "Muza/RT/Session.h"

#include <stddef.h>

void Test1F(void * /*dataP*/) {
  MzInitRT();
  MzSelectDevice();
  MzEndRT();
}

int main() { MzMeasureF(Test1F, NULL); }
