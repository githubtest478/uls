#include "uls.h"







//обработка и добавление флагов
t_flags *mx_process_flags(int flags_count, char **argv) {
    if(flags_count == 0) {  /* Если флагов 0 то возвращаем NULL */
        return NULL;
    }
    t_flags *flags = (t_flags*)malloc(sizeof(t_flags)); // создание струкруты ФЛАГОВ
    
    for(int i = 1; i <= flags_count; ++i) {     //начиная с первого и до (flags_count) проверка и добовление флагов
        mx_check_flags_in_str(argv[i], flags);      //проверка флага_флагов
    }
    return flags;
}

//  проверка флага_флагов в строке (строка уже приходит в формате (-ылоиыовимр\0))
void mx_check_flags_in_str(char *str, t_flags *flags) { 
    while(*(++str)) {       //пока не конец строки а также пропуск перкого символа ('-') !!!
        mx_check_flag(*str, flags);     //проверка символа на соответсвующий флаг, если он есть то ставим true исле нет то ошибка !!!     
    }
}

// ищет флаг и помечает его TRUE !ИНАЧЕ! ERROR
void mx_check_flag(char flag, t_flags *flags) {
    switch (flag) {
        case 108:   // ascii for 'l'                      
            flags->l = true;        /* добавление флага в структуру */
            break;
    
        default:
            printf("ERROR\n");      /* если флага не нашло то ошибка  */   
            break;
    }
}









