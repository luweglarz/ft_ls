#include "../includes/ft_ls.h"

bool lexicographical_compare(char *s1, char *s2){
    int i = 0;
    
    while(s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return (s1[i] > s2[i]);
}

bool time_compare(char *s1, char *s2){
    struct stat     s1_stat;
    struct stat     s2_stat;
    struct timespec s1_time;
    struct timespec s2_time;
    
    if (stat(s1, &s1_stat) == -1)
        fatal_error();
    s1_time = s1_stat.st_ctimespec;
    if (stat(s2, &s2_stat) == -1)
        fatal_error();
    s2_time = s2_stat.st_ctimespec;
    return (s1_time.tv_nsec > s2_time.tv_nsec);
}

static char *get_file_name(char *file_name){
    int i = ft_strlen(file_name) - 1;

    while(i && file_name[i] != '/')
        i--;
    if (i == 0)
        return (ft_strdup(file_name));
    return (ft_substr(file_name, i + 1, ft_strlen(file_name) - i));
}

t_file  *init_file(char *file_name){
    char    cat[PATH_MAX];
    t_file  *new_file = NULL;

    ft_bzero(&cat, sizeof(cat));
    if(strncmp(file_name, "./", 2) != 0)
        cat[0] = '.'; cat[1] = '/';
    if (!(new_file = ft_calloc(sizeof(t_file), 1)))
        fatal_error();
    new_file->name = get_file_name(file_name);
    if (file_name[0] == '.' && file_name[1] == '\0'){
        new_file->path[0] = '.';
        new_file->path[1] = '/';
    }
    else{
        ft_strncat(cat, file_name, ft_strlen(file_name));
        ft_strncpy(new_file->path, cat, ft_strlen(cat));
    }
    new_file->next = NULL;
    if (opendir(new_file->path) != NULL)
        new_file->isdir = true;
    else
        new_file->isdir = false;
    return (new_file);
}
