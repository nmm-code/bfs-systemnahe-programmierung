/**
 * @file ueb03.c 
 *
 * Hauptprogramm
 * 
 * Diese Datei darf nicht veraendert werden. 
 *
 * @author aan, avh, mhe, mre, tti
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "base64.h"

/**
 * Gibt die Hilfe auf dem uebergebenen Stream (stdout/stderr) aus.
 *
 * @param stream Ausgabestrom
 * @pre stream != NULL
 */
void
printUsage(FILE * stream) {
  assert (stream != NULL);
  
  fprintf(stream, "Usage:\n");
  fprintf(stream, "ueb03 -h\n");
  fprintf(stream, "  shows this help and exits\n");
  fprintf(stream, "- or -\n");
  fprintf(stream, "ueb03 -e INPUTFILE OUTPUTFILE\n");
  fprintf(stream, "  encodes INPUTFILE to OUTPUTFILE with Base64\n");
  fprintf(stream, "- or -\n");
  fprintf(stream, "ueb03 -d INPUTFILE OUTPUTFILE\n");
  fprintf(stream, "  decodes INPUTFILE to OUTPUTFILE with Base64\n");
}

/**
 * Hauptprogramm.
 *
 * Ueberprueft zunaechst die Eingaben auf gueltige Syntax und fuehrt
 * sofern kein Fehler aufgetreten ist die Operation gemaess der
 * Usage aus.
 *
 * @param argc Anzahl der Programmargumente
 * @param argv Array mit den Programmargumenten
 *
 * @return Fehlercode
 */
int
main(int argc, char * argv[]) {
  ErrorSet
      error = ERR_NULL
    ;
  char
      op = '\0'
    , dummy = '\0'
    ;
  
  if (argc == 2) {
    if ((sscanf(argv[1], "-%c%c", &op, &dummy) == 1) && (op == 'h')) {
      printUsage(stdout);
    } else {
      error = ERR_INVALID_CALL;
    }
    
  } else if (argc == 4) {
    if (sscanf(argv[1],"-%c%c", &op, &dummy) != 1) {
      // Parameter hat zu viele Zeichen
      error = ERR_INVALID_CALL;
      
    } else {
      switch(op) {
        case 'e':
          error = base64_encodeFile(argv[2], argv[3]);
          break;
        case 'd':
          error = base64_decodeFile(argv[2], argv[3]);
          break;
        default:
          // unbekannter Parameter
          error = ERR_INVALID_CALL;
      }
    }
  } else {
    // falsche Anzahl an Parametern
    error = ERR_INVALID_CALL;
  }
  
  if (error) {
    printError(stderr, error);
    printUsage(stderr);
  }
  
  return error;
}
