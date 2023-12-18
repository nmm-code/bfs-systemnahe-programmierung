/**
 * Hauptprogramm
 *
 * Diese Datei darf nicht veraendert werden.
 *
 * @author mhe, mre, tti
 */

#include <stdio.h>
#include <limits.h>
#include <assert.h>

#include "error.h"
#include "indexer.h"


/**
 * Gibt die Hilfe auf dem uebergebenen Stream aus.
 *
 * @param[in] stream Dateistream
 *
 * @pre stream != NULL
 */
static void
printUsage(FILE * stream)
{
  assert (stream != NULL);

  fprintf(stream, "Usage:\n");
  fprintf(stream, "    ueb04 [PARAM...]\n");
  fprintf(stream, "\n");
  fprintf(stream, "    where PARAM is any of the following:\n");
  fprintf(stream, "        -h      prints this information to stdout\n");
  fprintf(stream, "        -w LONG Sets the minimum word length (LONG must be 1 or larger),\n");
  fprintf(stream, "                default is 1\n");
  fprintf(stream, "        -W LONG Sets the maximum word length (LONG must be 1 or larger)\n");
  fprintf(stream, "                default is ULONG_MAX\n");
  fprintf(stream, "        -H      prints a human readable format instead of CSV\n");
  fprintf(stream, "        -m      activates memory management\n");
  fprintf(stream, "\n");
  fprintf(stream, "    Reads a stream from stdin and generates an index of found words.\n");
  fprintf(stream, "    The output is written to stdout - either as CSV or in human readable format.\n");
}

/**
 * Liest einen einzelnen Wert aus argv an der Stelle index als unsigned long
 * Wert in value ein.
 *
 * @param[in]  argv  Programmargumente
 * @param      index Position
 * @param[out] value gelesener Wert, kann im Fehlerfall ungueltig sein
 *
 * @return true wenn alles ok ist, im Fehlerfall false
 *
 * @pre index >= 0
 * @pre value != NULL
 */
static int
readBoundary(char * argv[], int index, unsigned long * value) {
  assert (index >= 0);
  assert (value != NULL);

  char
      check = '\0'
    ;

  return sscanf(argv[index], "%lu%c", value, &check) == 1;
}

/**
 * Hauptprogramm
 *
 * Liest von stdin einen Text ein und schreibt abhaengig von den Aufrufparameter
 * nach stdtout.
 *
 * @param argc Anzahl der Programmargumente
 * @param argv Array mit den Programmargumenten
 *
 * @return Fehlercode
 */
int
main(int argc, char * argv[]) {
  ErrorCode
      error = ERR_NULL
    ;

  int
      i                 = 1
    , help_wanted       = 0
    , human_readable    = 0
    , memory_management = 0
    ;

  unsigned long
      min_wordLength    = 1
    , max_wordLength    = ULONG_MAX
    ;

  char
      opChar = '\0'
    , check  = '\0'
    ;

  Index
      index  = INDEX_EMPTY;
    ;

  while (i < argc && !error) {
    if (sscanf(argv[i], "-%c%c", &opChar, &check) == 1) {
      switch (opChar) {
        case 'w':
          if (!((i < argc - 1) && readBoundary(argv, ++i, &min_wordLength))) {
            error = ERR_WRONG_ARG;
          }
          break;
        case 'W':
          if (!((i < argc - 1) && readBoundary(argv, ++i, &max_wordLength))) {
            error = ERR_WRONG_ARG;
          }
          break;
        case 'h':
          help_wanted = 1;
          break;
        case 'H':
          human_readable = 1;
          break;
        case 'm':
          memory_management = 1;
          break;
        default:
          error = ERR_WRONG_ARG;
          break;
      }
    } else {
      error = ERR_WRONG_ARG;
    }
    ++i;
  }

  if (!error) {
    if (!((1 <= min_wordLength) && (min_wordLength <= max_wordLength))) {
      error = ERR_WRONG_ARG;
    }
  }

  if (!error) {
    error = index_make(stdin, &index, min_wordLength, max_wordLength);

    if (human_readable) {
      error = index_printPretty(stdout, index);
    } else {
      error = index_printCSV(stdout, index);
    }

    index = index_delete(index);
  }

  if (memory_management) {
    if (word_refs != 0 || occlist_refs != 0 || wordlist_refs != 0) {
      error = ERR_MEMORY_LEAK;
    }

    fprintf(stderr, "WordRefs: %d\n", word_refs);
    fprintf(stderr, "OccListRefs: %d\n", occlist_refs);
    fprintf(stderr, "WordListRefs: %d\n", wordlist_refs);
  }

  if (!error && help_wanted) {
    printUsage(stdout);
  }

  if (error) {
    error_print(stderr, error) ;
    printUsage(stderr);
  }

  return error;
}
