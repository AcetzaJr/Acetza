#include "Muza/Panic.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void MzPanicF(int codeP, const char *messageP, ...) {
  printf("> Panic: ");
  va_list argsL;
  va_start(argsL, message);
  vprintf(messageP, argsL);
  va_end(argsL);
  printf("\n");
  exit(codeP);
}
