#ifndef __WORD_H__
#define __WORD_H__

/**
 * Ein Wort
 *
 * Diese Datei darf nicht veraendert werden.
 *
 * @author mhe, mre, tti
 */

/** Referenzaehler fuer die gespeicherten Woerter */
extern int word_refs;

/**
 * Typdefinition fuer ein Wort
 */
typedef char * Word;

/**
 * Das leere Wort
 */
#define WORD_EMPTY "\0"

/**
 * Kopiert die uebergebene Zeichenkette in einen neu reservierten
 * Speicherbereich. Der Speicherbereich wird durch word_copy reserviert.
 *
 * @param[in] str die zu kopierende Zeichenkette
 *
 * @return Zeiger auf das neue Wort
 *
 * @pre str != NULL
 */
Word word_copy(char * str);

/**
 * Gibt den vom Wort belegten Speicherbereich wieder frei.
 * Das uebergebene Wort darf danach nicht mehr verwendet werden.
 *
 * @param[in/out] w Wort
 *
 * @return NULL
 */
Word word_delete(Word w);

#endif
