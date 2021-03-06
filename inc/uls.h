#ifndef ULS_H
#define ULS_H //#include "uls.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <sys/ioctl.h>
#include "libmx.h"
#include <sys/xattr.h>
#include <grp.h>
#include <uuid/uuid.h>


//flag macrosses
#define SET_FLAG(reg, flag) (reg |= (flag)) //use to set flag
#define RESET_FLAG(reg, flag) (reg &= ~(flag)) //use to clear the flag
#define READ_FLAG(reg, flag) !!(reg & (flag)) //use to identify if flag(see e_flagset) is set

//error massages
#define USAGE "usage: uls [-@1AaCceGhlRrSTtufixpms] [file ...]\n"

//Color set
#define BLACK               "\033[30m"
#define RED                 "\033[31m"
#define GREEN               "\033[32m"
#define ORANGE              "\033[33m"
#define BLUE                "\033[34m"
#define MAGENTA             "\033[35m"
#define CYAN                "\033[36m"
#define LIGHT_GRAY          "\033[37m"
#define DEFAULT_COLLOR      "\033[0m"

#define BLACK_BG            "\033[40m"
#define	RED_BG              "\033[41m"
#define GREEN_BG            "\033[42m"
#define ORANGE_BG           "\033[43m"
#define BLUE_BG             "\033[44m"
#define MAGENTA_BG          "\033[45m"
#define CYAN_BG             "\033[46m"
#define LIGHT_GRAY_BG       "\033[47m"
#define DEFAULT_COLLOR_BG   "\033[49m"

enum e_flagset {
    clear_flags =   ((uint32_t)0x00000000U),    
    flag_At     =   ((uint32_t)0x00000001U),    //-@ Display extended attribute keys and sizes in long (-l) output
    flag_one    =   ((uint32_t)0x00000002U),    //-1 Force output to be one entry per line.  This is the default when output is not to a terminal.
    flag_A      =   ((uint32_t)0x00000004U),    //-A List all entries except for . and ..  Always set for the super-user.
    flag_a      =   ((uint32_t)0x00000008U),    //-a Include directory entries whose names begin with a dot (.).
    flag_C      =   ((uint32_t)0x00000010U),    //-C Force multi-column output; this is the default when output is to a terminal.
    flag_c      =   ((uint32_t)0x00000020U),    //-c Use time when file status was last changed for sorting (-t) or long printing (-l).
    flag_e      =   ((uint32_t)0x00000040U),    //-e Print the Access Control List (ACL) associated with the file, if present, in long (-l) output.
    flag_G      =   ((uint32_t)0x00000080U),    //-G Enable colorized output.  This option is equivalent to defining CLICOLOR in the environment.
    flag_h      =   ((uint32_t)0x00000100U),    //-h When used with the -l option, use unit suffixes: Byte, Kilobyte, Megabyte, Gigabyte, Terabyte and Petabyte in order to reduce the number of digits to three or less using base 2 for sizes.
    flag_l      =   ((uint32_t)0x00000200U),    //-l use a long listing format
    flag_R      =   ((uint32_t)0x00000400U),    //-R recursively list subdirectories recursively
    flag_r      =   ((uint32_t)0x00000800U),    //-r Reverse the order of the sort to get reverse lexicographical order or the oldest entries first.
    flag_S      =   ((uint32_t)0x00001000U),    //-S Sort files by size
    flag_T      =   ((uint32_t)0x00002000U),    //-T used with the -l option, display complete time information for the file, including month, day, hour, minute, second, and year.
    flag_t      =   ((uint32_t)0x00004000U),    //-t Sort by time modified
    flag_u      =   ((uint32_t)0x00008000U),    //-u Use time of last access, instead of last modification of the file for sorting (-t) or printing (-l).
    flag_f      =   ((uint32_t)0x00010000U),    //-f Output is not sorted.
    flag_i      =   ((uint32_t)0x00020000U),    //-i For each file, print the file's file serial number 
    flag_x      =   ((uint32_t)0x00040000U),    //-x Stream output format; The same as -C, except that the multi-column output is produced with entries sorted across, rather than down, the columns.
    flag_p      =   ((uint32_t)0x00080000U),    //-p Write a slash (/) after each filename if that file is a directory.
    flag_m      =   ((uint32_t)0x00100000U),    //-m Stream output format; List files across the page, separated by commas.
    flag_s      =   ((uint32_t)0x00200000U),    //-s Display the number of file system blocks actually used by each file, in units of 512 bytes, where partial units are rounded up to the next integer value.
    flag_file   =   ((uint32_t)0x00400000U),    //Addition flag
    flag_link   =   ((uint32_t)0x00800000U)     //Addition flag
};

typedef struct s_count {
    uint32_t dirs; 
    uint32_t files; 
    uint32_t links; 
    uint32_t line;
    uint32_t dirs_index;
    uint32_t files_index;
    uint32_t links_index;
    uint32_t recursion;
    int status;
}              t_count;

// ?????????????????? ?????? ???????????? ?? ????????????????????
typedef struct s_names {
    char **dirs;
    char **files;
    char **links;
    char **recursion_dirs;
    char ***list;
    struct stat filestat;
    struct dirent *dirs_content;    //ino_t  d_ino       File serial number.
                                    //char   d_name[]    Filename string of entry.
    uint64_t total_size;
    uint32_t *sort;
    time_t *time_sort;
    uint32_t flags;
    t_count count;
    DIR *folder;
}              t_names;

//functons
void arg_validation(int argn, char **argv, t_names *names);
void set_flags(t_names *names, char c);
void init_names_structure(t_names *names);
void print(t_names *names);
void read_dirs_struct(t_names *names);
void read_files_struct(t_names *names);
void read_links_struct(t_names *names);
void delete_list(t_names *names);
void sort(t_names *names);
void init_list(t_names *names);
void LineUp(t_names *names);
void fill_line(t_names *names);
void print_list(t_names *names);
void recursion_R_flag_main(t_names *names);
void multicolumn(t_names *names);
void set_color(t_names *names, char **file_name);
void print_xattr(t_names *names, uint8_t index_i, uint8_t index_j);

char *get_serial_number(t_names *names);
char *get_blocksize(t_names *names);
char *get_permission(t_names *names);
char *get_link_param(t_names *names);
char *get_owner(t_names *names);
char *get_group(t_names *names);
char *get_size(t_names *names);
char *get_time(t_names *names);
char *get_name(t_names *names);
char *get_link(t_names *names);

//debug function
void print_set_flags(t_names *names);

#endif /* ULS_H */
