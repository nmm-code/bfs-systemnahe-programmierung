/**
 * @file ueb02.c
 *
 * Hauptprogramm.
 *
 * @author mhe, mre, tti, Nima, Daniel
 */

#include <stdio.h>
#include <assert.h>
#include "cipher.h"
#include "error.h"

/**
 * Gibt die Hilfe auf dem uebergebenen Stream (stdout/stderr) aus.
 *
 * @param[in] stream Ausgabestrom
 *
 * @pre stream != NULL
 */
void printUsage(FILE * stream) {
  assert(stream != NULL);

  fprintf(stream, "Usage:\n");
  fprintf(stream, "ueb02 -h\n\n");
  fprintf(stream, "  shows this help and exits.\n\n");
  fprintf(stream, "- or -\n\n");
  fprintf(stream, "ueb02 OPERATION [ARGUMENT] [OPERATION [ARGUMENT], ...]\n\n");
  fprintf(stream, "  Executes a number of (simple cryptographic) operations. The maximum text\n");
  fprintf(stream, "  size for plain / cipher text and key is %i. The allowed input characters\n", MAX_TEXT_LENGTH);
  fprintf(stream, "  range from \"%c\" to \"%c\".\n\n", SMALLEST_CHAR, BIGGEST_CHAR);
  fprintf(stream, "  OPERATION:\n");
  fprintf(stream, "    -t TEXT:  Sets the TEXT as new (plain/cipher) text.\n");
  fprintf(stream, "    -C ROT:   Sets the cipher algorithm to caesar.\n");
  fprintf(stream, "              ROT is the rotation (a positive integer).\n");
  fprintf(stream, "    -V KEY:   Sets the cipher algorithm to vigenere.\n");
  fprintf(stream, "              KEY is the nonempty passkey.\n");
  fprintf(stream, "    -e:       Encodes and replaces the current text using the current\n");
  fprintf(stream, "              cipher algorithm.\n");
  fprintf(stream, "    -d:       Decodes and replaces the current text using the current\n");
  fprintf(stream, "              cipher algorithm.\n");
  fprintf(stream, "    -i:       Writes the histogram corresponding to the current text to\n");
  fprintf(stream, "              stdout, followed by a line break.\n");
  fprintf(stream, "    -w:       Writes the current text to stdout, followed by a line break.\n");
}

/**
 * Gibt den jeweiligen Error Code aus und die Hilfe mit stderr
 *
 * @param[in] err Error-Code
 */
void errorHappend(ErrorCode err) {
  printError(stderr, err);
  printUsage(stderr);
}

/**
 * Liest eine Zahl ein und mit return zurueck
 *
 * @param[in] str Eingabe string
 * 
 * @return eingegebene Zahl
 */
int readNumber(char *str) {
  char dummy = '\0';
  int rot = 0;

  if (1 != sscanf(str,"%d%c",&rot,&dummy))
  // Wenn ein Fehler passiert bei der Eingabe
    rot = -1;
  // else rotation wird zurueckgegeben
  return rot;
}

/**
 * Hauptprogramm.
 *
 * Ueberprueft zunaechst die Eingaben auf gueltige Syntax und fuehrt
 * sofern kein Fehler aufgetreten ist die Operationen gemaess der
 * Usage aus.
 *
 * @param[in] argc Anzahl der Programmargumente.
 * @param[in] argv Array mit den Programmargumenten.
 *
 * @return Fehlercode.
 */
int main(int argc, char * argv[]) {

  // Variablen initialisierung
  enum {
    MODE_NONE = 0,
    MODE_VIGENERE,
    MODE_CAESAR
  }
  mode = MODE_NONE;

  ErrorCode error = ERR_NULL;

  Text temp = EMPTY_TEXT,
        key = EMPTY_TEXT;

  int rot = 0;

  char opt = '\0',
     dummy = '\0';

  // Schleifenzaehler counter
  for (int counter = 1; counter < argc && !error; counter++)
    if (1 == sscanf(argv[counter], "-%c%c", & opt, & dummy)) {
      switch (opt) {
      case 'h':
        printUsage(stdout);
        break;

      case 't':
        if (argc > counter + 1)
          error = readText(temp, argv[counter + 1]);
        else
          error = ERR_TEXT_MISSING_TEXT;
        counter++;
        break;

      case 'C':
        if (argc > counter + 1) {
          rot = readNumber(argv[counter+1]);
          if (rot >= 0)
            mode = MODE_CAESAR;
          else
            error = ERR_CAESAR_INVALID_ROTATION;
        } else
          error = ERR_CAESAR_MISSING_ROTATION;
        counter++;
        break;

      case 'V':
        if (argc > counter + 1) {
          switch (readText(key, argv[counter + 1])) {
            case ERR_TEXT_ILLEGAL_CHAR:
              error = ERR_VIGENERE_KEY_ILLEGAL_CHAR;
              break;
            case ERR_TEXT_TOO_LONG:
              error = ERR_VIGENERE_KEY_TOO_LONG;
              break;
            default:
              if (key[0] == '\0')
                error = ERR_VIGENERE_EMPTY_KEY;
              break;
          }
          mode = MODE_VIGENERE;
        } else
          error = ERR_VIGENERE_MISSING_KEY;
        counter++;
        break;

      case 'e':
        switch (mode) {
          case MODE_VIGENERE:
            vigenereEncode(temp, key);
            break;
          case MODE_CAESAR:
            caesarEncode(temp, rot);
            break;
          default:
            error = ERR_ENCODE_WITHOUT_CIPHER;
            break;
        }
        break;

      case 'd':
        switch (mode) {
          case MODE_VIGENERE:
            vigenereDecode(temp, key);
            break;
          case MODE_CAESAR:
            caesarDecode(temp, rot);
            break;
          default:
            error = ERR_DECODE_WITHOUT_CIPHER;
            break;
        }
        break;

      case 'w':
        printText(stdout, temp);
        break;

      case 'i':
        printHistogram(stdout, temp);
        break;

      default:
        error = ERR_UNKNOWN_OPERATION;
        break;
      }
    } else
      error = ERR_UNKNOWN_OPERATION;

  if (argc < 2)
    error = ERR_CALL_MISSING_ARGS;

  if (error)
    errorHappend(error);

  return error;
}