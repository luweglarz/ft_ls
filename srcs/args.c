#include "../includes/ft_ls.h"

static void get_opts(char *av, e_options *opts){
    int i = 0;

    while(av[i]){
        if (av[i] == 'R')
            *opts = *opts | R;  
        else if (av[i] == 'a')
            *opts = *opts | a;
        else if (av[i] == 'a')
            *opts = *opts | a;
        else if (av[i] == 'r')
            *opts = *opts | r;
        else if (av[i] == 't')
            *opts = *opts | t;
        else if (av[i] == 'l')
            *opts = *opts | l;
        else
            *opts = *opts | UNKNOWN;
        i++;
    }
}

void    fileadd_by_time(int rev){
    (void)rev;

}

void    fileadd_by_alpha(t_file **files, char *file_name, int rev){
    t_file  *tmp_files = *files;
    t_file  *new_file = NULL;

    new_file = init_file(file_name);
    if (*files == NULL)
        *files = new_file;
    else if(((*files)->name[0] <= file_name[0] && rev > 0) || ((*files)->name[0] >= file_name[0] && rev == 0)){
            new_file->next = *files;
            *files = new_file;
    }
    else{
        while(tmp_files->next && ((tmp_files->next->name[0] <= file_name[0] && rev == 0) || (tmp_files->next->name[0] >= file_name[0] && rev > 0)))
            tmp_files = tmp_files->next;
        new_file->next = tmp_files->next;
        tmp_files->next = new_file;
    }
}

t_file *get_files_opts(int ac, char **av, e_options *opts){
    t_file      *files = NULL;
    struct stat dummy;
    int         i = 1;

    while (i < ac){
        if (av[i][0] =='-' && av[i][1] != '\0')
            get_opts(av[i] + 1, opts);
        else {
            if (stat(av[i], &dummy) == -1)
                printf("ls: %s: No such file or directory\n", av[i]);
            else{
                if (*opts & t)
                    fileadd_by_time(*opts & r);
                else
                    fileadd_by_alpha(&files, av[i], *opts & r);
            }
        }
        i++;
    }
    return files;
}