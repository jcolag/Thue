/* For want of a nail,
 *  the shoe was lost.
 * For want of a shoe,
 *  the horse was lost.
 * For want of a horse,
 *  the knight was lost.
 * For want of a knight,
 *  the battle was lost.
 * So it was a kingdom was lost,
 *  all for the want of a nail.
 *      -- George Herbert, Jacula Prudentum
 *         (Colloqual Adaptation)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define SEP "::="

char * nextinput(FILE * infile);

struct rule {
    char   lhs[64];
    char   rhs[64];
} rulebase[128];

int     ruleidx = 0,
        debug = 0;
char    dataspace[16384],
        tempspace[16384];

int main(int argc, char *argv[]) {
    char   *line,
           *c,
           *tmp,
           *target[64],
            tempstr[64];
    int     state,
            flagstate,
            i,
            order,
            temp,
            rnum[64];
    FILE   *infile;

    srand(time(0));
    target[0] = dataspace;
    memset (rulebase, 0, sizeof (rulebase));
    memset (dataspace, 0, sizeof (dataspace));
    if (argc > 1) {
        infile = fopen (argv[1], "r");
    } else {
        infile = stdin;
    }
    if (infile == NULL) {
        return -1;
    }

    order = 0;
    if (argc > 2) {
        switch (argv[2][0]) {
            case 'r':            /* Right-to-Left Processing */
                order = 2;
                break;
            case 'l':            /* Left-to-Right */
                order = 1;
                break;
            case 'd':
                debug = 1;
                break;
            default:
                /* Ignore it */
                break;
        }
    }

    /* Get input file */
    state = 0;
    while (!feof (infile)) {
        line = nextinput (infile);
        if (state == 0) {
            if (line == NULL || !strlen (line)) {
                continue;
            }
            c = strstr (line, SEP);
            if (c == NULL) {
                fprintf (stderr, "Malformed production: \"%s\"!\n", line);
            } else if (c == line) {
                state = 1;
            } else {
                flagstate = 0;
                for (tmp=line;tmp!=c;tmp++) {
                    if (!isspace (*tmp)) {
                        flagstate = 1;
                    }
                }
                if (flagstate) {
                    *c = '\000';
                    c += strlen (SEP);
                    strcpy (rulebase[ruleidx].lhs, line);
                    strcpy (rulebase[ruleidx].rhs, c);
                    ++ruleidx;
                } else {
                    state = 1;
                }
            }
        } else if (line != NULL) {
            strcat (dataspace, line);
        }
    }

    fclose (infile);

    if (debug) {
        printf ("Initial:  \"%s\"\n", dataspace);
    }

    /* Apply rules */
    state = 1;
    while (state) {
        /* Get all valid LHSs */
        int j = 1;
        int k = 0;
        c = dataspace;
        for (i=0;i<ruleidx;i++) {
            do {
                k = j;
                target[k] = strstr (c, rulebase[i].lhs);
                rnum[k] = i;
                if (target[k] == NULL) {
                    c = dataspace;
                } else {
                    ++j;
                    c = target[k] + 1;
                }
            }
            while (target[k]);
        }

        if (j == 1) {
            state = 0;
            continue;
        }

        /* Sort the LHS list - Just a bubble sort */
        for (i=1;i<j;i++) {
            for (k=1;k<i;k++) {
                if (target[i] < target[k]) {
                    c = target[i];
                    temp = rnum[i];
                    target[i] = target[k];
                    rnum[i] = rnum[k];
                    target[k] = c;
                    rnum[k] = temp;
                }
            }
        }

        /* Choose rule to apply */
        switch (order) {
            case 2:
                i = j - 1;
                break;
            case 1:
                i = 1;
                break;
            default:
                i = rand() % (j - 1) + 1;
                break;
        }
        line = target[i];
        temp = rnum[i];
        c = line + strlen (rulebase[temp].lhs);
        *line = '\000';

        /* Check for I/O */
        i = rulebase[temp].rhs[0] == '~';
        if (i) {
            puts (&rulebase[temp].rhs[1]);
            memset (tempstr, 0, sizeof (tempstr));
        } else {
            i = !strcmp (rulebase[temp].rhs, ":::");
            if (i) {
                scanf (" %64[^\n]", tempstr);
            }
        }

        /* Apply the rule */
        sprintf (tempspace, "%s%s%s", dataspace, i?tempstr:rulebase[temp].rhs, c);
        strcpy (dataspace, tempspace);
        if (debug) {
            puts (dataspace);
        }
    }

    if (debug) {
        printf ("Final:  \"%s\"\n", dataspace);
    }
    return 0;
}

char * nextinput (FILE * infile) {
    static char     inputline[256];
    char           *eol;
    int             idx;

    memset (inputline, 0, sizeof (inputline));
    /* Get next line from file */
    eol = fgets(inputline, sizeof(inputline), infile);
    if (eol == NULL) {
        return NULL;
    }
    for (idx=strlen(inputline)-1;isspace(inputline[idx]);idx--) {
        inputline[idx] = '\000';
    }
    /* Return pointer to string */
    return inputline;
}
