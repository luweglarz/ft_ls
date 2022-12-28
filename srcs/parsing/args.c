#include "../../includes/ft_ls.h"

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

void    build_file(t_file **files, char *file, e_options opts){
    char    path[PATH_MAX];

    ft_bzero(&path, sizeof(path));
    ft_strncpy(path, file, ft_strlen(file));
    if (opts & t)
        fileadd_by_time(files, file, path,  opts & r);
    else
        fileadd_by_alpha(files, file, path, opts & r);

}

int    get_files_opts(int ac, char **av, t_file **files, e_options *opts){
    struct stat dummy;
    int         i = 1;
    int         errors = 0;

    while (i < ac){
        if (av[i][0] =='-' && av[i][1] != '\0')
            get_opts(av[i] + 1, opts);
        else {
            if (stat(av[i], &dummy) == -1){
                write(2, "ft_ls: ", 8);
                write(2, av[i], ft_strlen(av[i]));
                write(2, ": No such file or directory\n", 29);
                errors++;
            }
            else
                build_file(files, av[i], *opts);
        }
        i++;
    }
    if (errors == 0 && *files == NULL){
        if (*opts & t)
            fileadd_by_time(files, ".", ".",  *opts & r);
        else
            fileadd_by_alpha(files, ".", ".", *opts & r);
    }
    return (errors);
}