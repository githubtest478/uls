#include "uls.h"

void arg_validation(int argn, char **argv, t_names *names)
{
    names->flags = clear_flags;

    if(argn == 1) {
        names->dirs[0] = ".";
        names->dirs_content[0] = readdir(opendir("."));
        names->dirs_count = 1;
        return;
    }

    names->dirs_count = 0;
    char macOS_options[] = "@1AaCceGhlRrSTtu";

    // char *linux_options[] = {
    //     "almost-all",       //-A
    //     "all",              //-a
    //     "color",            //-G
    //     "human-readable",   //-h
    // };

    for(uint8_t i = 1; i < argn; ++i) {
        if(!mx_strncmp(argv[i], "--", 2)) {
            //set flags with "--" prefix (optional)
        }
        else if(!mx_strncmp(argv[i], "-", 1)) {
            for(int j = 1; j < mx_strlen(argv[i]); ++j) {
                uint32_t pos = mx_get_char_index(macOS_options, argv[i][j]);
                
                if(pos != -1)
                    names->flags |= 1 << pos;
                else
                //error
            }   //set flags with "-" prefix
        }
        else {
            mx_realloc(names->dirs, names->dirs_count + 1);
            
            if(names->dirs)
                names->dirs[names->dirs_count++] = argv[i];   //read dirs to structure
        }
        //place for ERROR hendeling
    }
}
