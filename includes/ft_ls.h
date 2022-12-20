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
    struct stat     file_infos;
    
    struct s_file   *next;
}               t_file;

typedef struct  s_format{
    int  size_width;
    int  hard_links_width;
    int  user_name_width;
    int  user_group_width;
}               t_format;

t_file  *init_file(char *file_name, char *path);
void    free_files(t_file *files);
int     count_files(t_file *files);
bool    has_file(t_file *files);
bool    has_dir(t_file *files);

bool    alphabetic_compare(char *s1, char *s2);
bool    time_compare(struct stat file1, char *file2);

void    print_long_format(t_file *file, t_format *format);

void	print_dir(t_file *dir, e_options opts, bool root);
void	print_dir_recur(t_file *dir, e_options opts);
void    print_file(t_file *file, t_format *format, e_options opts);

void    fileadd_by_alpha(t_file **files, char *file_name, char *path, int rev);
void    fileadd_by_time(t_file **files, char *file_name, char *path, int rev);

int     get_files_opts(int ac, char **av, t_file **files, e_options *opts);

size_t	count_digit(size_t number);
void    get_width(t_file *files, t_format *format);

bool is_past_six_month(int file_month, int file_year);
int  get_month_number(char *month);

void    fatal_error(t_file *files);

#endif