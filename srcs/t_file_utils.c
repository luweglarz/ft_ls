#include "../includes/ft_ls.h"

int count_files(t_file *files){
    int    i = 0;
    t_file *tmp_files = files;

    while(tmp_files){
        tmp_files = tmp_files->next;
        i++;
    }
    return (i);
}

static char get_alpha(char c){
    if (c >= 'A' && c <= 'Z')
        return (c + 32);
    return (c);
}

bool alphabetic_compare(char *s1, char *s2){
    int i = 0;

    while(s1[i] && s2[i] && get_alpha(s1[i]) == get_alpha(s2[i]))
        i++;
    return (get_alpha(s1[i]) > get_alpha(s2[i]));
}

bool time_compare(char *s1, char *s2){
    struct stat     s1_stat;
    struct stat     s2_stat;
    
    if (stat(s1, &s1_stat) == -1)
        fatal_error();
    if (stat(s2, &s2_stat) == -1)
        fatal_error();
    return (s1_stat.st_ctime > s2_stat.st_ctime);
}

static char *get_file_name(char *file_name){
    int begin = ft_strlen(file_name) - 1;
    int end = ft_strlen(file_name) - 1;

    while(end && file_name[end] == '/')
        end--;
    begin = end;
    while(begin && file_name[begin] != '/')
        begin--;
    if (begin == 0)
        end++;
    return (ft_substr(file_name, begin, end + begin));
}

void    free_files(t_file *files){
    t_file *to_free;

    while (files){
        to_free = files;
        free(to_free->name);
        files = files->next;
        free(to_free);
    }
}

t_file  *init_file(char *file_name, char *path){
    t_file  *new_file = NULL;
    DIR     *is_dir = false;

    if (!(new_file = ft_calloc(sizeof(t_file), 1)))
        fatal_error();
    file_name = get_file_name(file_name);
    ft_bzero(&new_file->name, sizeof(new_file->name));
    ft_strncpy(new_file->name, file_name, ft_strlen(file_name));
    free(file_name);
    ft_bzero(&new_file->path, sizeof(new_file->path));
    ft_strncpy(new_file->path, path, ft_strlen(path));

    new_file->next = NULL;

    is_dir = opendir(new_file->path);
    if (is_dir != NULL){
        new_file->isdir = true;
        free(is_dir);
    }
    return (new_file);
}
