#ifndef PARSE_OPT_H
#define PARSE_OPT_H

#ifdef  __cplusplus
extern "C" {
#endif
    void help() ;
    void parse_opt(int argc, char *argv[], int* verbeux, char* in, char* out, int* lien) ;
#ifdef  __cplusplus
}
#endif
#endif
