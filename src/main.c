#include "uls.h"

int main(int argn, char **argv) {
    t_names *names = (t_names *)malloc(sizeof(t_names));
    
    init_dir_structure(names);
    arg_validation(argn, argv, names);
    print_dirs(names);

    return EXIT_SUCCESS;
}
