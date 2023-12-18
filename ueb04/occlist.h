#ifndef __OCCLIST_H__
#define __OCCLIST_H__

/**
 * Liste von Wort-Vorkommen
 *
 * Ein Vorkommen ist ein Tupel aus Zeilennummer und Nummer des Wortes innerhalb
 * der Zeile (beide Zaehlungen beginnen bei 0).
 *
 * @author mhe, mre, tti, Nima, Daniel
 */

/** Getter-Makros fuer Occurrence-Komponenten */
#define LINE(OCC) ((OCC).line)
#define POS(OCC)  ((OCC).pos)

/** Referenzaehler fuer die gespeicherten OccList-Knoten */
extern int occlist_refs;

/**
 * Typdefinition fuer Vorkommen
 */
typedef struct Occurrence {
   unsigned long line;
   unsigned int pos;
} Occurrence;


typedef struct OccListNode *OccList;
struct OccListNode {
  Occurrence elem;
  OccList next;
};


/**
 * Erzeugt eine leere Liste.
 * Da eine Liste nur ein Zeiger auf ein Element ist, ist die leere Liste der
 * Nullzeiger.
 *
 * @return Leere Liste
 */
OccList occlist_empty();

/**
 * Prueft ob die Liste leer ist.
 *
 * @param[in] l Zu pruefende Liste
 *
 * @return True, wenn die Liste leer ist, sonst false
 */
int occlist_isEmpty(OccList l);

/**
 * Liefert das Kopf-Element der Liste.
 *
 * @param[in] l Liste
 *
 * @return Das erste Element
 *
 * @pre Die Liste darf nicht leer sein.
 */
Occurrence occlist_head(OccList l);

/**
 * Liefert die Liste ohne das Kopf-Element.
 *
 * @param[in] l Liste
 *
 * @return Der Rest
 *
 * @pre Die Liste darf nicht leer sein.
 */
OccList occlist_tail(OccList l);

/**
 * Fuegt das Element vorne an der Liste an und gibt einen Zeiger auf den neuen
 * Listenanfang zurueck.
 *
 * @param[in] l   Liste
 * @param     occ Element
 *
 * @return Veraenderte Liste
 */
OccList occlist_cons(OccList l, Occurrence occ);

/**
 * Fuegt das Element sortiert in die Liste ein.
 * Dabei wird zunaechst aufsteigend nach line und, falls line identisch ist,
 * aufsteigend nach pos sortiert. Wenn die Occurence schon in der Liste
 * vorhanden ist, wird sie nicht erneut eingefuegt.
 *
 * @param[in] l   Liste
 * @param     occ Element
 *
 * @return Veraenderte Liste
 */
OccList occlist_insert(OccList l, Occurrence occ);

/**
 * Loescht die gesamte Liste und gibt ihren belegten Speicher wieder frei.
 * Die uebergebene Liste darf danach nicht mehr verwendet werden.
 *
 * @param[in] l Liste
 *
 * @return leere Liste
 */
OccList occlist_delete(OccList l);


#endif
