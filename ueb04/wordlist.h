#ifndef __WORDLIST_H__
#define __WORDLIST_H__

/**
 * Liste von Woertern und ihren Vorkommen
 *
 * @author mhe, mre, tti, Nima, Daniel
 */

#include "occlist.h"
#include "word.h"

/** Referenzaehler fuer die gespeicherten Wortlistenelemente */
extern int wordlist_refs;

typedef struct WordListNode *WordList;
struct WordListNode {
 Word word;
 OccList occs;
 WordList next;
};

/**
 * Erzeugt eine leere Liste.
 * Da eine Liste nur ein Zeiger auf ein Element ist, ist die leere Liste der
 * Nullzeiger.
 *
 * @return Leere Liste
 */
WordList wordlist_empty();

/**
 * Prueft ob die Liste leer ist.
 *
 * @param[in] l Zu pruefende Liste
 *
 * @return True, wenn die Liste leer ist, sonst false
 */
int wordlist_isEmpty(WordList l);

/**
 * Liefert das Wort am Kopf der Liste.
 *
 * @param[in] l Liste
 *
 * @return Wort des ersten Elements
 *
 * @pre Die Liste darf nicht leer sein.
 */
Word wordlist_head_word(WordList l);

/**
 * Liefert die Vorkommensliste am Kopf der uebergebenen Liste.
 *
 * @param[in] l Liste
 *
 * @return Liste von Vorkommen
 *
 * @pre Die Liste darf nicht leer sein.
 */
OccList wordlist_head_occs(WordList l);

/**
 * Liefert die Liste ohne das Kopf-Element.
 *
 * @param[in] l Liste
 *
 * @return Der Rest
 *
 * @pre Die Liste darf nicht leer sein.
 */
WordList wordlist_tail(WordList l);

/**
 * Fuegt das Element (Wort & Vorkommen) vorne an der Liste an und gibt einen
 * Zeiger auf den neuen Listenanfang zurueck.
 *
 * Das Wort bzw. die Vorkommensliste werden nicht kopiert. Fuer die spaetere
 * Speicherfreigabe des Wortes und der Vorkommensliste ist die Wortliste
 * verantwortlich.
 *
 * @param[in] l    Wortliste
 * @param[in] word das Wort
 * @param[in] occs Die Liste mit den Vorkommen des Wortes
 *
 * @return veraenderte Liste
 *
 * @pre word != NULL
 * @pre occs ist nicht leer
 */
WordList wordlist_cons(WordList l, Word word, OccList occs);

/**
 * Fuegt das Vorkommen eines Wortes in die Liste ein. Falls das Wort noch nicht
 * vorhanden ist, wird das Wort aufsteigend sortiert, entsprechend des
 * Ergebnisses von strcmp, mit seinem Vorkommen in die Liste eingefuegt. Sofern
 * das Wort schon enthalten ist, wird das Vorkommen entsprechend der Sortierung
 * von occlist_insert in die Vorkommensliste des bereits vorhandenen Wortes
 * eingefuegt.
 *
 * Die Funktion gibt den Zeiger auf die veraenderte Liste zurueck.
 *
 * Das Wort wird nicht kopiert.
 * Fuer die spaetere Speicherfreigabe des Wortes ist die Wortliste
 * verantwortlich.
 *
 * @param[in] l   Liste
 * @param[in] w   das Wort
 * @param[in] occ Vorkommen des Wortes
 *
 * @return veraenderte Liste
 *
 * @pre word != NULL
 */
WordList wordlist_insert(WordList l, Word word, Occurrence occ);

/**
 * Loescht die gesamte Liste und gibt ihren belegten Speicher wieder frei.
 * Die uebergebene Liste darf danach nicht mehr verwendet werden.
 *
 * @param[in/out] l Liste
 *
 * @return leere Liste
 */
WordList wordlist_delete(WordList l);


#endif
