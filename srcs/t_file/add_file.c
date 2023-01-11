#include "ft_ls.h"

void    fileadd_by_time(t_file **files, char *file_name, char *path, int rev){
    t_file  *tmp_files = *files;
    t_file  *new_file = NULL;

    if ((new_file = init_file(file_name, path)) == NULL){
        write(2, "ft_ls: No such file or directory: ", 35);
        write(2, path, ft_strlen(path));
        write(2, "\n", 1);
        return ;
    }
    if (*files == NULL)
        *files = new_file;
    else if((time_compare(*files, new_file) == true && rev == 0) ||
        (time_compare(*files, new_file) == false && rev > 0)){
        new_file->next = *files;
        *files = new_file;
    }
    else{
        while(tmp_files->next && ((time_compare(tmp_files->next, new_file) == false && rev == 0) ||
        (time_compare(tmp_files->next, new_file) == true && rev > 0)))
        tmp_files = tmp_files->next;
        new_file->next = tmp_files->next;
        tmp_files->next = new_file;
    }
}

void    fileadd_by_alpha(t_file **files, char *file_name, char *path, int rev){
    t_file  *tmp_files = *files;
    t_file  *new_file = NULL;

    if ((new_file = init_file(file_name, path)) == NULL){
        write(2, "ft_ls: No such file or directory: ", 35);
        write(2, path, ft_strlen(path));
        write(2, "\n", 1);
        return ;
    }
    if (*files == NULL)
        *files = new_file;
    else if((alphabetic_compare((*files)->name, file_name) == true && rev == 0) ||
        (alphabetic_compare((*files)->name, file_name) == false && rev > 0)){
        new_file->next = *files;
        *files = new_file;
    }
    else{
        while(tmp_files->next && ((alphabetic_compare(tmp_files->next->name, file_name) == false && rev == 0) ||
        (alphabetic_compare(tmp_files->next->name, file_name) == true && rev > 0)))
            tmp_files = tmp_files->next;
        new_file->next = tmp_files->next;
        tmp_files->next = new_file;
    }
}
