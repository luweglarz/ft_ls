#ifndef FT_LS_H
# define FT_LS_H

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>
#include <stdbool.h>
#include <errno.h>

#include "../libft/libft.h"

typedef enum    s_options{
    R = 1,
    a = 2,
    r = 4,
    t = 8,
    l = 16,
    UNKNOWN = 32
}               e_options;

typedef struct  s_file{
    char            *name;
    char            path[PATH_MAX];
    bool            isdir;
    struct s_file   *next;
}               t_file;

t_file  *init_file(char *file_name);
int     count_files(t_file *files);
bool    lexicographical_compare(char *s1, char *s2);
bool    time_compare(char *s1, char *s2);

void	print_dir(t_file *file, e_options opts, bool root);

void    fileadd_by_alpha(t_file **files, char *file_name, int rev);
void    fileadd_by_time(t_file **files, char *file_name, int rev);

void    get_files_opts(int ac, char **av, t_file **files, e_options *opts);

void    fatal_error();

#endif