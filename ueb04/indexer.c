/**
 *Implementierung der Indizierung von beliebigen Dateien
 *
 *@author mhe, mre, tti, Nima, Daniel
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "indexer.h"

/**
 *Ueberpruefung ob der char c ein Buchstabe ist
 *
 *@param[in] c Ueberpruefender char
 *@return TRUE || FALSE
 */
_Bool isLetter(char c)
{
  return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

/**
 *Liest aus dem uebergebenen Stream und ueberliest dabei alle Zeichen ausser
 *denen, die zu einem Wort gehoeren, also alle Klein- und Grossbuchstaben. Wird
 *hierbei ein zu einem Wort gehoeriges Zeichen z gefunden, so wird das Ueberlesen
 *beendet und das zuletzt gefundene Zeichen z wieder zurueck in den Stream
 *geschrieben. Zeilenumbrueche werden zwar auch ueberlesen, aber gleichzeitig
 *wird die Anzahl der ueberlesenen Zeilenumbrueche ueber newlines kommuniziert.
 *
 *Die Funktion darf nicht mit einem Stream aufgerufen werden, der bereits das
 *Dateiende ueberschritten hat.
 *
 *@param[in/out] stream   Zeiger auf den Eingabestream
 *@param[out]    newlines Anzahl der ueberlesenen Zeilenumbrueche
 *
 *@return ERR_NULL || ERR_READ_STREAM
 *
 *@pre stream != NULL
 *@pre !feof(stream)
 *@pre newlines != NULL
 */
static ErrorCode
skip(FILE *stream, unsigned int *newlines)
{
  assert(stream != NULL);
  assert(!feof(stream));
  assert(newlines != NULL);
  ErrorCode error = ERR_NULL;
  int ch = '\0';

  while ((ch = fgetc(stream)) != EOF && !error && !isLetter(ch))
  {
    if (ferror(stream))
      error = ERR_READ_STREAM;
    if (ch == '\n')
      (*newlines)++;
  }

  // Buchstabe wird zurueck geschrieben
  if (isLetter(ch))
     if (ungetc(ch, stream) != ch)
      error = ERR_READ_STREAM;

  return error;
}

/**
 *Liest aus dem uebergebenen Stream ein einzelnes Wort bestehend aus Klein- und
 *Grossbuchstaben in einen Puffer ein. Der Puffer nebst seiner Groesse bei Aufruf
 *von readWord wird vom Aufrufer per Parameter buffer und bufsize uebergeben.
 *Der Puffer darf die Groesse 0 haben, in diesem Fall muss *buffer dem NULL-Zeiger
 *entsprechen. Sofern der Puffer nicht ausreichend gross fuer das einzulesende
 *Wort ist, wird er von readWord geeignet vergroessert. Die neue Groesse des
 *Puffers (die groesser als fuer das Wort erforderlich ausfallen darf) und der
 *moeglicherweise neue Anfangszeiger des Puffers wird dem Aufrufer ueber die
 *Parameter buffer und bufsize zurueckgemeldet. Die Laenge des gelesenen Wortes
 *wird ueber den Parameter wordsize zurueckgemeldet.
 *
 *Die Funktion readWord erzeugt im Puffer ein leeres Wort, wenn sie im Stream
 *unmittelbar auf ein Trennzeichen trifft.
 *
 *Die Funktion darf nicht mit einem Stream aufgerufen werden, der bereits das
 *Dateiende ueberschritten hat.
 *
 *Wird beim Einlesen ein Trennzeichen t gefunden, so wird das Einlesen beendet
 *und das zuletzt gefundene Zeichen t wieder zurueck in den Stream geschrieben.
 *
 *@param[in/out] stream   Zeiger auf den Eingabestream
 *@param[in/out] buffer   Zeiger auf einen Pufferanfangszeiger
 *@param[in/out] bufsize  Zeiger auf die Groesse des Puffers buffer
 *@param[out]    wordsize Zeiger auf die Laenge des eingelesen Wortes
 *
 *@return ERR_NULL || ERR_READ_STREAM
 *
 *@pre stream != NULL
 *@pre !feof(stream)
 *@pre buffer != NULL
 *@pre bufsize != NULL
 *@pre (*buffer != NULL) == (*bufsize > 0)
 *@pre wordsize != NULL
 */
static ErrorCode
readWord(FILE *stream, char **buffer, unsigned int *bufsize, unsigned int *wordsize)
{
  assert(stream != NULL);
  assert(!feof(stream));
  assert(buffer != NULL);
  assert(bufsize != NULL);
  assert((*buffer != NULL) == (*bufsize > 0));
  assert(wordsize != NULL);

  ErrorCode error = ERR_NULL;
  int ch = 0;
  unsigned int idx = 0;

  while ((ch = fgetc(stream)) != EOF && !error && isLetter(ch))
  {
    if (ferror(stream))
      error = ERR_READ_STREAM;

    if (idx > *bufsize)
    {
      *bufsize *= 2;
      *buffer = realloc(*buffer, (*bufsize) *sizeof(char));
      if (*buffer == NULL)
      {
        error_print(stderr, ERR_OUT_OF_MEMORY);
        exit(ERR_OUT_OF_MEMORY);
      }
    }

    (*buffer)[idx++] = ch;
  }

  // Nicht Buchstabe wird zurueck geschrieben
  if (!isLetter(ch))
    if (ungetc(ch, stream) != ch)
      error = ERR_READ_STREAM;

  (*buffer)[idx] = '\0';
  *bufsize = idx + 1;
  *wordsize = idx;

  // größe verkleinern 
  *buffer = realloc(*buffer, (*bufsize) *sizeof(char));
  word_refs++;
  if (*buffer == NULL)
  {
    error_print(stderr, ERR_OUT_OF_MEMORY);
    exit(ERR_OUT_OF_MEMORY);
  }

  return error;
}

ErrorCode
index_make(FILE *stream, Index *index, unsigned long min, unsigned long max)
{
  assert(stream != NULL);
  assert(wordlist_isEmpty(*index));
  assert(min >= 1);
  assert(max >= min);

  ErrorCode error = ERR_NULL;

  Word buffer = NULL;

  unsigned int bufsize = 0,
               wordsize = 0;

  unsigned int pos = 0,
               line = 0;

  Occurrence occ = {0};

  // Falls ein Trennzeichen am anfang steht wird diese übersprungen
  if (!feof(stream))
    error = skip(stream, &line);

  while (!feof(stream))
  {
    pos++;

    buffer = malloc(sizeof(char) * (min + 1));
    if (buffer == NULL)
    {
      error_print(stderr, ERR_OUT_OF_MEMORY);
      exit(ERR_OUT_OF_MEMORY);
    }

    bufsize = (min + 1);
    wordsize = 0;
    error = readWord(stream, &buffer, &bufsize, &wordsize);

    if (wordsize >= min && wordsize <= max)
    {
      occ.line = line;
      occ.pos = pos - 1;
      (*index) = wordlist_insert(*index, buffer, occ);
    }
    else
      pos--; // Wenn ein Wort zu gross oder zu klein ist

    buffer = word_delete(buffer);

    // Trennzeichen skippen
    if (!feof(stream))
    {
      unsigned int before = line;
      error = skip(stream, &line);
      // falls line hochgezaehlt wurde wird pos = 0
      if (before < line)
        pos = 0;
    }
  }

  return error;
}

ErrorCode
index_printCSV(FILE *stream, Index index)
{
  assert(stream != NULL);
  ErrorCode error = ERR_NULL;
  Index run = index;

  while (run != NULL)
  {
    OccList o = run->occs;
    while (o != NULL)
    {
      // Ausgabe von String,line,pos
      if (0 > fprintf(stream, "%s,", run->word) || 0 > fprintf(stream, "%ld,", o->elem.line) || 0 > fprintf(stream, "%d\n", o->elem.pos))
        error = ERR_WRITE_STREAM;
      o = o->next;
    }

    run = run->next;
  }

  return error;
}

ErrorCode
index_printPretty(FILE *stream, Index index)
{
  assert(stream != NULL);
  ErrorCode error = ERR_NULL;
  Index run = index;

  while (run != NULL)
  {
    OccList o = run->occs;
    // Ausgabe von String
    if (0 > fprintf(stream, "%s:\n", run->word))
      error = ERR_WRITE_STREAM;

    for (int i = 0; o != NULL; i++, o = o->next)
    {
      // Ausgabe von Line und Pos
      if (0 > fprintf(stream, "(%ld,", o->elem.line) || 0 > fprintf(stream, "%d),\n", o->elem.pos))
        error = ERR_WRITE_STREAM;
      // Einruecken
      for (int j = 0; j < i * 3; j++)
        fprintf(stream, " ");
    }

    // Fuer das naeste Wort Zeilenumbruch
    if (0 > fprintf(stream, "\n"))
      error = ERR_WRITE_STREAM;
    run = run->next;
  }

  return error;
}

Index index_delete(Index index)
{
  return wordlist_delete(index);
}