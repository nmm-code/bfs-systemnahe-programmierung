#ifndef __ERROR_H__
#define __ERROR_H__
/**
 * @file error.h
 *
 * Definition der Fehlercodes / Fehlerfaelle.
 *
 * Diese Datei darf nicht veraendert werden. 
 * 
 * @author aan, avh, mhe, mre, tti
 */

#include <stdio.h>

/**
 * Aufzaehlung aller moeglichen Fehlerfaelle.
 */
typedef enum {
  /** Alles gut - kein Fehler */
  ERR_NULL              = 0x00,
  /** Fehler beim Oeffnen oder Lesen der Quelldatei */
  ERR_SOURCE_FILE       = 0x01,
  /** Fehler beim Oeffnen oder Beschreiben der Zieldatei */
  ERR_DESTINATION_FILE  = 0x02,
  /** Ungueltige Base64-Daten waehrend decode */
  ERR_INVALID_B64_DATA  = 0x04,
  /** Signalisierung: Fehler waehrend encode */
  ERR_B64_ENCODE        = 0x10,
  /** Signalisierung: Fehler waehrend decode */
  ERR_B64_DECODE        = 0x20,
  /** Ungueltiger Programmaufruf */
  ERR_INVALID_CALL      = 0x40,
} ErrorCode;

/**
 * Datentyp fuer Fehlermengen, eine Bitmenge aus ErrorCodes
 */
typedef int ErrorSet;

/**
 * Schreibt die uebergebenen Fehlermeldungen in den uebergebenen Ausgabestrom.
 * 
 * @param stream Zu nutzender Ausgabestrom
 * @param error Fehlermenge mit Fehlercodes
 * @pre stream != NULL
 * @pre error != ERR_NULL
 */
void printError(FILE * stream, ErrorSet error);

#endif
 