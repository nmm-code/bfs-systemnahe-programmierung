/**
 * Implementierung der Liste von Woertern und ihren Vorkommen
 *
 * @author mhe, mre, tti, Nima, Daniel
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "wordlist.h"
#include "error.h"

/** Referenzaehler fuer die gespeicherten Wortlistenelemente */
int wordlist_refs = 0;

WordList
wordlist_empty()
{
  return NULL;
}

int wordlist_isEmpty(WordList l)
{
  return l == wordlist_empty();
}

Word wordlist_head_word(WordList l)
{
  return l->word;
}

OccList
wordlist_head_occs(WordList l)
{
  return l->occs;
}

WordList
wordlist_tail(WordList l)
{
  return l->next;
}

WordList
wordlist_cons(WordList l, Word word, OccList occs)
{
  assert(word != NULL);
  assert(!occlist_isEmpty(occs));

  WordList res = malloc(sizeof(*res));
  wordlist_refs++;
  if (res == NULL)
  {
    error_print(stderr, ERR_OUT_OF_MEMORY);
    exit(ERR_OUT_OF_MEMORY);
  }

  res->word = word_copy(word);
  res->occs = occlist_cons(occlist_empty(), occs->elem);
  occs = occlist_delete(occs);
  res->next = l;
  return res;
}

WordList
wordlist_insert(WordList l, Word word, Occurrence occ)
{
  assert(word != NULL);
  OccList occs = occlist_cons(occlist_empty(), occ);

  // Leere Liste fuegt anfang
  if (wordlist_isEmpty(l))
    return wordlist_cons(wordlist_empty(), word, occs);

  // das einfuegende Wort ist kleiner
  if (0 < strcmp(l->word, word))
    return wordlist_cons(l, word, occs);

  // falls es ein Identisches Wort existiert wird die occliste ergaenzt
  WordList run = l;
  while (run != NULL)
  {
    if (0 == strcmp(run->word, word))
    {
      run->occs = occlist_insert(run->occs, occs->elem);
      occs = occlist_delete(occs);
      return l;
    }
    run = run->next;
  }
  // fuegt das neuer Wort ein mit Vorkommen
  run = l;
  while ((run->next != NULL) && (0 > strcmp(run->next->word, word)))
    run = run->next;

  run->next = wordlist_cons(run->next, word, occs);
  return l;
}

WordList
wordlist_delete(WordList l)
{
  // loescht das Wort und Vorkommen eines Knotens bis die liste leer ist
  while (l != NULL)
  {
    l->word = word_delete(l->word);
    l->occs = occlist_delete(l->occs);
    free(l);
    wordlist_refs--;
    l = l->next;
  }
  return wordlist_empty();
}
