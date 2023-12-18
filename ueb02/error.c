/**
 * @file error.c
 *
 * Ausgabe der entsprechenden Fehlermeldungen.
 *
 * Diese Datei darf nicht veraendert werden.
 *
 * @author mhe, mre, tti
 */

#include <stdio.h>
#include <assert.h>
#include "error.h"

void
printError(FILE * stream, ErrorCode error) {

  assert (stream != NULL);

  char * format = "Error: %s\n";

  switch (error) {
    case ERR_NULL:
      fprintf(stream, format, "Should not see me! No error occurred.");
      break;
    case ERR_CALL_MISSING_ARGS:
      fprintf(stream, format, "No arguments given.");
      break;
    case ERR_UNKNOWN_OPERATION:
      fprintf(stream, format, "Unknown Operation.");
      break;
    case ERR_TEXT_MISSING_TEXT:
      fprintf(stream, format, "Missing text.");
      break;
    case ERR_TEXT_ILLEGAL_CHAR:
      fprintf(stream, format, "Illegal character in given text.");
      break;
    case ERR_TEXT_TOO_LONG:
      fprintf(stream, format, "Given Text too long.");
      break;
    case ERR_ENCODE_WITHOUT_CIPHER:
    case ERR_DECODE_WITHOUT_CIPHER:
      fprintf(stream, format, "No cipher algorithm selected.");
      break;
    case ERR_CAESAR_MISSING_ROTATION:
    case ERR_CAESAR_INVALID_ROTATION:
      fprintf(stream, format, "Missing or invalid rotation for caesar cipher.");
      break;
    case ERR_VIGENERE_MISSING_KEY:
    case ERR_VIGENERE_EMPTY_KEY:
    case ERR_VIGENERE_KEY_TOO_LONG:
    case ERR_VIGENERE_KEY_ILLEGAL_CHAR:
      fprintf(stream, format, "Missing, empty or invalid key for vigenere cipher.");
      break;
    case ERR_UNKNOWN:
    default:
      fprintf(stream, format, "An unknown error occurred.");
      break;
  }

}
