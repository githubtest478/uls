#ifndef ULS_H
#define ULS_H //#include "uls.h"

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>
#include "libmx.h"

//flag macrosses
#define SET_FLAG(reg, flag) (reg |= flag) //use to set flag
#define RESET_FLAG(reg, flag) (reg &= ~flag) //use to clear the flag
#define READ_FLAG(reg, flag) (reg & flag) //use to identify if flag(see e_flagset) is set

//error massages
#define USAGE "usage: uls [-l] [file ...]\n"

enum e_flagset {
    clear_flags =   ((uint16_t)0x0000U),    
    flag_At     =   ((uint16_t)0x0001U),    //-@ Display extended attribute keys and sizes.
    flag_one    =   ((uint16_t)0x0002U),    //-1 force output to be one entry per line.
    flag_A      =   ((uint16_t)0x0004U),    //List all entries including those starting with a dot . Except for . and ..
    flag_a      =   ((uint16_t)0x0008U),    //List all entries including those starting with a dot .
    flag_C      =   ((uint16_t)0x0010U),    //Force multi-column output
    flag_c      =   ((uint16_t)0x0020U),    //Use time when file status was last changed for sorting or printing.
    flag_e      =   ((uint16_t)0x0040U),    //-e  Print the Access Control List (ACL) associated with the file, if present, in long (-l) output.
    flag_G      =   ((uint16_t)0x0080U),    //-G Enable colour output.
    flag_h      =   ((uint16_t)0x0100U),    //-h used with -l and -s, print sizes like 1K 234M 2G etc.
    flag_l      =   ((uint16_t)0x0200U),    //-l use a long listing format
    flag_R      =   ((uint16_t)0x0400U),    //-R recursively list subdirectories recursively
    flag_r      =   ((uint16_t)0x0800U),    //-r Reverse the order of the sort to get reverse lexicographical order or the oldest entries first.
    flag_S      =   ((uint16_t)0x1000U),    //-S Sort files by size
    flag_T      =   ((uint16_t)0x2000U),    //-T  used with the -l option, display complete time information for the file, including month, day, hour, minute, second, and year.
    flag_t      =   ((uint16_t)0x4000U),    //-t Sort by time modified
    flag_u      =   ((uint16_t)0x8000U)     //-u Use time of last access, instead of last modification of the file for sorting (-t) or printing (-l).
};

// структура для файлов и директорий
typedef struct s_names {
    char **dirs;
    struct dirent **dirs_content;   //ino_t  d_ino       File serial number.
                                    //char   d_name[]    Filename string of entry.
    uint8_t dirs_count;
    uint16_t flags;
}              t_names;

//functons
void arg_validation(int argn, char **argv, t_names *names);


#endif /* ULS_H */
