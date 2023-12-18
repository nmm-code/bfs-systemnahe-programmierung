/**
 * @file cipher.c
 *
 * Implementation des Moduls mit  Verschluesselungsfunktionen.
 *
 * @author mhe, mre, tti, Nima, Daniel
 *
 */

#include <stdio.h>
#include <assert.h>
#include "cipher.h"

void caesarEncode(Text plain, unsigned int rot) {
  assert(plain != NULL);

  rot %= (BIGGEST_CHAR - SMALLEST_CHAR) + 1;
  // Eine große Zahl zu eine kleine Zahl gemacht

 for (int idx = 0; plain[idx] != '\0'; idx++) 
  if ((BIGGEST_CHAR) < ( plain[idx] + rot))
    plain[idx] += rot + SMALLEST_CHAR - BIGGEST_CHAR - 1;
    // Ueberlauf 
  else
    plain[idx] += rot;
    // Text + Rotation
  
}

void caesarDecode(Text plain, unsigned int rot) {
  assert(plain != NULL);

  rot %= (BIGGEST_CHAR - SMALLEST_CHAR) + 1;
  // Eine große Zahl zu eine kleine Zahl gemacht

  rot = (BIGGEST_CHAR - SMALLEST_CHAR) - rot + 1;
  // Zahl invertiert

  caesarEncode(plain, rot);
}

void vigenereEncode(Text plain, Text pass) {
  assert(plain != NULL);
  assert(pass != NULL);
  assert(*pass);

  int passIdx = 0;

  for(int idx = 0; plain[idx] != 0; idx++,passIdx++) {
    // passIdx wird auf den Anfang gesetzt
    if (pass[passIdx] == '\0')
      passIdx = 0;

    if (BIGGEST_CHAR < ( plain[idx] + pass[passIdx] - SMALLEST_CHAR))
      plain[idx] = plain[idx] + pass[passIdx] - BIGGEST_CHAR - 1;
      // Ueberlauf
    else
      plain[idx] += pass[passIdx] - SMALLEST_CHAR;
      // Text + pass Zahl

  }
}

void vigenereDecode(Text plain, Text pass) {
  assert(plain != NULL);
  assert(pass != NULL);
  assert(*pass);

  int passIdx = 0;

 for (int idx = 0; plain[idx] != '\0';idx++,passIdx++) {
    // passIdx wird auf den Anfang gesetzt
    if (pass[passIdx] == '\0')
      passIdx = 0;

    if ((plain[idx] - (pass[passIdx] - SMALLEST_CHAR) < SMALLEST_CHAR))
      plain[idx] = plain[idx] - pass[passIdx] + BIGGEST_CHAR + 1; 
      // Ueberlauf
    else
      plain[idx] -= pass[passIdx] - SMALLEST_CHAR;
      // Text - pass Zahl  

  }
}

ErrorCode readText(Text text, char * str) {
  assert(text != NULL);
  assert(str != NULL);

  ErrorCode error = ERR_NULL;

  if (text[0] != 0)
    for (int idx = 0; text[idx]; idx++)
      text[idx] = 0;
    // Text wird geleert

  for (int idx = 0;str[idx] != '\0' && !error; idx++) 
    if (( str[idx] < SMALLEST_CHAR) || ( str[idx] > BIGGEST_CHAR))
      error = ERR_TEXT_ILLEGAL_CHAR;
    // Illegaler Char wurde eingelesen
    else if (idx < MAX_TEXT_LENGTH)
      text[idx] = str[idx];
    else
      error = ERR_TEXT_TOO_LONG;
    // Text ist zu lang

  return error;
}

void printText(FILE * stream, Text text) {
  assert(stream != NULL);
  assert(text != NULL);

  fprintf(stream,"%s\n",text);
}

void printHistogram(FILE * stream, Text text) {
  assert(stream != NULL);
  assert(text != NULL);

  short arr[BIGGEST_CHAR - SMALLEST_CHAR + 1] = {0};
  // Ein Array um die Vorkommen zu zaehlen
  int countC = 0,
         idx = 0;

  // geht den String durch und zaehlt die Chars
  for (int idx = 0;text[idx]; idx++) 
    arr[text[idx]-SMALLEST_CHAR]++;

  // fuegt gegebenenfalls ein Leerzeichen hinzu wenn das Vorkommen groesser als einstellig ist 
  for (idx = 0; idx < (BIGGEST_CHAR - SMALLEST_CHAR) + 1; idx++)
    if (arr[idx]) {
      countC = arr[idx];
      countC /= 10;
      while (countC) {
        countC /= 10;
        fprintf(stream, " ");
      }
      fprintf(stdout, "%c ", idx+SMALLEST_CHAR);
      // Gibt den jeweiligen char aus
    }

  fprintf(stream, "\n");

  for (idx = 0; idx < (BIGGEST_CHAR - SMALLEST_CHAR) + 1; idx++) 
    if (arr[idx]) 
      fprintf(stream, "%d ", arr[idx]);
      // Gibt den Vorkommen aus

  fprintf(stream, "\n");
}