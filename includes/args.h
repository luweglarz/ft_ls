#ifndef ARGS_H
# define ARGS_H

typedef enum    s_options{
    R = 1,
    a = 2,
    r = 4,
    t = 8,
    l = 16,
    UNKNOWN = 32
}               e_options;

int     get_files_opts(int ac, char **av, t_file **files, e_options *opts);

#endif