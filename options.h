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
    std::string get_pre() {return pre;}
    int get_verbeux()     {return verbeux;}
    int get_typelien()    {return typelien;}
    double get_valmax()    {return valmax;}
private:
    int getopt (int argc, char* argv[], const char* opts);
    int opterr ;
    int	optind ;
    int	optopt;
    char* optarg;
    int verbeux ;
    std::string in ;
    std::string out ;
    std::string pre ;
    int typelien ;
    double valmax;
};

#endif
