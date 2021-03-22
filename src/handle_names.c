#include "uls.h"

//обработка имен файлов и директорий (нужны как и валидные так и не валидные)
t_names *mx_process_names(int end_flags, int argc, char **argv) {
    if(end_flags == argc) {     //если конец равен количеству аргументов то имен нету! 
        return NULL;
    }
    t_names *names = (t_names*)malloc(sizeof(t_names));     // создание струкруры под имена 
    names->count = 0;   //  инициализания количество имен 
    names->names = (char**)malloc(sizeof(char*) * (argc - end_flags));

    for(int i = end_flags, y = 0; i < argc; ++i, ++y) {     // проход по всем именам 
        int len = mx_strlen(argv[i]);   //  узнаем длину именни
        names->names[y] = (char*)malloc(sizeof(char) * len);    //  выделяем нужное количиство памяти
        mx_strcpy(names->names[y], argv[i]);    //  копируем в структуру имя
        names->count += 1;  //  увеличиваем количество имен на +1
    }
    return names;   // возвращаем указатель на сруктуру
}







