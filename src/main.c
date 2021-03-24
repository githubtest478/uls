#include "uls.h"

int main(int argn, char **argv) {
    t_names *names = malloc(sizeof(t_names));

    arg_validation(argn, argv, names);
    // init_structure(names); //need to be developed
    uls(names);//example

    free(names);

    return EXIT_SUCCESS;
}
