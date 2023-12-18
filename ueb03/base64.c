/**
 * @file base64.c
 *
 * Implementierung des Base64-Moduls
 *
 * @author aan, avh, mhe, mre, tti, Nima, Daniel
 */

#include <assert.h>

#include "base64.h"

/** Base64-Zeichensatz */
unsigned char base64[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                          'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                          'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                          'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                          'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                          'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                          'w', 'x', 'y', 'z', '0', '1', '2', '3',
                          '4', '5', '6', '7', '8', '9', '+', '/'};

ErrorSet base64_encodeFile(char *source, char *dest) {
  assert(source != NULL); 
  assert(dest != NULL);

  ErrorSet error = ERR_NULL;

  FILE *fileSource = NULL,
       *fileDest   = NULL;

  // Oeffnen der Dateien
  if ((fileSource  = fopen(source,"rb")) == NULL)
    error =  ERR_SOURCE_FILE;        // Konnte nicht geoeffnet werden
  else if ((fileDest = fopen(dest,"wb")) == NULL)
    error = ERR_DESTINATION_FILE;    // Konnte nicht geoeffnet werden
  else {
   error = base64_encodeStream(fileSource,fileDest);
   
  // Schliessen der Dateien
    if (0 != fclose(fileSource))
      error |= ERR_SOURCE_FILE;      // Konnte nicht geschlossen werden
    else if (0 != fclose(fileDest))
      error |= ERR_DESTINATION_FILE; // Konnte nicht geschlossen werden
  }
  
  // Wenn ein Fehler passierte ,ist das ein Encode Fehler
  if (error)
    error |= ERR_B64_ENCODE;
  return error;
}

ErrorSet base64_decodeFile(char *source, char *dest) {
  assert(source != NULL); 
  assert(dest != NULL);

  ErrorSet error = ERR_NULL;

  FILE *fileSource = NULL,
       *fileDest   = NULL;

  // Oeffnen der Dateien
  if ((fileSource  = fopen(source,"rb")) == NULL)
    error = ERR_SOURCE_FILE;          // Konnte nicht geoeffnet werden
  else if ((fileDest = fopen(dest,"wb")) == NULL)
    error = ERR_DESTINATION_FILE;     // Konnte nicht geoeffnet werden
  else {
    error = base64_decodeStream(fileSource,fileDest);

    // Schliessen der Dateien
    if (0 != fclose(fileSource))
      error |=  ERR_SOURCE_FILE;      // Konnte nicht geschlossen werden
    else if (0 != fclose(fileDest))
      error |=  ERR_DESTINATION_FILE; // Konnte nicht geschlossen werden
  }

  // Wenn ein Fehler passierte ,ist das ein Decode Fehler
  if (error)
    error |= ERR_B64_DECODE;
  return error;
}

ErrorSet base64_encodeStream(FILE *source, FILE *dest) {
  assert(source != NULL); 
  assert(dest   != NULL);

  ErrorSet         error = ERR_NULL;

  int                CH = '\0',   
                    tempBytes = 0;

  unsigned char   tempC = '\0',
                  resultC = '\0',
                overFlow = '\0';

  // Laufvariable tempBytes die den aktuellen Byte umwandelt
  tempBytes = 1;
  while ((CH = fgetc(source)) != EOF && !error) {
    tempC = CH;
    switch (tempBytes) {
      case 1:
        resultC = base64[tempC >> 2];                     
        // 1111 1100 >> 2 = 0011 1111
        // Erste 6 bit umgewandelt
        overFlow = (tempC & 3) << 4;                      
        // 0000 0011 << 4 = 0011 0000
        // Fuer den naechsten Byte
      break;

      case 2:
        resultC = base64[overFlow | (tempC & 240) >> 4];  
        // overflow mit den linken Halbbyte OR verkuepft
        // 0011 0000 | 0000 1111
        overFlow = (tempC & 15) << 2;       
        // rechte Halbbyte links verschoben            
        // 0000 1111 << 2 = 0011 1100
      break;

      case 3:            
        resultC = base64[overFlow | (tempC & 192) >> 6];  
        // overflow mit den 2 hoechsten wertigsten OR verkuepft
        // 1100 0000 >> 6 = 0000 0011 | 0011 1100
        overFlow = tempC & 63;   
        // letzt Halbbyte                         
        //  63  == 0011 1111
      break;
    }
    // base64 chars werden geschrieben
    if (0 > fprintf(dest,"%c",resultC)) 
      error = ERR_DESTINATION_FILE; 
    // Fehler beim schreiben
    else if (tempBytes == 3) { 
    // Beim letzten Byte 
      if (0 > fprintf(dest,"%c",base64[overFlow]))  
      // wird overflow ausgegeben
        error = ERR_DESTINATION_FILE;  
        // Fehler beim schreiben
      tempBytes = 0;
    }
    tempBytes++;
  }
  // Wenn kein Error passierte
  if (!error && tempBytes != 1) {
    // Wird der Rest ausgegeben ,falls vorhanden
    if (overFlow)
      if (0 >  fprintf(dest,"%c",base64[overFlow]))
        error = ERR_DESTINATION_FILE;
         // Fehler beim schreiben

    // die Padding Bytes werden reingeschrieben
    for (tempBytes = 4 - tempBytes;tempBytes > 0 && !error;  tempBytes--)
      if (0 > fprintf(dest,"="))
        error = ERR_DESTINATION_FILE;   
         // Fehler beim schreiben    
  }    
  return error;
}

/**
 * Ueberprueft ob der uebergebene char im base64 Zeichensatz vorhanden ist
 * 
 * @param ch uebergebener char
 * 
 * @return base64 array[idx] oder -1 wenn nicht gefunden
 * 
 */
int base64_findIdx(char ch) {
// Findet den Index vom Base64 array
for (unsigned char idx = 0; idx < sizeof(base64); idx++)  {
 if (base64[idx] == ch) // bei Gleichheit 
  return idx;
}
  return -1; // -1 ,wenn es nicht gefunden wurde
}

ErrorSet base64_decodeStream(FILE *source, FILE *dest) {
  assert(source != NULL); 
  assert(dest != NULL);

  ErrorSet error = ERR_NULL;

  unsigned char tempC = '\0',
                resultC = '\0',
                overFlow = '\0';

                int CH    = '\0',
                    count = 0;

  // Nach dem '=' darf kein anderes Symbol folgen
  _Bool padding = 0;

  // Lauf Variable tempBytes  
  int  bit6 = 1;

  while ((CH = fgetc(source)) !=  EOF && !error) {
    if (CH != '=') {
      // Uebepruefung ob der TempC im base64 array ist
      if (-1 == (CH = base64_findIdx(CH)) || padding)     
        error |= ERR_INVALID_B64_DATA;
      else {
        tempC = CH;
        switch (bit6) {
          case 1:
            // Einlesen des erste 6 Bits
            // 0011 1111 << 2 = 1111 1100
            overFlow = tempC << 2;
          break;

          case 2:
            // resultC definieren ,weil es jetzt ein vollständiger Byte ist
            // 1111 1100 | 0000 0011 
            resultC = overFlow | (tempC >> 4);
            overFlow = tempC << 4;
          break;

          case 3:
            // resultC definieren ,weil es jetzt ein vollständiger Byte ist       
            // 1111 0000 | 0000 1111
            resultC = overFlow | (tempC >> 2);
            overFlow = tempC << 6;
          break;

          case 4:
            // resultC definieren ,weil es jetzt ein vollständiger Byte ist       
            // 1100 0000 | 0011 1111
            resultC = overFlow | tempC;
            bit6 = 0;
          break;
        }
        // In die Datei schreiben ,wenn ein vollstaendiges byte entstanden ist
        if (bit6 != 1)
          if (0 > fprintf(dest,"%c",resultC))
            error |= ERR_DESTINATION_FILE;  // Fehler beim schreiben
      bit6++; // 6er Bits weiter gehen
      }
    } else
      padding = 1;  // wenn ein '=' kommt kein anders Zeichen danach

    count++;
  } 
  
  if (count % 4 != 0) 
  // die base64 Dateien muessen ein Vielfaches von 4 beinhalten, um eine gueltige Datei zu sein
    error |= ERR_INVALID_B64_DATA;
  return error;
}
