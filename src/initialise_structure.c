#include "uls.h"

void init_names_structure(t_names *names)
{
    RESET_FLAG(names->flags, ~clear_flags);
    names->flags |= flag_C;
    names->dirs_count = 0;
    names->dirs_index = 0;
    names->count_file = 0;
    names->count_line = 0;
    names->total_size = 0;
    names->sort = NULL;
    names->dirs = NULL;
    names->list = NULL;
    names->dirs_content = NULL;
    names->folder = NULL;
}
