/**
 * Implementierung eines Moduls zur Fehlerbehandlung
 *
 * Diese Datei darf nicht veraendert werden.
 *
 * @author mhe, mre, tti
 */

#include "error.h"


void
error_print(FILE * stream, ErrorCode error) {
  switch (error) {
    case ERR_NULL:
      fprintf(stream, "Error! No Error - should not see me!\n");
      break;
    case ERR_WRONG_ARG:
      fprintf(stream, "Syntax error! Wrong argument!\n");
      break;
    case ERR_READ_STREAM:
      fprintf(stream, "Error! Could not read from stream!\n");
      break;
    case ERR_WRITE_STREAM:
      fprintf(stream, "Error! Could not write to stream!\n");
      break;
    case ERR_MEMORY_LEAK:
      fprintf(stream, "Error! Memory Leak!\n");
      break;
    case ERR_OUT_OF_MEMORY:
      fprintf(stream, "PANIC! Out of memory!\n");
      break;
    default:
      fprintf(stream, "Error! Unknown ErrorCode!\n");
      break;
  }
}
