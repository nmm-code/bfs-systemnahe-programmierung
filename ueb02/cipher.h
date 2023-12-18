#ifndef __CIPHER_H__
#define __CIPHER_H__
/**
 * @file cipher.h
 *
 * Schnittstellendefinition des Moduls mit
 * Verschluesselungsfunktionen.
 *
 * Diese Datei darf nicht veraendert werden.
 *
 * @author mhe, mre, tti
 *
 */

#include <stdio.h>
#include "error.h"

/** Sofern nicht vom Compiler festgelegt, definiere eine maximale Laenge. */
#ifndef MAX_TEXT_LENGTH
#define MAX_TEXT_LENGTH 30
#endif

/** Sofern nicht vom Compiler festgelegt, definiere das kleinste Zeichen. */
#ifndef SMALLEST_CHAR
#define SMALLEST_CHAR ' '
#endif

/** Sofern nicht vom Compiler festgelegt, definiere das groesste Zeichen. */
#ifndef BIGGEST_CHAR
#define BIGGEST_CHAR '~'
#endif


/** Typendefinition fuer einen Text. */
typedef unsigned char Text[MAX_TEXT_LENGTH + 1]; // inkl. Nulltermination

/** Leerer Text zur Variableninitialisierung. */
#define EMPTY_TEXT {0}

/**
 * Verschluesselt einen Text mit Caesar-Chiffre, dabei wird der uebergebene
 * Text veraendert.
 *
 * @param[in]  plain Klartext
 * @param[out] plain Kryptotext
 * @param      rot   Rotation
 *
 * @pre plain != NULL
 *
 */
void caesarEncode(Text plain, unsigned int rot);

/**
 * Verschluesselt einen Text mit Vigenere-Chiffre, dabei wird der uebergebene
 * Text veraendert.
 *
 * @param[in]  plain Klartext
 * @param[out] plain Kryptotext
 * @param[in]  pass  Passwort
 *
 * @pre plain != NULL
 * @pre pass != NULL
 * @pre pass ist nicht leer
 *
 */
void vigenereEncode(Text plain, Text pass);

/**
 * Entschluesselt einen Text mit Caesar-Chiffre, dabei wird der uebergebene
 * Text veraendert.
 *
 * @param[in]  plain Kryptotext
 * @param[out] plain Klartext
 * @param      rot Rotation
 *
 * @pre plain != NULL
 *
 */
void caesarDecode(Text plain, unsigned int rot);

/**
 * Entschluesselt einen Text mit Vigenere-Chiffre, dabei wird der uebergebene
 * Text veraendert.
 *
 * @param[in]  plain Kryptotext
 * @param[out] plain Klartext
 * @param[in]  pass  Passwort
 *
 * @pre plain != NULL
 * @pre pass != NULL
 * @pre pass ist nicht leer
 *
 */
void vigenereDecode(Text plain, Text pass);

/**
 * Liest einen Text ein.
 *
 * @param[out] text eingelesener Text
 * @param[in]  str  Eingabestring
 *
 * @pre text != NULL
 * @pre str != NULL
 *
 * @return Fehlercode:
 *         ERR_TEXT_ILLEGAL_CHAR wenn der einzulesende Text ungueltige Zeichen enthaelt
 *         ERR_TEXT_TOO_LONG wenn der Text laenger ist als der verfuegbare Platz
 */
ErrorCode readText(Text text, char * str);


/**
 * Schreibt den uebergebenen Text auf den uebergebenen Ausgabestrom.
 *
 * @param[in] stream Ausgabestrom
 * @param[in] text   Text
 *
 * @pre stream != NULL
 * @pre text != NULL
 *
 */
void printText(FILE * stream, Text text);

/**
 * Gibt das Histogram des uebergebenen Texts auf dem uebergebenen Ausgabestrom aus.
 *
 * Die Ausgabe erfolgt spaltenweise in zwei Zeilen. Eine Spalte beinhaltet
 * stets das im Text vorhandene Zeichen (Auftrittshaeufigkeit > 0) und die
 * Anzahl seiner Vorkommen. Die Inhalte der Spalten sind voneinander durch
 * Leerzeichen getrennt und rechtsbuendig ausgerichtet. Die Breite der Anzahl
 * der Vorkommen bestimmt die Breite der Spalte. Die Zeichen werden gemaess
 * ihrer Reihenfolge im Zeichenvorrat ausgegeben.
 *
 * @param[in] stream Ausgabestrom
 * @param[in] text   Text
 *
 * @pre stream != NULL
 * @pre text != NULL
 *
 */
void printHistogram (FILE * stream, Text text);

#endif
