#include "../includes/ft_ls.h"

void    fileadd_by_time(int rev){
    (void)rev;

}

void    fileadd_by_alpha(t_file **files, char *file_name, int rev){
    t_file  *tmp_files = *files;
    t_file  *new_file = NULL;

    new_file = init_file(file_name);
    if (*files == NULL)
        *files = new_file;
    else if((lexicographical_compare((*files)->name, file_name) == true && rev == 0) ||
        (lexicographical_compare((*files)->name, file_name) == false && rev > 0)){
        new_file->next = *files;
        *files = new_file;
    }
    else{
        while(tmp_files->next && ((lexicographical_compare(tmp_files->next->name, file_name) == false && rev == 0) ||
        (lexicographical_compare(tmp_files->next->name, file_name) == true && rev > 0)))
            tmp_files = tmp_files->next;
        new_file->next = tmp_files->next;
        tmp_files->next = new_file;
    }
}
