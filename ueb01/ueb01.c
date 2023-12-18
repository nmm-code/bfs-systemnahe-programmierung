/*
 * @file ueb01.c
 * Uebung Systemnahe Programmierung im WS 22/23.
 *
 * Ein einfaches Programm fuer Ganzzahlen, welches testen kann ob
 * eine Zahl prim oder froehlich ist und ausgehend von einer Zahl
 * deren Teiler finden kann.
 *
 * @author mhe, mre, tti, ias105448, ias105303
 *
 */

/*< Eingebundene Bibliotheken >*/
#include <stdio.h>

/*
 * Aufzaehlungs Datentype Error
 * 
 * Deklaration für ShowError  
 */
typedef enum {
    ERR_OK = 0,
    ERR_ARGUMENT,
    ERR_INVALID_FUNCTION,
    ERR_NEGATIV_NUMBER,
    ERR_NOT_NUMBER,
}
Error;

/*
 * Gibt die Hilfe auf dem uebergebenen Stream (stdout/stderr) aus.
 *
 * @param[in] stream Ausgabestrom
 */
void printUsage(FILE * stream) {
    fprintf(stream, "Usage:\n");
    fprintf(stream, "\n");
    fprintf(stream, "  ueb01 -h\n");
    fprintf(stream, "\n");
    fprintf(stream, "  shows this help and exits.\n");
    fprintf(stream, "\n");
    fprintf(stream, "  - or -\n");
    fprintf(stream, "\n");
    fprintf(stream, "  ueb01 NUM OP\n");
    fprintf(stream, "\n");
    fprintf(stream, "  checks whether a given number is prime or a happy number or finds the\n");
    fprintf(stream, "  divisors of a given number. A call always consists of a number followed\n");
    fprintf(stream, "  by an operation, where:\n");
    fprintf(stream, "\n");
    fprintf(stream, "  NUM has to be positive integer numbers (including 0).\n");
    fprintf(stream, "\n");
    fprintf(stream, "  OP is one of:\n");
    fprintf(stream, "    p checks whether NUM is prime or not\n");
    fprintf(stream, "    d looks for the dividers of NUM\n");
    fprintf(stream, "    h checks whether NUM is a happy number\n");
    fprintf(stream, "\n");
}

/*
 * Fehler Procedur
 * 
 * Gibt einen Fehlercode aus wenn err != 0 und die Hilfe 
 *
 * @param[in] err Fehlercode
 *
 * @return err Fehlercode
 */
Error ShowError(Error err) {
    fprintf(stderr, "Error: ");
        switch (err) {
            case ERR_ARGUMENT:
                fprintf(stderr, "Parameter");
                break;
            case ERR_INVALID_FUNCTION:
                fprintf(stderr, "Function not found");
                break;
            case ERR_NEGATIV_NUMBER:
                fprintf(stderr, "Number must be positiv");
                break;
            case ERR_NOT_NUMBER:
                fprintf(stderr, "Enter a \"Number\"");
                break;
            default:
                fprintf(stderr, "Unknown");
                break;
            }
        fprintf(stderr, "! \n");
    printUsage(stderr);
    return err;
}

/*
 * Primenzahl Funktion
 * 
 * Ueberprueft den Parameter Num ob es eine Primenzahl ist
 *
 * @param[in] num Ueberpruefende Zahl
 *
 * @return (True / False) == (1 / 0) :^)
 */
_Bool isPrime(int z) {
    int bool = 1;

    if (z != 2) {
        if ((z <= 1) || (z % 2 == 0))
            bool = 0;
        else {
            int i = 3;
            while ((i*i <= z) && bool) {
                if (z % i == 0)
                    bool = 0;
                i += 2;
            }
        }
    }
    return bool;
}

/*
 * Teiler Procedur
 * 
 * Gibt aus dem num Parameter alle vorhanden Teiler zurueck
 *
 * @param[in] num Ueberpruefende Zahl
 *
 */
void printDivisor(int num) {
    int i     = 1, 
        half  = num / 2;

    fprintf(stdout, "The number %d has the following divisors: ", num);

    while (i <= half) {
        if (num % i == 0)
            fprintf(stdout, "%d, ", i);
        i++;
    }
    fprintf(stdout, "%d", num);
}

/*
 * Fröhliche Zahl Funktion
 * 
 * Ueberprueft den Parameter Num ob es eine Fröhliche zahl ist
 *
 * @param[in] num Ueberpruefende Zahl
 *
 * @return (True / False) == (1 / 0) :^)
 */
_Bool isHappy(int num) {
    int i = num;
    int sum = 0;

    while ((i != 4) && (i > 1)) {
        while (i) {
           sum = sum + (i % 10) * (i % 10);
           i /= 10;
        }
        i = sum;
        sum = 0;
    }
   return i == 1;
}

/*
 * Hauptprogramm.
 *
 * Ueberprueft zunaechst die Eingaben auf gueltige Syntax und fuehrt
 * sofern kein Fehler aufgetreten ist die dem angegebenen Operator
 * entsprechende Berechnung aus:
 *
 * d findet die Teiler einer Zahl und gibt sie aus
 * h ueberprueft, ob die angegebene Zahl froehlich ist
 * p prueft, ob die angegebene Zahl prim ist
 *
 * Es wird entweder das Ergebnis der Berechnung ausgegeben oder eine
 * entsprechende Fehlermeldung gefolgt von der Hilfe.
 *
 * @param[in] argc Anzahl der Programmargumente.
 * @param[in] argv Array mit den Programmargumenten.
 *
 * @return Fehlercode.
 */
int main(int argc, char * argv[]) {
    Error err = ERR_OK;
    int   num =   0;
    char   c1 = '\0',
           c2 = '\0',
           c3 = '\0';

    if (argc == 2) {
        if ((2 == sscanf(argv[1], "%c%c%c", & c1, & c2, & c3)) && ((c1 == '-') && (c2 == 'h')))
            printUsage(stdout);
        else
            err = ERR_ARGUMENT;
    } else if (argc == 3) {     
        if (1 == sscanf(argv[1], "%i%c", &num, &c1)) {
            if (num < 0)
                err = ERR_NEGATIV_NUMBER;
            else if (1 == sscanf(argv[2], "%c%c", &c1, &c2)) {
                switch (c1) {
                    case 'p':
                        if (isPrime(num))
                            fprintf(stdout, "*\\o/* The number %d is a prime number. *\\o/*", num);
                        else
                            fprintf(stdout, "O_o The number %d is not a prime number. o_O", num);
                        break;

                    case 'd':
                        if (!num)
                            fprintf(stdout, "The number %d is not dividable.", num);
                        else 
                            printDivisor(num);
                        break;

                    case 'h':
                        if (isHappy(num))
                            fprintf(stdout, "*\\o/* The number %d is a happy number. *\\o/*", num);
                        else
                            fprintf(stdout, "O_o The number %d is a sad number. o_O", num);
                        break;

                    default:
                        err = ERR_INVALID_FUNCTION;
                        break;
                }
                if (!err)
                    fprintf(stdout, "\n");
            } else
                err = ERR_INVALID_FUNCTION;
        } else
            err = ERR_NOT_NUMBER;
    } else
        err = ERR_ARGUMENT;

    if (err)
        ShowError(err);
    return err; 
}