#include "../includes/ft_ls.h"

bool    has_file(t_file *files){
    t_file *tmp_files = files;

    while(tmp_files){
        if (tmp_files->isdir == false)
            return (true);
        tmp_files = tmp_files->next;
    }
    return (false);
}

bool    has_dir(t_file *files){
    t_file *tmp_files = files;

    while(tmp_files){
        if (tmp_files->isdir == true)
            return (true);
        tmp_files = tmp_files->next;
    }
    return (false);
}

void    free_files(t_file *files){
    t_file *to_free;

    while (files){
        to_free = files;
        files = files->next;
        free(to_free);
    }
}

int count_files(t_file *files){
    int    i = 0;
    t_file *tmp_files = files;

    while(tmp_files){
        tmp_files = tmp_files->next;
        i++;
    }
    return (i);
}

t_file  *init_file(char *file_name, char *path){
    t_file      *new_file = NULL;
    struct stat file_infos;

    if (!(new_file = ft_calloc(sizeof(t_file), 1)))
        return (NULL);
    file_name = ft_strdup(file_name);
    ft_bzero(&new_file->name, sizeof(new_file->name));
    ft_strncpy(new_file->name, file_name, ft_strlen(file_name));
    free(file_name);
    ft_bzero(&new_file->path, sizeof(new_file->path));
    ft_strncpy(new_file->path, path, ft_strlen(path));
    new_file->next = NULL;

    if(lstat(new_file->path, &file_infos) == -1)
        return (NULL);
    if (S_ISDIR(file_infos.st_mode))
        new_file->isdir = true;
    new_file->hard_links = file_infos.st_nlink;
    new_file->size = file_infos.st_size;
    return (new_file);
}
