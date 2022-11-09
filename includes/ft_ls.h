#ifndef FT_LS_H
# define FT_LS_H

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include "../libft/libft.h"

typedef enum    s_options{
    R = 1,
    a = 2,
    r = 4,
    t = 8,
    l = 16,
    UNKNOWN = 32
}               e_options;

t_list  *get_args_opts(int ac, char **av, e_options *opts);

#endif