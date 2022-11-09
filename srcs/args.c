#include "../includes/ft_ls.h"

static void getOpts(char *av, e_options *opts){
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

t_list *get_args_opts(int ac, char **av, e_options *opts){
    t_list      *args = NULL;
    struct stat dummy;
    int         i = 1;

    while (i < ac){
        if (av[i][0] =='-' && av[i][1] != '\0')
            getOpts(av[i] + 1, opts);
        else {
            if (stat(av[i], &dummy) == -1)
                printf("ls: %s: No such file or directory\n", av[i]);
            else
                ft_lstadd_back(&args, ft_lstnew(ft_strdup(av[i])));
        }
        i++;
    }
    return args;
}