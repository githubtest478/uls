#include "uls.h"

static void init_count_struct(t_count *count)
{
    count->dirs = 0;
    count->files = 0;
    count->links = 0;
    count->line = 0;
    count->dirs_index = 0;
    count->files_index = 0;
    count->links_index = 0;
    count->recursion = 0;
    count->status = 0;
}

void init_names_structure(t_names *names)
{
    RESET_FLAG(names->flags, ~clear_flags);
    names->flags |= flag_C;
    names->total_size = 0;
    init_count_struct(&names->count);
    names->sort = NULL;
    names->dirs = NULL;
    names->files = NULL;
    names->links = NULL;
    names->list = NULL;
    names->dirs_content = NULL;
    names->folder = NULL;
    names->recursion_dirs = NULL;
}
