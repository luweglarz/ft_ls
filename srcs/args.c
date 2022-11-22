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

void    get_files_opts(int ac, char **av, t_file **files, e_options *opts){
    char    path[PATH_MAX];
    struct stat dummy;
    int         i = 1;

    while (i < ac){
        if (av[i][0] =='-' && av[i][1] != '\0')
            get_opts(av[i] + 1, opts);
        else {
            if (stat(av[i], &dummy) == -1)
                ft_printf("ls: %s: No such file or directory\n", av[i]);
            else{
                ft_bzero(&path, sizeof(path));
                ft_strncpy(path, ".", ft_strlen(av[i]));
                if (av[i][0] != '.' && av[i][1] != '/' && av[i][2] != '\0'){
                    ft_strncat(path, "/", 1);
                    ft_strncat(path, av[i], ft_strlen(av[i]));
                }
                if (*opts & t)
                    fileadd_by_time(files, av[i], path,  *opts & r);
                else
                    fileadd_by_alpha(files, av[i], path, *opts & r);
            }
        }
        i++;
    }
}