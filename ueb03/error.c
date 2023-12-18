/** 
 * @file error.c 
 *
 * Ausgabe der entsprechenden Fehlermeldungen.
 *
 * @author aan, avh, mhe, mre, tti, Nima, Daniel
 */

#include <assert.h>

#include "error.h"

/**
 * Gibt die uebergebene Zeichenkette aus, wenn das Bit des 
 * uebergebenen ErrorCodes im uebergebenen ErrorSet gesetzt ist.
 * 
 * @param stream Zu nutzender Ausgabestrom
 * @param error BitSet aus Fehlercodes (Fehlermenge)
 * @param flag ErrorCode, dessen Bit in error gesetzt sein muss
 * @param msg Auszugebene Zeichenkette
 * @pre stream != NULL
 * @pre msg != NULL
 */
void
printIfSet(FILE * stream, ErrorSet error, ErrorCode flag, char * msg) {
  assert(stream != NULL);
  assert(msg != NULL);

  if ((error & flag) == flag)
    fprintf(stream,"%s",msg);
}

void
printError(FILE * stream, ErrorSet error) {
  assert (stream != NULL);
  assert (error != ERR_NULL);
  
  fprintf(stream, "ERROR[0x%02X]:\n", error);
  printIfSet(stream, error, ERR_B64_ENCODE,       "  An error occurred while encoding:\n");
  printIfSet(stream, error, ERR_B64_DECODE,       "  An error occurred while decoding:\n");
  printIfSet(stream, error, ERR_SOURCE_FILE,      "  Could not open or read source file.\n");
  printIfSet(stream, error, ERR_DESTINATION_FILE, "  Could not open or write to destination file.\n");
  printIfSet(stream, error, ERR_INVALID_B64_DATA, "  The Base64 data contains invalid data.\n");
  printIfSet(stream, error, ERR_INVALID_CALL,     "  Invalid program call.\n");
}
