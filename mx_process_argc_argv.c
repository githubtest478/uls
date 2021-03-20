#include "uls.h"




// обработка входящих аргументов и проверка их на валидность
void mx_process_argc_argv(int argc, char **argv) { 
    t_flags *flags = mx_process_flags(mx_count_flags(argc, argv), argv);    //если флаги есть то возвращает указатель на струкруру !ИНАЧЕ! NULL !!!! 
    

    // test
    if(flags == NULL) {
        printf("no flags");
    }




}







// подсчет количества всех аргументов корорые начинаются с ('-')
int mx_count_flags(int argc, char **argv) {
    int flags_count = 0;

    for(int i = 1; i < argc; ++i) {
        if(argv[i][0] == '-') {
            ++flags_count;
        }
    }
    return flags_count;
}

