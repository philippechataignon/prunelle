#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>

#include "options.h" 

options::options(int argc, char *argv[])
{
    int c;
    verbeux = 1;
    typelien = 1 ;
    opterr = 0;
    optind = 1;
    out = "/dev/null" ;
    while ((c = getopt (argc, argv, "vqi:o:l:h")) != -1) {
        switch (c) {
            case 'v':
                verbeux++ ;
                break;
            case 'q':
                verbeux = 0 ;
                break;
            case 'i':
                in = std::string(optarg) ; 
                break;
            case 'o':
                out = std::string(optarg) ;
                break;
            case 'l':
                typelien = atoi(optarg) ;
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

int
options::getopt(int argc, char* argv[], char* opts)
{
	static int sp = 1;
	register int c;
	register char *cp;

	if(sp == 1)
		if(optind >= argc ||
		   argv[optind][0] != '-' || argv[optind][1] == '\0')
			return(EOF);
		else if(strcmp(argv[optind], "--") == 0) {
			optind++;
			return(EOF);
		}
	optopt = c = argv[optind][sp];
	if(c == ':' || (cp=strchr(opts, c)) == 0) {
		printf("%s : illegal option -- %c",argv[0], c);
		if(argv[optind][++sp] == '\0') {
			optind++;
			sp = 1;
		}
		return('?');
	}
	if(*++cp == ':') {
		if(argv[optind][sp+1] != '\0')
			optarg = &argv[optind++][sp+1];
		else if(++optind >= argc) {
			printf("%s : option requires an argument -- %c", argv[0], c);
			sp = 1;
			return('?');
		} else
			optarg = argv[optind++];
		sp = 1;
	} else {
		if(argv[optind][++sp] == '\0') {
			sp = 1;
			optind++;
		}
		optarg = 0;
	}
	return(c);
}

void
options::help()
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
