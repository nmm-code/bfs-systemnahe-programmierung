#ifndef __ERROR_H__
#define __ERROR_H__

/**
 * Schnittstelle eines Moduls zur Fehlerbehandlung
 *
 * Diese Datei darf nicht veraendert werden.
 *
 * @author mhe, mre, tti
 */

#include <stdio.h>

/**
 * Aufzaehlung von Fehlerfaellen
 */
enum ErrorCode {
  /** kein Fehler */
  ERR_NULL = 0,

  /** Es wurden falsche oder ungueltige Argumente eingegeben */
  ERR_WRONG_ARG,

  /** Das Lesen aus dem Stream ist fehlgeschlagen */
  ERR_READ_STREAM,

  /** Das Schreiben in den Stream ist fehlgeschlagen */
  ERR_WRITE_STREAM,

  /** Speicherleck */
  ERR_MEMORY_LEAK,

  /** Fehler beim Allozieren von Speicher */
  ERR_OUT_OF_MEMORY
};

/**
 * Aufzaehlungstyp fuer Fehlerfaelle
 */
typedef enum ErrorCode ErrorCode;

/**
 * Funktion zur Behandlung von Fehlerfaellen
 *
 * In allen Fehlerfaellen wird lediglich eine aussagekraeftige Fehlermeldung
 * auf stream ausgegeben.
 *
 * @param[in] stream Ausgabestrem
 * @param     error  Fehlercode
 *
 * @pre stream != NULL
 */
void error_print(FILE * stream, ErrorCode error);

#endif
