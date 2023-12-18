#ifndef __INDEXER_H__
#define __INDEXER_H__

/**
 * Modul zur Indizierung von beliebigen Dateien als Liste von Woerter mit ihren
 * Vorkommen
 *
 * Diese Datei darf nicht veraendert werden.
 *
 * @author mhe, mre, tti
 */

#include <stdio.h>

#include "error.h"
#include "wordlist.h"

/**
 * Ein Index
 */
typedef WordList Index;

/**
 * Der leerere Index
 */
#define INDEX_EMPTY wordlist_empty()

/**
 * Erzeugt zum Eingabestream stream einen Index. Initial ist dazu ein Zeiger auf
 * einen leeren Index zu uebergeben. Nach Ablauf der Funktion zeigt der Zeiger
 * index auf den fertig erzeugten Index zu stream.
 *
 * Im Stream werden Woerter nach folgenden Regeln erkannt: Ein Wort ist eine
 * mindestens einelementige Zeichenfolge, die lediglich aus Klein- und
 * Grossbuchstaben (ASCII), also 'a' bis 'z' und ' A' bis 'Z', besteht.
 * Zwei Woerter werden durch eine mindestens einelementige Folge von Trennzeichen
 * getrennt, wobei Trennzeichen alle Zeichen (bzw. Bytewerte) sind, die nicht
 * in Woertern vorkommen koennen. Folgen von Trennzeichen koennen auch am Anfang
 * oder Ende des streams auftreten (muessen aber nicht). Zeilenumbrueche sind
 * Trennzeichen, die zugleich die Angabe zur Zeile, in der ein Wort vorkommt,
 * steuern. Als Zeilenumbruch wird ausschliesslich der Unix-Zeilenumbruch '\\n'
 * gewertet.
 *
 * Er werden lediglich Woerter mit einer Mindestlaenge von min und einer
 * Maximallaenge max in den Index aufgenommen. Woerter, die kuerzer oder laenger
 * sind werden ohne Signalisierung eines Fehlers ueberlesen.
 *
 * @param[in/out] stream der Dateistream
 * @param[out]    index  Zeiger auf einen Index
 * @param         min    kuerzeste zu indizierende Wortlaenge
 * @param         min    laengste zu indizierende Wortlaenge
 *
 * @return ERR_NULL || ERR_READ_STREAM
 *
 * @pre stream != NULL
 * @pre index ist ein Zeiger auf einen leeren Index
 * @pre min >= 1
 * @pre max >= min
 */
ErrorCode index_make(FILE * stream, Index * index, unsigned long min,
    unsigned long max);

/**
 * Gibt den uebergebenen Index auf dem uebergebenen stream im CSV-Format aus.
 * Je Wort und Vorkommen des Wortes wird dazu eine Zeile erzeugt.
 *
 * Dabei besteht eine Zeile immer aus (ohne Leerzeichen):
 * Wort,Zeile,Position
 *
 * Die Sortierung der Woerter und Wortvorkommen entspricht hierbei der Sortierung
 * der entsprechenden Listen. D.h. z.B., dass die Zeilen zu den Vorkommen eines
 * Wortes in einem Block nacheinander ausgegeben werden (entsprechend der
 * Sortierung der Vorkommen).
 *
 * Als Zeilenumbruch wird der Unix-Zeilenumbruch '\\n' verwendet. Nach jeder Zeile
 * einschliesslich der letzten Zeile wird ein Zeilenumbruch ausgegeben. Daraus
 * folgt, dass im Falle des leeren Index nichts ausgegeben wird.
 *
 * @param[in] stream der Dateistream
 * @param[in] index  der Index
 *
 * @return ERR_NULL || ERR_WRITE_STREAM
 *
 * @pre stream != NULL
 */
ErrorCode index_printCSV(FILE * stream, Index index);

/**
 * Gibt den uebergebenen Index auf dem uebergebenen stream in einem fuer
 * Menschen gut lesbaren Format aus.
 *
 * @param[in] stream der Dateistream
 * @param[in] index  der Index
 *
 * @return ERR_NULL || ERR_WRITE_STREAM
 *
 * @pre stream != NULL
 */
ErrorCode index_printPretty(FILE * stream, Index index);

/**
 * Loescht den Index und gibt den durch ihn belegten Speicher wieder frei.
 * Der uebergebene Index darf danach nicht mehr verwendet werden.
 *
 * @param[in] index zu loeschender Index
 *
 * @return leerer Index
 */
Index index_delete(Index index);

#endif
