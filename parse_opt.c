/*                                                                           */
/* This program is free software; you can redistribute it and/or modify      */
/* it under the terms of the GNU General Public License as published by      */
/* the Free Software Foundation; either version 2 of the License, or         */
/* (at your option) any later version.                                       */
/*                                                                           */
/* This program is distributed in the hope that it will be useful,           */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/* GNU General Public License for more details.                              */
/*                                                                           */
/* You should have received a copy of the GNU General Public License         */
/* along with this program; if not, write to the Free Software               */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <getopt.h>
#include "parse_opt.h"

void
help()
{
    puts ("Prunelle - Philippe CHATAIGNON") ;
    puts ("sous license GPL") ;
    puts ("");
    puts ("Utilisation : prunelle -i fich [-o fich] -l lien [-v] [-q] [-h]") ;
    puts ("        -i : fichier flux préparé pour prunelle (obligatoire)");
    puts ("        -o : nom du fichier en sortie (par défaut : /dev/null)");
    puts ("        -l : type de lien (par défaut 0=aa)");
    puts ("        -q : supprime les messages en sortie");
    puts ("        -v : augmente les messages en sortie");
    puts ("        -h : affiche cette aide");
    puts ("");
}

void
parse_opt(int argc, char *argv[], int* verbeux, char* in, char* out, int* lien)
{
    int c;

    *verbeux = 1;
    opterr = 0;
    strncpy(out,"/dev/null",128) ;
    while ((c = getopt (argc, argv, "vqi:o:l:h")) != -1) {
        switch (c) {
            case 'v':
                *verbeux++ ;
                break;
            case 'q':
                *verbeux = 0 ;
                break;
            case 'i':
                strncpy(in,optarg,128) ;
                break;
            case 'o':
                strncpy(out,optarg,128) ;
                break;
            case 'l':
                *lien = atoi(optarg) ;
                break;
            case 'h' :
                help() ;
                exit(10) ;
                break ;
            case '?':
                if (isprint (optopt)) {
                    help() ;
                    fprintf (stderr, "Option inconnue `-%c'.\n", optopt);
                } else {
                    help() ;
                    fprintf (stderr, "Caractère non reconnu dans les options `\\x%x'.\n",optopt);
                }
            default:
                abort ();
        }
    }    
}
