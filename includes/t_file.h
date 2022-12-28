#ifndef T_FILE_H
# define T_FILE_H

typedef struct  s_file{
    char            name[NAME_MAX];
    char            path[PATH_MAX];
    bool            isdir;
    struct stat     file_infos;
    
    struct s_file   *next;
}               t_file;

t_file  *init_file(char *file_name, char *path);
void    free_files(t_file *files);
int     count_files(t_file *files);
bool    has_file(t_file *files);
bool    has_dir(t_file *files);
bool    is_device(t_file *file);

void    fileadd_by_alpha(t_file **files, char *file_name, char *path, int rev);
void    fileadd_by_time(t_file **files, char *file_name, char *path, int rev);

bool    alphabetic_compare(char *s1, char *s2);
bool    time_compare(t_file *file1, t_file *file2);

#endif