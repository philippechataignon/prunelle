#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>

class options
{
public:
    options(int argc, char* argv[]);
    
    void help() ;
    std::string get_in()  {return in;}
    std::string get_out() {return out;}
    int get_verbeux()     {return verbeux;}
    int get_typelien()    {return typelien;} 
private:
    int getopt (int argc, char* argv[], char* opts);
    int opterr ;
    int	optind ;
    int	optopt;
    char* optarg;
    int verbeux ;
    std::string in ;
    std::string out ;
    int typelien ;
};

#endif
