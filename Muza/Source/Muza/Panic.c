#include "Muza/Panic.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void MzPanic(int code, const char *message, ...) {
  printf("> Panic: ");
  va_list args;
  va_start(args, message);
  vprintf(message, args);
  va_end(args);
  printf("\n");
  exit(code);
}
