#include "../includes/ft_ls.h"

void    print_file(t_file *file, size_t max_size, size_t max_hard_links, e_options opts){
    if (opts & l)
	    print_long_format(file, max_size, max_hard_links);
    else
        ft_printf("%s\n", file->name);
}