#include "includes/ft_ls.h"

int main(int ac, char **av){
    e_options   opts = 0;
    t_list      *args = NULL;

    args = get_args_opts(ac, av, &opts);
    if (args == NULL)
        ft_lstadd_back(&args, ft_lstnew(strdup("./")));
    return (0);
}
