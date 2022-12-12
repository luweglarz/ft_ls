#ifndef FT_LS_H
# define FT_LS_H

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>
#include <errno.h>

#include "../libft/libft.h"
#include "../ft_printf/ft_printf.h"

typedef enum    s_options{
    R = 1,
    a = 2,
    r = 4,
    t = 8,
    l = 16,
    UNKNOWN = 32
}               e_options;

typedef struct  s_file{
    char            name[NAME_MAX];
    char            path[PATH_MAX];
    bool            isdir;

    size_t          hard_links;
    size_t          size;
    struct s_file   *next;
}               t_file;

t_file  *init_file(char *file_name, char *path);
void    free_files(t_file *files);
int     count_files(t_file *files);
bool    has_file(t_file *files);
bool    has_dir(t_file *files);

bool    alphabetic_compare(char *s1, char *s2);
bool    time_compare(char *s1, char *s2);

void    print_long_format(t_file *file, size_t size_max, size_t hard_links_max);

void	print_dir(t_file *dir, e_options opts, bool root);
void	print_dir_recur(t_file *dir, e_options opts);

void    fileadd_by_alpha(t_file **files, char *file_name, char *path, int rev);
void    fileadd_by_time(t_file **files, char *file_name, char *path, int rev);

int     get_files_opts(int ac, char **av, t_file **files, e_options *opts);

void    fatal_error();

#endif