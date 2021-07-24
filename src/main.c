#include "uls.h"

int main(int argn, char **argv) {
    int status = 0;
    t_names *names = (t_names *)malloc(sizeof(t_names));
    
    init_names_structure(names);
    arg_validation(argn, argv, names);
    status = names->count.status;
    print(names);

    // system("leaks -q uls");
    return status;
}
