/**
 * Implementierung der Liste von Wort-Vorkommen
 *
 * @author mhe, mre, tti, Nima, Daniel
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "occlist.h"
#include "error.h"

/** Referenzaehler fuer die gespeicherten OccList-Knoten */
int occlist_refs = 0;

OccList
occlist_empty()
{
  return NULL;
}

int occlist_isEmpty(OccList l)
{
  return l == occlist_empty();
}

Occurrence
occlist_head(OccList l)
{
  assert(!occlist_empty(l));
  return l->elem;
}

OccList
occlist_tail(OccList l)
{
  assert(!occlist_empty(l));
  return l->next;
}

OccList
occlist_cons(OccList l, Occurrence occ)
{
  OccList res = malloc(sizeof(*res));
  occlist_refs++;
  if (res == NULL)
  {
    error_print(stderr, ERR_OUT_OF_MEMORY);
    exit(ERR_OUT_OF_MEMORY);
  }
  res->elem = occ;
  res->next = l;
  return res;
}

OccList
occlist_insert(OccList l, Occurrence occ)
{

  if (occlist_isEmpty(l))
    return occlist_cons(l, occ);
    
  // Vor das aktuelle einfuegen
  if (l->elem.line > occ.line) 
    return occlist_cons(l, occ);
  else
  {
    OccList run = l;
    // mitte oder hinter einfuegen
    while (!occlist_isEmpty(run->next) && run->elem.line < occ.line && run->next->elem.line <= occ.line)
    {
      run = run->next;
    }
    // Identischer line wird nach pos geschaut und eingefuegt
    while (!occlist_isEmpty(run->next) && run->next->elem.line == occ.line && run->elem.pos < occ.pos)
      run = run->next;
    // fuegt hinzu
    // doppelte dürfen nicht dabei
    if (occ.line != run->elem.line || occ.pos != run->elem.pos )
    run->next = occlist_cons(run->next, occ);
  }
  return l;
}

OccList
occlist_delete(OccList l) {
  OccList res = l;

  while (!occlist_isEmpty(l)) {
    res = occlist_tail(l);
    free(l);
    l = res;
    occlist_refs--;
  }
  return occlist_empty();
}
