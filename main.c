#include "includes/ft_ls.h"

int main(int ac, char **av){
    e_options   opts = 0;
    t_list      *args = NULL;
    t_file      *files = NULL;

    if (ac > 1)
        files = get_files_opts(ac, av, &opts);
    if (ac == 1)
        files = init_file(".");
    return (0);
}
