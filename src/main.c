#include "uls.h"

int main(int argn, char **argv) {
    t_names *names = malloc(sizeof(t_names));

    arg_validation(argn, argv, names);
    print_dirs(names);

    free(names);
    
    return EXIT_SUCCESS;
}
