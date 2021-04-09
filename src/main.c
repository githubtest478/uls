#include "uls.h"

int main(int argn, char **argv) {
    t_names *names = (t_names *)malloc(sizeof(t_names));
    
    init_names_structure(names);
    arg_validation(argn, argv, names);
    print(names);

    // system("leaks -q uls");
    return EXIT_SUCCESS;
}
