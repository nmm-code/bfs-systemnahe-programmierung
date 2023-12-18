/**
 * Implementierung der Wort-Funktionen
 *
 * @author mhe, mre, tti, Nima, Daniel
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "word.h"
#include "error.h"

/** Referenzaehler fuer die gespeicherten Woerter */
int word_refs = 0;

Word word_copy(char *str)
{
  // Neuer Speicher wird reserviert
  Word res = malloc(strlen(str) + 1);
  word_refs++;

  if (res == NULL)
  {
    error_print(stderr, ERR_OUT_OF_MEMORY);
    exit(ERR_OUT_OF_MEMORY);
  }
  // String wird in res kopiert
  strcpy(res, str);
  return res;
}

Word word_delete(Word w)
{
  word_refs--;
  free(w);
  return NULL;
}
