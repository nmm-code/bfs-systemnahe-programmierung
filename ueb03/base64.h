#ifndef __BASE64_H__
#define __BASE64_H__

/**
 * @file base64.h
 * 
 * Schnittstelle des Base64-Moduls
 * 
 * Diese Datei darf nicht veraendert werden. 
 * 
 * @author aan, avh, mhe, mre, tti
 * 
 */

#include <stdio.h>

#include "error.h"

/**
 * Kodiert eine Binaerdatei mit Base64 zu einer ASCII-Textdatei.
 * 
 * @param char * source Dateiname der Quelldatei
 * @param char * dest Dateiname der Zieldatei
 * @pre source != NULL 
 * @pre dest != NULL
 * @return ErrorSet mit moeglichen Fehlercodes:
 *  - ERR_ENCODE Ein Fehler ist aufgetreten.
 *  - ERR_SOURCE_FILE Fehler beim Oeffnen oder Lesen der Quelldatei
 *  - ERR_DESTINATION_FILE Fehler beim Oeffnen oder Beschreiben der Zieldatei
 */
ErrorSet base64_encodeFile(char * source, char * dest); 

/**
 * Dekodiert eine mit Base64 kodierte Quelldatei zu einer Binaerdatei.
 * 
 * @param char * source Dateiname der Quelldatei
 * @param char * dest Dateiname der Zieldatei
 * @pre source != NULL 
 * @pre dest != NULL
 * @return ErrorSet mit moeglichen Fehlercodes:
 *  - ERR_DECODE Ein Fehler ist aufgetreten.
 *  - ERR_SOURCE_FILE Fehler beim Oeffnen oder Lesen der Quelldatei
 *  - ERR_DESTINATION_FILE Fehler beim Oeffnen oder Beschreiben der Zieldatei
 */
ErrorSet base64_decodeFile(char * source, char * dest);

/**
 * Kodiert einen Stream mit Binaerdaten mit Base64 zu einem ASCII-Text.
 * 
 * @param FILE * source Quelldatei
 * @param FILE * dest Zieldatei
 * @pre source != NULL
 * @pre dest != NULL
 * @return ErrorSet mit moeglichen Fehlercodes:
 *  - ERR_ENCODE Ein Fehler ist aufgetreten.
 *  - ERR_SOURCE_FILE Quelldatei nicht lesbar
 *  - ERR_DESTINATION_FILE Zieldatei nicht beschreibbar
 */
ErrorSet base64_encodeStream(FILE * source, FILE * dest);

/**
 * Dekodiert einen Stream mit mit Base64 kodierten Daten zu einem
 * Stream mit Binaerdaten.
 * 
 * @param FILE * source Quelldatei
 * @param FILE * dest Zieldatei
 * @pre source != NULL
 * @pre dest != NULL
 * @return ErrorSet mit moeglichen Fehlercodes:
 *  - ERR_DECODE Ein Fehler ist aufgetreten.
 *  - ERR_SOURCE_FILE Quelldatei nicht lesbar
 *  - ERR_DESTINATION_FILE Zieldatei nicht beschreibbar
 *  - ERR_INVALID_B64_DATA Ungueltiges Zeichen in der Quelldatei oder
 *    Fehlendes Zeichen in der Quelldatei (Anzahl der Zeichen % 4 != 0)
 */
ErrorSet base64_decodeStream(FILE * source, FILE * dest);

#endif
